// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "TargetWidgetComponent.generated.h"

class UTargetWidget;

UCLASS()
class PORTFOLIO_API UTargetWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	UTargetWidget* TargetWidget;
	
	virtual void BeginPlay() override;

	void SetTargetVisible(bool visible);
};
