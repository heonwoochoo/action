// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/InGame/ExitQuestionBox.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/Menu/InGame/ExitBox.h"

void UExitQuestionBox::OnClickedOKButton()
{
	Super::OnClickedOKButton();

	// 게임종료
	UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(this, 0), EQuitPreference::Quit, false);
}

void UExitQuestionBox::OnClickedCancelButton()
{
	if (ExitBox)
	{
		ExitBox->Activate();
	}

	Super::OnClickedCancelButton();
}

void UExitQuestionBox::SetExitBox(UExitBox* InExitBox)
{
	ExitBox = InExitBox;
}
