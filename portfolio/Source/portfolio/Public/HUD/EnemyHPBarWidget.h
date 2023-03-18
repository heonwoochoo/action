// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHPBarWidget.generated.h"

class UProgressBar;

UCLASS()
class PORTFOLIO_API UEnemyHPBarWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HPBar;
};
