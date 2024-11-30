// Fill out your copyright notice in the Description page of Project Settings.


#include "MainActor.h"
#include "S1Actor.h"

// Sets default values
AMainActor::AMainActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<AS1Actor> FindClass(TEXT("/Script/Engine.Blueprint'/Game/_Trycatch/BP_S1Actor.BP_S1Actor_C'"));
	if (FindClass.Succeeded())
	{
		ActorClass = FindClass.Class;
	}
}

// Called when the game starts or when spawned
void AMainActor::BeginPlay()
{
	Super::BeginPlay();

	FVector Location(0, 0, 0);
	FRotator Rotation(0, 0, 0);
	
	//Actor = GetWorld()->SpawnActor<AS1Actor>(Location, Rotation);
	
	// equevalant with dynamic_cast
	Actor = Cast<AS1Actor>(GetWorld()->SpawnActor(ActorClass));
	Actor->SetLifeSpan(5.0f);
	//GetWorld()->DestroyActor(Actor);
}

// Called every frame
void AMainActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

