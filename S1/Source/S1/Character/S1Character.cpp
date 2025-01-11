// Fill out your copyright notice in the Description page of Project Settings.


#include "S1Character.h"

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

void AS1Character::Highlight()
{
	bHighlighted = true;
}

void AS1Character::UnHighlight()
{
	bHighlighted = false;
}

