// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "S1Object.generated.h"

/**
 * 
 */
UCLASS()
class S1_API US1Object : public UObject
{
	GENERATED_BODY()

public:
	int32 HP = 100;
	int32 MP = 50;
	float Speed = 3.5f;
	
};
