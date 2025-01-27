// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/S1AnimInstance.h"
//#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/S1Player.h"

US1AnimInstance::US1AnimInstance(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void US1AnimInstance::NativeInitializeAnimation()
{
	/* Referred from AnimInstance default blueprint*/
	Super::NativeInitializeAnimation();

	Character = Cast<AS1Character>(TryGetPawnOwner());
	if (Character)
		MovementComponent = Character->GetCharacterMovement();
}

void US1AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	/* Referred from AnimInstance default blueprint*/
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Character == nullptr)
		return;
	if (MovementComponent == nullptr)
		return;

	Velocity = MovementComponent->Velocity;
	GroundSpeed = Velocity.Size2D();

	bShouldMove = (GroundSpeed > 3.f && MovementComponent->GetCurrentAcceleration() != FVector::ZeroVector);
	bIsFalling = MovementComponent->IsFalling();
}
