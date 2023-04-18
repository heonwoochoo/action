// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/TwoButtonWidget.h"
#include "ReturnQuestionBox.generated.h"

class UExitBox;

UCLASS()
class PORTFOLIO_API UReturnQuestionBox : public UTwoButtonWidget
{
	GENERATED_BODY()
	
protected:

	virtual void OnClickedOKButton() override;

	virtual void OnClickedCancelButton() override;

private:
	// 부모 메뉴
	UExitBox* ExitBox;

public:
	void SetExitBox(UExitBox* InExitBox);

};
