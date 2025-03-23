// Fill out your copyright notice in the Description page of Project Settings.


#include "S1Character.h"
#include "S1Define.h"
#include "Components/WidgetComponent.h"
#include "UI/S1HpBarWidget.h"
#include "AbilitySystem/S1AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/S1AttributeSet.h"

// Sets default values
AS1Character::AS1Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HpBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HpBarComponent->SetupAttachment(GetRootComponent());

	ConstructorHelpers::FClassFinder<UUserWidget> HealthBarWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/WBP_HpBar.WBP_HpBar_C'"));
	if (HealthBarWidgetClass.Succeeded())
	{
		HpBarComponent->SetWidgetClass(HealthBarWidgetClass.Class);
		HpBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
		HpBarComponent->SetDrawAtDesiredSize(true);
		HpBarComponent->SetRelativeLocation(FVector(0, 0, 100));
	}
}

// Called when the game starts or when spawned
void AS1Character::BeginPlay()
{
	Super::BeginPlay();
	RefreshHpBarRatio();

	AddCharacterAbilities();
}

// Called every frame
void AS1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AS1Character::HandleGameplayEvent(FGameplayTag EventTag)
{
}

void AS1Character::Highlight()
{
	bHighlighted = true;
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(250);
}

void AS1Character::UnHighlight()
{
	bHighlighted = false;
	GetMesh()->SetRenderCustomDepth(false);
}

void AS1Character::OnDamaged(int32 Damage, TObjectPtr<AS1Character> Attacker)
{
	float Hp = AttributeSet->GetHealth();
	float MaxHp = AttributeSet->GetMaxHealth();

	Hp = FMath::Clamp(Hp - Damage, 0, MaxHp);
	AttributeSet->SetHealth(Hp);

	if (Hp == 0)
	{
		OnDead(Attacker);
	}

	//D(FString::Printf(TEXT("%d"), Hp));
	RefreshHpBarRatio();
}

void AS1Character::OnDead(TObjectPtr<AS1Character> Attacker)
{
	if (CreatureState == ECreatureState::Dead)
		return;

	CreatureState = ECreatureState::Dead;
}

void AS1Character::RefreshHpBarRatio()
{
	if (HpBarComponent && AttributeSet)
	{
		float Hp = AttributeSet->GetHealth();
		float MaxHp = AttributeSet->GetMaxHealth();
		float Ratio = static_cast<float>(Hp) / MaxHp;
		US1HpBarWidget* HpBar =	Cast<US1HpBarWidget>(HpBarComponent->GetUserWidgetObject());
		HpBar->SetHpRatio(Ratio);
	}
}

UAbilitySystemComponent* AS1Character::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
} 

void AS1Character::InitAbilitySystem()
{

}

void AS1Character::AddCharacterAbilities()
{
	 US1AbilitySystemComponent* ASC = Cast<US1AbilitySystemComponent>(AbilitySystemComponent);
	 if (ASC == nullptr)
	 {
		 return;
	 }

	 ASC->AddCharacterAbilities(StartupAbilities);
}
