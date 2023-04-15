// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/UserCreateBox.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/DefaultGameMode.h"
#include "HUD/Menu/StartMenu.h"

void UUserCreateBox::NativeConstruct()
{
	Super::NativeConstruct();

	InitUsernameTextBox();
	InitOKButton();
	InitCancelButton();
}

void UUserCreateBox::OnHoveredOKButton()
{
	if (ActivatedBox && OKImage)
	{
		OKImage->SetBrushFromTexture(ActivatedBox);
	}
}

void UUserCreateBox::OnUnhoveredOKButton()
{
	if (DeactivatedBox && OKImage)
	{
		OKImage->SetBrushFromTexture(DeactivatedBox);
	}
}

void UUserCreateBox::OnClickedOKButton()
{
	if (UsernameTextBox)
	{
		CheckExistUserName(UsernameTextBox->GetText());

		if (StartMenu && bIsValidUserName)
		{
			StartMenu->AddUser(UsernameTextBox->GetText());
			RemoveFromParent();
		}
	}

	PlayButtonSound();
}

void UUserCreateBox::OnHoveredCancelButton()
{
	if (ActivatedBox && CancelImage)
	{
		CancelImage->SetBrushFromTexture(ActivatedBox);
	}
}

void UUserCreateBox::OnUnhoveredCancelButton()
{
	if (DeactivatedBox && CancelImage)
	{
		CancelImage->SetBrushFromTexture(DeactivatedBox);
	}
}

void UUserCreateBox::OnClickedCancelButton()
{
	RemoveFromParent();

	PlayButtonSound();
}

void UUserCreateBox::OnChangedEnterText(const FText& Text)
{
	CheckIsValidUserName(Text);
}

void UUserCreateBox::CheckIsValidUserName(const FText& Text)
{
	if (!ErrorMessageText) return;

	FString InputText = Text.ToString();

	int32 TextLength = InputText.Len();

	// 글자수 미달
	if (TextLength < MinUserNameLength)
	{
		ErrorMessageText->SetText(FText::FromName(ShortLengthMessage));
		bIsValidUserName = false;
		return;
	}

	// 글자수 초과
	if (InputText.Len() > MaxUserNameLength)
	{
		ErrorMessageText->SetText(FText::FromName(ExceedMaxLengthMessage));
		bIsValidUserName = false;
		return;
	}

	for (auto& c : InputText)
	{
		if (isspace(c))
		{
			// 공백 포함
			ErrorMessageText->SetText(FText::FromName(WhiteSpaceMessage));
			bIsValidUserName = false;
			return;
		}
		else if (!isalpha(c))
		{
			// 영문 아님
			ErrorMessageText->SetText(FText::FromName(NeedAlphaMessage));
			bIsValidUserName = false;
			return;
		}
	}

	ErrorMessageText->SetText(FText::FromName(" "));
	bIsValidUserName = true;
}

void UUserCreateBox::CheckExistUserName(const FText& Text)
{
	bool IsExist = UGameplayStatics::DoesSaveGameExist(Text.ToString(), 0);
	if (IsExist)
	{
		bIsValidUserName = false;
		if (ErrorMessageText)
		{
			ErrorMessageText->SetText(FText::FromName(ExistNameMessage));
		}
	}
	else
	{
		bIsValidUserName = true;
	}
}

void UUserCreateBox::InitUsernameTextBox()
{
	if (UsernameTextBox)
	{
		UsernameTextBox->OnTextChanged.AddDynamic(this, &UUserCreateBox::OnChangedEnterText);
		CheckIsValidUserName(UsernameTextBox->GetText());
	}
}

void UUserCreateBox::InitOKButton()
{
	if (OKButton)
	{
		OKButton->OnHovered.AddDynamic(this, &UUserCreateBox::OnHoveredOKButton);
		OKButton->OnUnhovered.AddDynamic(this, &UUserCreateBox::OnUnhoveredOKButton);
		OKButton->OnClicked.AddDynamic(this, &UUserCreateBox::OnClickedOKButton);
	}
}

void UUserCreateBox::InitCancelButton()
{
	if (CancelButton)
	{
		CancelButton->OnHovered.AddDynamic(this, &UUserCreateBox::OnHoveredCancelButton);
		CancelButton->OnUnhovered.AddDynamic(this, &UUserCreateBox::OnUnhoveredCancelButton);
		CancelButton->OnClicked.AddDynamic(this, &UUserCreateBox::OnClickedCancelButton);
	}
}

void UUserCreateBox::PlayButtonSound()
{
	ADefaultGameMode* DefaultGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this));
	if (DefaultGameMode)
	{
		DefaultGameMode->PlayCheckButtonClickSound();
	}
}

void UUserCreateBox::SetStartMenu(UStartMenu* UserWidget)
{
	StartMenu = UserWidget;
}
