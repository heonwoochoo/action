// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDBase.generated.h"

class AEnemyBase;

UCLASS()
class PORTFOLIO_API AHUDBase : public AHUD
{
	GENERATED_BODY()
	
public:
	AHUDBase();

protected:
	virtual void Tick(float DeltaSeconds) override;

public:
};
