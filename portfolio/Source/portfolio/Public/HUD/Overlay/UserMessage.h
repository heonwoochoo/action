// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserMessage.generated.h"

class UWidgetAnimation;
class UTextBlock;

UCLASS()
class PORTFOLIO_API UUserMessage : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;
	
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* ShowHideAnimation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* NotifyingText;

public:
	void NotifyMessageToUser(const FText& Message);

private:
	void PlayShowHideAnimation();
};
