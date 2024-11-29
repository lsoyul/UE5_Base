// Copyright Epic Games, Inc. All Rights Reserved.

#include "S1.h"
#include "Modules/ModuleManager.h"

#include "S1LogChannels.h"

class FS1Module : public FDefaultGameModuleImpl
{
	virtual void StartupModule() override
	{
		//UE_LOG(LogTemp, Log, TEXT("Hello World"));
		UE_LOG(LogS1, Log, TEXT("Hello World"));
	}

	virtual void ShutdownModule() override
	{

	}
};

IMPLEMENT_PRIMARY_GAME_MODULE( FS1Module, S1, "S1" );
