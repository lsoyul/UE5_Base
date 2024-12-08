// Fill out your copyright notice in the Description page of Project Settings.


#include "S1AssetManager.h"
#include "S1LogChannels.h"

US1AssetManager::US1AssetManager() : Super()
{
}

US1AssetManager& US1AssetManager::Get()
{
	if (US1AssetManager* Singleton = Cast<US1AssetManager>(GEngine->AssetManager))
	{
		return *Singleton;
	}

	UE_LOG(LogS1, Fatal, TEXT("Can't find US1AssetManager"));

	return *NewObject<US1AssetManager>();
}
