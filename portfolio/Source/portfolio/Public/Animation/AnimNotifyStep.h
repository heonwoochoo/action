// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Types/CharacterTypes.h"
#include "AnimNotifyStep.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UAnimNotifyStep : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
	// 발의 방향
	UPROPERTY(EditAnywhere)
	EFoot Foot;

	// 움직임의 종류
	UPROPERTY(EditAnywhere)
	EMovementType MovementType;
};
