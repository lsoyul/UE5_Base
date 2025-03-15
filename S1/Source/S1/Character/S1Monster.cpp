// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/S1Monster.h"
#include "AbilitySystem/S1AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/S1AttributeSetMonster.h"

AS1Monster::AS1Monster()
{
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	AbilitySystemComponent = CreateDefaultSubobject<US1AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<US1AttributeSetMonster>("AttributeSetMonster");
}

// Called when the game starts or when spawned
void AS1Monster::BeginPlay()
{
	Super::BeginPlay();

	InitAbilitySystem();
}

// Called every frame
void AS1Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AS1Monster::InitAbilitySystem()
{
	Super::InitAbilitySystem();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
