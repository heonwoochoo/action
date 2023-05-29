// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/SettingTypes.h"
#include "SavedNotifyBox.generated.h"

class UButton;
class UImage;
class UTexture2D;

UCLASS()
class PORTFOLIO_API USavedNotifyBox : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	// 텍스쳐
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* ActivatedBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* DeactivatedBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* OKImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* OKButton;

	UFUNCTION()
	void OnHoveredOKButton();

	UFUNCTION()
	void OnUnhoveredOKButton();

	UFUNCTION()
	virtual void OnClickedOKButton();

private:
	void InitOKButton();

public:
	UFUNCTION()
	void OnChangedInputMode(const EInputMode& Mode);
};
