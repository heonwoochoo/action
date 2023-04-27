// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HeadUpText.generated.h"

class UTextBlock;
class UWidgetAnimation;

UCLASS()
class PORTFOLIO_API UHeadUpText : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ShowingText;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FloatUp;

public:
	void SetShowingText(const FText& InText, const FColor& Color);

};
