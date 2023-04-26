// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GuideMessage.generated.h"

class UTextBlock;

UCLASS()
class PORTFOLIO_API UGuideMessage : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* GuideText;

public:
	void ShowGuideMessage(const FText& Message);
	void HideGuideMessage();
};
