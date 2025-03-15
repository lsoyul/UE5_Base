// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/S1HpBarWidget.h"
#include "Components/ProgressBar.h"

US1HpBarWidget::US1HpBarWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void US1HpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void US1HpBarWidget::SetHpRatio(float Ratio)
{
	if (HpBar)
	{
		HpBar->SetPercent(Ratio);
	}
}
