// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/S1AbilitySystemComponent.h"

void US1AbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<class UGameplayAbility>>& StartupAbilities)
{
	for (auto& AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		FGameplayAbilitySpecHandle SpecHandle = GiveAbility(AbilitySpec);
		
		auto& a = ActivatableAbilities;

		//TryActivateAbility(SpecHandle);			// Ability 사용
		//GiveAbilityAndActivateOnce(AbilitySpec);	// Ability 부여 및 사용
		SpecHandles.Add(SpecHandle);
	}
}

void US1AbilitySystemComponent::ActivateAbility(FGameplayTag AbilityTag)
{
	for (FGameplayAbilitySpecHandle& SpecHandle : SpecHandles)
	{
		// TODO
		TryActivateAbility(SpecHandle);
	}
}
