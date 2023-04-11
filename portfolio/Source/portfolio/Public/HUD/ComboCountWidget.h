// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ComboCountWidget.generated.h"

class UTextBlock;
class UWidgetAnimation;

UCLASS()
class PORTFOLIO_API UComboCountWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ComboCountText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetAnimation* AnimShowText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetAnimation* AnimHideText;



public:
	void SetComboCount(int32 Count);

	void PlayShowAnimation();
	void PlayHideAnimation();

	FWidgetAnimationDynamicEvent EndAnimationEvent;

	UFUNCTION()
	void EndHideAnimation();

	UFUNCTION()
	void VisibilityChanged(ESlateVisibility InVisibility);
};
