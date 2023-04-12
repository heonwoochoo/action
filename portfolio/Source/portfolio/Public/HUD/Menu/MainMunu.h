// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMunu.generated.h"

class UButton;
class UImage;
class UTexture2D;

UCLASS()
class PORTFOLIO_API UMainMunu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* StartButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* StartButtonImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* OptionsButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* OptionsButtonImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* CreditsButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* CreditsButtonImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* QuitButtonImage;

	UFUNCTION()
	void OnHoveredStartButton();

	UFUNCTION()
	void OnUnhoveredStartButton();

	UFUNCTION()
	void OnHoveredOptionsButton();

	UFUNCTION()
	void OnUnhoveredOptionsButton();

	UFUNCTION()
	void OnHoveredCreditsButton();

	UFUNCTION()
	void OnUnhoveredCreditsButton();

	UFUNCTION()
	void OnHoveredQuitButton();

	UFUNCTION()
	void OnUnhoveredQuitButton();
};
