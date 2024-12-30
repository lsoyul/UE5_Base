// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "S1PlayerController.generated.h"

struct FInputActionValue;

/**
 * 
 */
UCLASS()
class S1_API AS1PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AS1PlayerController(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void Input_Move(const FInputActionValue& InputValue);
	void Input_Turn(const FInputActionValue& InputValue);
	void Input_Jump(const FInputActionValue& InputValue);
	void Input_Attack(const FInputActionValue& InputValue);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAnimMontage> AttackMontage;

protected:
	/*
	UPROPERTY(EditAnywhere, Category=Input)
	TObjectPtr<class UInputMappingContext> InputMappingContext;
	
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> TestAction;
	
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> TurnAction;
	*/
};
