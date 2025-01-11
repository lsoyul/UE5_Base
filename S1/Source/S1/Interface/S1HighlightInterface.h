// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "S1HighlightInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class US1HighlightInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class S1_API IS1HighlightInterface
{
	GENERATED_BODY()

public:
	virtual void Highlight() = 0;
	virtual void UnHighlight() = 0;
};
