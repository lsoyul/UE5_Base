// Fill out your copyright notice in the Description page of Project Settings.


#include "S1Character.h"
#include "S1Define.h"

// Sets default values
AS1Character::AS1Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AS1Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AS1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AS1Character::HandleGameplayEvent(FGameplayTag EventTag)
{
}

void AS1Character::Highlight()
{
	bHighlighted = true;
}

void AS1Character::UnHighlight()
{
	bHighlighted = false;
}

void AS1Character::OnDamaged(int32 Damage, TObjectPtr<AS1Character> Attacker)
{
	Hp = FMath::Clamp(Hp - Damage, 0, MaxHp);
	if (Hp == 0)
	{
		OnDead(Attacker);
	}

	D(FString::Printf(TEXT("%d"), Hp));
}

void AS1Character::OnDead(TObjectPtr<AS1Character> Attacker)
{
	if (CreatureState == ECreatureState::Dead)
		return;

	CreatureState = ECreatureState::Dead;
}

