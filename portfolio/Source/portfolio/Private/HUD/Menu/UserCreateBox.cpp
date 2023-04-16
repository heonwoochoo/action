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
}

void UUserCreateBox::OnClickedOKButton()
{
	Super::OnClickedOKButton();

	if (UsernameTextBox)
	{
		CheckExistUserName(UsernameTextBox->GetText());

		if (StartMenu && bIsValidUserName)
		{
			StartMenu->AddUser(UsernameTextBox->GetText());
			RemoveFromParent();
		}
	}
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

void UUserCreateBox::SetStartMenu(UStartMenu* UserWidget)
{
	StartMenu = UserWidget;
}
