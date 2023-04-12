// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionsMenu.generated.h"

class UButton;
class UImage;
class UTexture2D;

UCLASS()
class PORTFOLIO_API UOptionsMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* BackButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ArrowLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* ActivedArrowLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* DeactivedArrowLeft;

	void OnHoveredBackButton();
	void OnUnhoveredBackButton();

};
