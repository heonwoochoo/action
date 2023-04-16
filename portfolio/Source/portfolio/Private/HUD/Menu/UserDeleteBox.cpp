// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/UserDeleteBox.h"
#include "HUD/Menu/StartMenu.h"
#include "Components/TextBlock.h"

void UUserDeleteBox::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUserDeleteBox::OnClickedOKButton()
{
	Super::OnClickedOKButton();

	if (StartMenu)
	{
		StartMenu->DeleteSelectedUser();
		StartMenu->SetEnableLoadButton(false);
		StartMenu->SetEnableDeleteButton(false);
	}

	RemoveFromParent();
}

void UUserDeleteBox::SetUserNameText(FText UserName)
{
	if (UsernameText)
	{
		UsernameText->SetText(UserName);
	}
}

void UUserDeleteBox::SetStartMenu(UStartMenu* UserWidget)
{
	StartMenu = UserWidget;
}
