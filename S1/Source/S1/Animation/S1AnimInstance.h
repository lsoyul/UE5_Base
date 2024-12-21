// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "S1AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class S1_API US1AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	US1AnimInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AS1Player> Character;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UCharacterMovementComponent> MovementComponent;

protected:
	UPROPERTY(BlueprintReadOnly)
	FVector Velocity = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly)
	float GroundSpeed = 0.f;

	UPROPERTY(BlueprintReadOnly)
	bool bShouldMove = false;

	UPROPERTY(BlueprintReadOnly)
	bool bIsFalling = false;

};
