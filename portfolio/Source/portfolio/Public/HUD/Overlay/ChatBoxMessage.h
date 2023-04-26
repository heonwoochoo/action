// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChatBoxMessage.generated.h"

class UTextBlock;

UCLASS()
class PORTFOLIO_API UChatBoxMessage : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TimeText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MessageText;

private:
	FText GetFormatTimeText(const FDateTime& Time);

public:
	void SetMessageText(const FText& Message);

	void SetTextColor(const FColor& Color);
};
