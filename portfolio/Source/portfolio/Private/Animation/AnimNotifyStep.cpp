// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyStep.h"
#include "DefaultCharacter.h"
#include "Component/FootstepComponent.h"

void UAnimNotifyStep::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	ADefaultCharacter* Character = Cast<ADefaultCharacter>(MeshComp->GetOwner());
	if (Character)
	{
		UFootstepComponent* FootstepComponent = Character->GetFootstepComponent();
		if (FootstepComponent)
		{
			FootstepComponent->HandleFootstep(Foot);
		}
	}
}