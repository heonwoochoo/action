// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "EnemyHPBarWidgetComponent.generated.h"

class UEnemyHPBarWidget;

UCLASS()
class PORTFOLIO_API UEnemyHPBarWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
protected:
	UEnemyHPBarWidget* HPBarWidget;

public:
	virtual void BeginPlay() override;
};
