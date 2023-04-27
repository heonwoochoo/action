// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HeadUpWidget.generated.h"

class UStackBox;
class UHeadUpText;

UCLASS()
class PORTFOLIO_API UHeadUpWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UStackBox* TextStackBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UHeadUpText> ShowingTextClass;

public:
	// 텍스트 블록 생성
	void HandleHeadUpText(const FText& InText, const FColor& Color);
};
