// Fill out your copyright notice in the Description page of Project Settings.


#include "S1Actor.h"

// Sets default values
AS1Actor::AS1Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AS1Actor::BeginPlay()
{
	Super::BeginPlay();
	Hp++;
}

// Called every frame
void AS1Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

