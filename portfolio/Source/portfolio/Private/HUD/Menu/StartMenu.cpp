// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/StartMenu.h"
#include "Components/StackBox.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "HUD/Menu/UserCreateBox.h"
#include "HUD/Menu/SavedUser.h"

void UStartMenu::NativeConstruct()
{
	Super::NativeConstruct();

	InitNewButton();
	InitLoadButton();
	InitDeleteButton();
}

void UStartMenu::OnHoveredNewButton()
{
	if (NewImage && ActivatedBox)
	{
		NewImage->SetBrushFromTexture(ActivatedBox);
	}
}

void UStartMenu::OnUnhoveredNewButton()
{
	if (NewImage && DeactivatedBox)
	{
		NewImage->SetBrushFromTexture(DeactivatedBox);
	}
}

void UStartMenu::OnClickedNewButton()
{
	UserCreateBox = Cast<UUserCreateBox>(CreateWidget(this, UserCreateBoxClass));
	if (UserCreateBox)
	{
		UserCreateBox->AddToViewport(1);
		UserCreateBox->SetStartMenu(this);
	}

	PlayButtonSound();
}

void UStartMenu::OnHoveredLoadButton()
{
	if (LoadImage && ActivatedBox)
	{
		LoadImage->SetBrushFromTexture(ActivatedBox);
	}
}

void UStartMenu::OnUnhoveredLoadButton()
{
	if (LoadImage && DeactivatedBox)
	{
		LoadImage->SetBrushFromTexture(DeactivatedBox);
	}
}

void UStartMenu::OnClickedLoadButton()
{
	PlayButtonSound();
}

void UStartMenu::OnHoveredDeleteButton()
{
	if (DeleteImage && ActivatedBox)
	{
		DeleteImage->SetBrushFromTexture(ActivatedBox);
	}
}

void UStartMenu::OnUnhoveredDeleteButton()
{
	if (DeleteImage && DeactivatedBox)
	{
		DeleteImage->SetBrushFromTexture(DeactivatedBox);
	}
}

void UStartMenu::OnClickedDeleteButton()
{
	SavedUserList.Remove(SelectedUser);
	SelectedUser->RemoveFromParent();

	for (int32 i = 0; i < SavedUserList.Num(); ++i)
	{
		SavedUserList[i]->SetListNumber(i + 1);
	}

	PlayButtonSound();
}

void UStartMenu::OnClickedBackButton()
{
	if (UserCreateBox)
	{
		UserCreateBox->RemoveFromParent();
	}

	Super::OnClickedBackButton();
}

void UStartMenu::InitNewButton()
{
	if (NewButton)
	{
		NewButton->OnHovered.AddDynamic(this, &UStartMenu::OnHoveredNewButton);
		NewButton->OnUnhovered.AddDynamic(this, &UStartMenu::OnUnhoveredNewButton);
		NewButton->OnClicked.AddDynamic(this, &UStartMenu::OnClickedNewButton);
	}
}

void UStartMenu::InitLoadButton()
{
	if (LoadButton)
	{
		LoadButton->OnHovered.AddDynamic(this, &UStartMenu::OnHoveredLoadButton);
		LoadButton->OnUnhovered.AddDynamic(this, &UStartMenu::OnUnhoveredLoadButton);
		LoadButton->OnClicked.AddDynamic(this, &UStartMenu::OnClickedLoadButton);
	}
}

void UStartMenu::InitDeleteButton()
{
	if (DeleteButton)
	{
		DeleteButton->OnHovered.AddDynamic(this, &UStartMenu::OnHoveredDeleteButton);
		DeleteButton->OnUnhovered.AddDynamic(this, &UStartMenu::OnUnhoveredDeleteButton);
		DeleteButton->OnClicked.AddDynamic(this, &UStartMenu::OnClickedDeleteButton);
	}
}

void UStartMenu::AddUser(const FText UserName)
{
	USavedUser* SavedUser = Cast<USavedUser>(CreateWidget(this, SavedUserClass));
	if (SavedUser)
	{
		SavedUser->SetStartMenu(this);
		SavedUser->SetUserName(UserName);
		SavedUser->SetListNumber(SavedUserList.Num() + 1);
		SavedUser->SetCreatedDate();

		SavedUserList.Add(SavedUser);
		
		if (SavedGameBox)
		{
			SavedGameBox->AddChildToStackBox(SavedUser);
		}
	}
}

USavedUser* UStartMenu::GetSelectedUser() const
{
	return SelectedUser;
}

void UStartMenu::SetSelectedUser(USavedUser* SavedUser)
{
	SelectedUser = SavedUser;
}
