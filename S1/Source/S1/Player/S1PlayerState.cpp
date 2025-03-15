// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/S1PlayerState.h"
#include "AbilitySystem/S1AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/S1AttributeSetPlayer.h"

AS1PlayerState::AS1PlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<US1AbilitySystemComponent>("AbilitySystemComponent");
	AttributeSetPlayer = CreateDefaultSubobject<US1AttributeSetPlayer>("AttributeSetPlayer");
} 

UAbilitySystemComponent* AS1PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

US1AbilitySystemComponent* AS1PlayerState::GetS1AbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

US1AttributeSetPlayer* AS1PlayerState::GetS1AttributeSetPlayer() const
{
	return AttributeSetPlayer;
}
