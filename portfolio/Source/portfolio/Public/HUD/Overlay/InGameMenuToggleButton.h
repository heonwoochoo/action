// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameMenuToggleButton.generated.h"


class UWidgetAnimation;
class UButton;
class UImage;
class UTexture2D;

UCLASS()
class PORTFOLIO_API UInGameMenuToggleButton : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* ShowOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ToggleButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ToggleButtonImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Texture")
	UTexture2D* ActivatedRightArrow;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Texture")
	UTexture2D* DeactivatedRightArrow;

	UFUNCTION()
	void OnHoveredToggleButton();

	UFUNCTION()
	void OnUnhoveredToggleButton();

	UFUNCTION()
	void OnClickedToggleButton();

private:
	void InitToggleButton();
};
