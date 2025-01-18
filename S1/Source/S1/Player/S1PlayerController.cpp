// Fill out your copyright notice in the Description page of Project Settings.


#include "S1PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "System/S1AssetManager.h"
#include "Data/S1InputData.h"
#include "S1GameplayTags.h"
#include "Character/S1Player.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"


AS1PlayerController::AS1PlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void AS1PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (const US1InputData* InputData = US1AssetManager::GetAssetByName<US1InputData>("InputData"))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputData->InputMappingContext, 0);
		}
	}

	S1Player = Cast<AS1Player>(GetCharacter());
}

void AS1PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (const US1InputData* InputData = US1AssetManager::GetAssetByName<US1InputData>("InputData"))
	{
		UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

		auto Action1 = InputData->FindInputActionByTag(S1GameplayTags::Input_Action_SetDestination);

		// Setup mouse input actions
		EnhancedInputComponent->BindAction(Action1, ETriggerEvent::Started, this, &ThisClass::OnInputStarted);
		EnhancedInputComponent->BindAction(Action1, ETriggerEvent::Triggered, this, &ThisClass::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(Action1, ETriggerEvent::Completed, this, &ThisClass::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(Action1, ETriggerEvent::Canceled, this, &ThisClass::OnSetDestinationReleased);
	}
}

void AS1PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	TickCursorTrace();

	if (false == GetCharacter()->GetMesh()->GetAnimInstance()->Montage_IsPlaying(nullptr))
	{
		SetCreatureState(ECreatureState::Moving);
	}

	ChaseTargetAndAttack();
}

void AS1PlayerController::TickCursorTrace()
{
	if (bMousePressed)
	{
		return;
	}

	FHitResult OutCursorHit;
	if (false == GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, OUT OutCursorHit))
	{
		return;
	}

	AS1Character* LocalHighlightActor = Cast<AS1Character>(OutCursorHit.GetActor());
	if (LocalHighlightActor == nullptr)
	{
		// 이미 highlight 된 액터가 있었는데 없어짐.
		if (HighlightActor)
		{
			HighlightActor->UnHighlight();
		}
	}
	else
	{
		if (HighlightActor)
		{
			// 이미 highlight 된 액터가 있었는데 새로운 액터를 highlight 한 상황.
			if (HighlightActor != LocalHighlightActor)
			{
				HighlightActor->UnHighlight();
				LocalHighlightActor->Highlight();
			}
			
			// 동일한 액터면 무시
		}
		else
		{
			// 원래 없었고 새로운 타겟.
			LocalHighlightActor->Highlight();
		}
	}

	HighlightActor = LocalHighlightActor;
}

void AS1PlayerController::ChaseTargetAndAttack()
{
	if (TargetActor == nullptr)
	{
		return;
	}

	if (GetCreatureState() == ECreatureState::Skill)
	{
		return;
	}

	FVector Direction = TargetActor->GetActorLocation() - S1Player->GetActorLocation();
	
	if (Direction.Length() < 250.0f) // Is in attack range?
	{
		GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Cyan, TEXT("Attack"));

		if (AttackMontage)
		{
			if (bMousePressed)
			{
				FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(S1Player->GetActorLocation(), TargetActor->GetActorLocation());
				S1Player->SetActorRotation(Rotator);

				GetCharacter()->PlayAnimMontage(AttackMontage);
				SetCreatureState(ECreatureState::Skill);

				TargetActor = HighlightActor;
			}
			else
			{
				TargetActor = nullptr;
			}
		}
	}
	else
	{
		FVector WorldDirection = Direction.GetSafeNormal();
		S1Player->AddMovementInput(WorldDirection, 1.0f, false);
	}
}

void AS1PlayerController::OnInputStarted()
{
	StopMovement();
	bMousePressed = true;
	TargetActor = HighlightActor;
}

// Triggered every frame when the input is held down
void AS1PlayerController::OnSetDestinationTriggered()
{
	if (GetCreatureState() == ECreatureState::Skill)
	{
		return;
	}

	if (TargetActor)
	{
		return;
	}

	// Flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();

	// Look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, OUT Hit);

	// If hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}

	if (FollowTime <= ShortPressThreshold)
		return;

	// Move towards mouse pointer or touch
	if (S1Player)
	{
		FVector WorldDirection = (CachedDestination - S1Player->GetActorLocation()).GetSafeNormal();
		S1Player->AddMovementInput(WorldDirection, 1.0f, false);
	}
}

void AS1PlayerController::OnSetDestinationReleased()
{
	bMousePressed = false;

	if (GetCreatureState() == ECreatureState::Skill)
	{
		return;
	}

	// If it was short press
	if (FollowTime <= ShortPressThreshold)
	{
		if (TargetActor == nullptr)
		{
			// Move to cached destination and spawn cursor particle
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);	// working on NavMeshVolumn..
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
		}
	}

	FollowTime = 0.f;
}

ECreatureState AS1PlayerController::GetCreatureState()
{
	if (S1Player)
	{
		return S1Player->CreatureState;
	}

	return ECreatureState::None;
}

void AS1PlayerController::SetCreatureState(ECreatureState InState)
{
	if (S1Player)
	{
		S1Player->CreatureState = InState;
	}
}
