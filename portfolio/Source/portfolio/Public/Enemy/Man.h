// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyBase.h"
#include "Man.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API AMan : public AEnemyBase
{
	GENERATED_BODY()
	
public:
	AMan();

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

protected:
	virtual void BeginPlay() override;

	virtual void AttackCharacter() override;
};
