// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/InGame/ExitBox.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/DefaultGameMode.h"
#include "HUD/Menu/InGame/ExitQuestionBox.h"
#include "Components/Overlay.h"
#include "HUD/Menu/InGame/ReturnQuestionBox.h"
#include "Controller/CharacterController.h"
#include "DefaultCharacter.h"

void UExitBox::NativeConstruct()
{
	InitReturnSMenuButton();
	InitExitGameButton();
	InitCancelButton();

	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController)
	{
		CharacterController->OnChangedInputMode.AddDynamic(this, &UExitBox::OnChangedInputMode);
	}
}

void UExitBox::NativeDestruct()
{
	Super::NativeDestruct();

	// 인풋모드 변경
	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController)
	{
		CharacterController->SetInputModeToGame();
	}

	// 오픈 상태 변수 변경
	ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (DefaultCharacter)
	{
		DefaultCharacter->SetIsMouseShowing(false);
	}
}

void UExitBox::OnHoveredReturnSMenuButton()
{
	if (ActivatedBox && ReturnSMenuImage)
	{
		ReturnSMenuImage->SetBrushFromTexture(ActivatedBox);
	}
}

void UExitBox::OnUnhoveredReturnSMenuButton()
{
	if (DeactivatedBox && ReturnSMenuImage)
	{
		ReturnSMenuImage->SetBrushFromTexture(DeactivatedBox);
	}
}

void UExitBox::OnClickedReturnSMenuButton()
{
	if (ReturnQuestionBoxClass)
	{
		ReturnQuestionBox = Cast<UReturnQuestionBox>(CreateWidget(this, ReturnQuestionBoxClass));
		if (ReturnQuestionBox)
		{
			ReturnQuestionBox->AddToViewport();
			ReturnQuestionBox->SetExitBox(this);
			Deactivate();
		}
	}
	PlayButtonSound();
}

void UExitBox::OnHoveredExitGameButton()
{
	if (ActivatedBox && ExitGamelImage)
	{
		ExitGamelImage->SetBrushFromTexture(ActivatedBox);
	}
}

void UExitBox::OnUnhoveredExitGameButton()
{
	if (DeactivatedBox && ExitGamelImage)
	{
		ExitGamelImage->SetBrushFromTexture(DeactivatedBox);
	}
}

void UExitBox::OnClickedExitGameButton()
{
	if (ExitQuestionBoxClass)
	{
		ExitQuestionBox = Cast<UExitQuestionBox>(CreateWidget(this, ExitQuestionBoxClass));
		if (ExitQuestionBox)
		{
			ExitQuestionBox->AddToViewport();
			ExitQuestionBox->SetExitBox(this);
			Deactivate();
		}
	}

	PlayButtonSound();
}

void UExitBox::OnHoveredCancelButton()
{
	if (ActivatedBox && CancelImage)
	{
		CancelImage->SetBrushFromTexture(ActivatedBox);
	}
}

void UExitBox::OnUnhoveredCancelButton()
{
	if (DeactivatedBox && CancelImage)
	{
		CancelImage->SetBrushFromTexture(DeactivatedBox);
	}
}

void UExitBox::OnClickedCancelButton()
{
	RemoveFromParent();
	PlayButtonSound();
}

void UExitBox::InitReturnSMenuButton()
{
	if (ReturnSMenuButton)
	{
		ReturnSMenuButton->OnHovered.AddDynamic(this, &UExitBox::OnHoveredReturnSMenuButton);
		ReturnSMenuButton->OnUnhovered.AddDynamic(this, &UExitBox::OnUnhoveredReturnSMenuButton);
		ReturnSMenuButton->OnClicked.AddDynamic(this, &UExitBox::OnClickedReturnSMenuButton);
	}
}

void UExitBox::InitExitGameButton()
{
	if (ExitGameButton)
	{
		ExitGameButton->OnHovered.AddDynamic(this, &UExitBox::OnHoveredExitGameButton);
		ExitGameButton->OnUnhovered.AddDynamic(this, &UExitBox::OnUnhoveredExitGameButton);
		ExitGameButton->OnClicked.AddDynamic(this, &UExitBox::OnClickedExitGameButton);
	}
}

void UExitBox::InitCancelButton()
{
	if (CancelButton)
	{
		CancelButton->OnHovered.AddDynamic(this, &UExitBox::OnHoveredCancelButton);
		CancelButton->OnUnhovered.AddDynamic(this, &UExitBox::OnUnhoveredCancelButton);
		CancelButton->OnClicked.AddDynamic(this, &UExitBox::OnClickedCancelButton);
	}
}

void UExitBox::PlayButtonSound()
{
	ADefaultGameMode* DefaultGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this));
	if (DefaultGameMode)
	{
		DefaultGameMode->PlayCheckButtonClickSound();
	}
}

void UExitBox::RemoveExitQuestionBox()
{
	if (ExitQuestionBox)
	{
		ExitQuestionBox->RemoveFromParent();
	}

	if (ReturnQuestionBox)
	{
		ReturnQuestionBox->RemoveFromParent();
	}
}

void UExitBox::Deactivate()
{
	SetIsEnabled(false);
	if (ExitBoxOverlay)
	{
		ExitBoxOverlay->SetRenderOpacity(0.3f);
	}
}

void UExitBox::Activate()
{
	SetIsEnabled(true);
	if (ExitBoxOverlay)
	{
		ExitBoxOverlay->SetRenderOpacity(1.f);
	}
}

void UExitBox::OnChangedInputMode(const EInputMode& Mode)
{
	if (Mode == EInputMode::EIM_Game)
	{
		RemoveFromParent();
	}
}