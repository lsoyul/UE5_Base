// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/S1HighlightInterface.h"
#include "S1Define.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemInterface.h"
#include "S1Character.generated.h"

UCLASS()
class S1_API AS1Character : public ACharacter, public IS1HighlightInterface, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AS1Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void HandleGameplayEvent(FGameplayTag EventTag);

public:
	virtual void Highlight() override;
	virtual void UnHighlight() override;

	virtual void OnDamaged(int32 Damage, TObjectPtr<AS1Character> Attacker);
	virtual void OnDead(TObjectPtr<AS1Character> Attacker);

	void RefreshHpBarRatio();

protected:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void InitAbilitySystem();

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;

public:
	UPROPERTY(BlueprintReadWrite)
	ECreatureState CreatureState = ECreatureState::Moving;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UWidgetComponent> HpBarComponent;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class US1AbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class US1AttributeSet> AttributeSet;

public:
	void AddCharacterAbilities();

	UPROPERTY(EditAnywhere, Category=Abilities)
	TArray<TSubclassOf<class UGameplayAbility>> StartupAbilities;
};
