// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyBase.h"
#include "MinionLane.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API AMinionLane : public AEnemyBase
{
	GENERATED_BODY()
	
public:
	AMinionLane();

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

protected:
	virtual void BeginPlay() override;

	virtual void AttackCharacter() override;
};
