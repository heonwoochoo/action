// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/InGame/ReturnQuestionBox.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/Menu/InGame/ExitBox.h"
#include "GameInstance/DefaultGameInstance.h"

void UReturnQuestionBox::OnClickedOKButton()
{
	Super::OnClickedOKButton();

	UDefaultGameInstance* DefaultGameInstance = Cast<UDefaultGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (DefaultGameInstance)
	{
		DefaultGameInstance->OpenGameStartLevel();
	}
}

void UReturnQuestionBox::OnClickedCancelButton()
{
	if (ExitBox)
	{
		ExitBox->Activate();
	}

	Super::OnClickedCancelButton();
}

void UReturnQuestionBox::SetExitBox(UExitBox* InExitBox)
{
	ExitBox = InExitBox;
}
