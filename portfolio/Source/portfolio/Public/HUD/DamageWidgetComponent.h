// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DamageWidgetComponent.generated.h"

class UDamageTextWidget;

UCLASS()
class PORTFOLIO_API UDamageWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDamageTextWidget* DamageTextWidget;


public:
	void SetDamageText(float Damage);
};
