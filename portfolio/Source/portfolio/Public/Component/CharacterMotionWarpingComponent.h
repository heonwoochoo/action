// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MotionWarpingComponent.h"
#include "CharacterMotionWarpingComponent.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UCharacterMotionWarpingComponent : public UMotionWarpingComponent
{
	GENERATED_BODY()
	
public:
	UCharacterMotionWarpingComponent(const FObjectInitializer& ObjectInitializer);

	virtual void InitializeComponent() override;
};
