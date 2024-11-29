// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "S1Actor.generated.h"

class US1Object;

UCLASS()
class S1_API AS1Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AS1Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	/*US1Object* Obj1;

	UPROPERTY()
	US1Object* Obj2;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Stat)
	int32 Hp = 100;

	UPROPERTY(VisibleAnywhere)
	int32 Mp = 50;
	
	UPROPERTY(VisibleAnywhere)
	float Speed = 3.5f;
};
