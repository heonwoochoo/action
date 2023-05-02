// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BossHPBar.generated.h"

class UTextBlock;
class UProgressBar;
class UWidgetAnimation;

UCLASS()
class PORTFOLIO_API UBossHPBar : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* NameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* ShowProgressBar;

public:
	void SetName(const FText& InName);

	UFUNCTION()
	void OnChangedHP(const float& CurrentHp, const float& MaxHp);
};
