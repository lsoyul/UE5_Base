// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/S1Monster.h"

AS1Monster::AS1Monster()
{
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
}

// Called when the game starts or when spawned
void AS1Monster::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AS1Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}