// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/BossBase.h"
#include "BossGideon.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API ABossGideon : public ABossBase
{
	GENERATED_BODY()
	
public:
	ABossGideon();

protected:
	virtual void BeginPlay() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual void Tick(float DeltaTime) override;
};
