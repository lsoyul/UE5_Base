// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "S1PlayerController.generated.h"

struct FInputActionValue;
class UNiagaraSystem;
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
	/** Input handlers for SetDestination action **/
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();

public:
	/** Time threshold to know if it was short press **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold = 0.3f;

	/** Fx class that we will spawn when clicking **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UNiagaraSystem> FXCursor;

private:
	FVector CachedDestination;
	float FollowTime; // For how long it has been pressed
};
