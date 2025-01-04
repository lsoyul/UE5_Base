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

void AS1PlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void AS1PlayerController::OnSetDestinationTriggered()
{
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
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0f, false);
	}
}

void AS1PlayerController::OnSetDestinationReleased()
{
	// If it was short press
	if (FollowTime <= ShortPressThreshold)
	{
		// Move to cached destination and spawn cursor particle
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);	// working on NavMeshVolumn..
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}
