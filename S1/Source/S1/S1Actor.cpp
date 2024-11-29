// Fill out your copyright notice in the Description page of Project Settings.


#include "S1Actor.h"
#include "S1Object.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
// CDO와 연관된 부분만 초기화 하는것을 권장.
// 게임로직 관련 초기화는 BeginPlay쪽에서..
AS1Actor::AS1Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> FindMesh(TEXT("/Script/Engine.StaticMesh'/Game/_Trycatch/SM_ChamferCube.SM_ChamferCube'"));
	if (FindMesh.Succeeded())
	{
		Box->SetStaticMesh(FindMesh.Object);
	}
}

// Called when the game starts or when spawned
void AS1Actor::BeginPlay()
{
	Super::BeginPlay();

	//Obj1 = NewObject<US1Object>();
	//Obj2 = NewObject<US1Object>();

	//GEngine->ForceGarbageCollection(true);
}

// Called every frame
void AS1Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}