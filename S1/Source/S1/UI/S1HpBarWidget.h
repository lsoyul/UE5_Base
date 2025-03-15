// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S1HpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class S1_API US1HpBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	US1HpBarWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void NativeConstruct() override;

public:
	void SetHpRatio(float Ratio);

protected:
	UPROPERTY(meta=(BindWidget), BlueprintReadWrite)
	TObjectPtr<class UProgressBar> HpBar;
};
