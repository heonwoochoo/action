// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/TwoButtonWidget.h"
#include "UserDeleteBox.generated.h"

class UTexture2D;
class UStartMenu;

UCLASS()
class PORTFOLIO_API UUserDeleteBox : public UTwoButtonWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* UsernameText;

	virtual void OnClickedOKButton() override;

private:
	// StartMenu 인스턴스
	UStartMenu* StartMenu;

public:
	void SetUserNameText(FText UserName);

	void SetStartMenu(UStartMenu* UserWidget);
};
