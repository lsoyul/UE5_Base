// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "S1AssetManager.generated.h"

/**
 * 
 */
UCLASS()
class S1_API US1AssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	US1AssetManager();

	static US1AssetManager& Get();

	// TODO

};
