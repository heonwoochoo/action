// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProgressBarContainer.generated.h"


class UTextBlock;
class UProgressBar;


UCLASS()
class PORTFOLIO_API UProgressBarContainer : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* HpCurrent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* HpMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* HPProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* StaminaCurrent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* StaminaMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* StaminaProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* ExpProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* LevelText;

public:
	void Init();

	UFUNCTION()
	void UpdateHealth(const float& CurrentHp, const float& MaxHp);

	UFUNCTION()
	void UpdateStamina(const float& CurrentSp, const float& MaxSp);

	UFUNCTION()
	void UpdateExp(const float& CurrentExp, const float& MaxExp);

	UFUNCTION()
	void UpdateLevel(const int32& NewLevel);
};
