// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "S1PlayerState.generated.h"

class US1AbilitySystemComponent;
class US1AttributeSetPlayer;

/**
 * 
 */
UCLASS()
class S1_API AS1PlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AS1PlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	US1AbilitySystemComponent* GetS1AbilitySystemComponent() const;
	US1AttributeSetPlayer* GetS1AttributeSetPlayer() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<US1AbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<US1AttributeSetPlayer> AttributeSetPlayer;
};
