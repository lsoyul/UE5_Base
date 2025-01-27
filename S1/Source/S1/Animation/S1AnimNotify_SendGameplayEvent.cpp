// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/S1AnimNotify_SendGameplayEvent.h"
#include "Character/S1Character.h"

US1AnimNotify_SendGameplayEvent::US1AnimNotify_SendGameplayEvent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void US1AnimNotify_SendGameplayEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AS1Character* LocalCharacter = Cast<AS1Character>(MeshComp->GetOwner());
	if (LocalCharacter)
	{
		LocalCharacter->HandleGameplayEvent(EventTag);
	}
}

