// Fill out your copyright notice in the Description page of Project Settings.


#include "S1PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "System/S1AssetManager.h"
#include "Data/S1InputData.h"
#include "S1GameplayTags.h"
#include "Character/S1Player.h"


AS1PlayerController::AS1PlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
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

	//if (auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	//{
	//	Subsystem->AddMappingContext(InputMappingContext, 0);	// InputMappingContext, priority
	//}
}

void AS1PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (const US1InputData* InputData = US1AssetManager::GetAssetByName<US1InputData>("InputData"))
	{
		UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

		auto Action1 = InputData->FindInputActionByTag(S1GameplayTags::Input_Action_Move);
		EnhancedInputComponent->BindAction(Action1, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);

		auto Action2 = InputData->FindInputActionByTag(S1GameplayTags::Input_Action_Turn);
		EnhancedInputComponent->BindAction(Action2, ETriggerEvent::Triggered, this, &ThisClass::Input_Turn);

		auto Action3 = InputData->FindInputActionByTag(S1GameplayTags::Input_Action_Jump);
		EnhancedInputComponent->BindAction(Action3, ETriggerEvent::Triggered, this, &ThisClass::Input_Jump);

		auto Action4 = InputData->FindInputActionByTag(S1GameplayTags::Input_Action_Attack);
		EnhancedInputComponent->BindAction(Action4, ETriggerEvent::Triggered, this, &ThisClass::Input_Attack);
	}

	//if (auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	//{
	//	EnhancedInputComponent->BindAction(TestAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Test);
	//	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	//	EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Turn);
	//}
}

void AS1PlayerController::Input_Move(const FInputActionValue& InputValue)
{
	FVector2D MovementVector = InputValue.Get<FVector2D>();

	if (MovementVector.X != 0)
	{
		//FVector Direction = FVector::ForwardVector * MovementVector.X;
		//GetPawn()->AddActorWorldOffset(Direction * 50.f);

		FRotator Rotator = GetControlRotation();
		FVector Direction = UKismetMathLibrary::GetForwardVector(FRotator(0, Rotator.Yaw, 0));
		GetPawn()->AddMovementInput(Direction, MovementVector.X);
	}

	if (MovementVector.Y != 0)
	{
		//FVector Direction = FVector::RightVector * MovementVector.Y;
		//GetPawn()->AddActorWorldOffset(Direction * 50.f);
		
		FRotator Rotator = GetControlRotation();
		FVector Direction = UKismetMathLibrary::GetRightVector(FRotator(0, Rotator.Yaw, 0));
		GetPawn()->AddMovementInput(Direction, MovementVector.Y);
	}
}

void AS1PlayerController::Input_Turn(const FInputActionValue& InputValue)
{
	float val = InputValue.Get<float>();
	AddYawInput(val);	// ** Apply at PlayerController
}

void AS1PlayerController::Input_Jump(const FInputActionValue& InputValue)
{
	if (AS1Character* TargetCharacter = Cast<AS1Character>(GetPawn()))
	{
		TargetCharacter->Jump();
	}
	
}

void AS1PlayerController::Input_Attack(const FInputActionValue& InputValue)
{
	UE_LOG(LogS1, Log, TEXT("Input_Attack"));
}
