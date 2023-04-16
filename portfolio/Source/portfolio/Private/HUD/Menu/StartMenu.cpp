// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/StartMenu.h"
#include "Components/StackBox.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "HUD/Menu/UserCreateBox.h"
#include "HUD/Menu/SavedUser.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstance/DefaultGameInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "HUD/Menu/UserDeleteBox.h"

void UStartMenu::NativeConstruct()
{
	Super::NativeConstruct();

	InitNewButton();
	InitLoadButton();
	InitDeleteButton();

	LoadUserNameFromSaveGame();
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
	UserDeleteBox = Cast<UUserDeleteBox>(CreateWidget(this, UserDeleteBoxClass));
	if (UserDeleteBox && SelectedUser)
	{
		UserDeleteBox->AddToViewport(1);
		UserDeleteBox->SetStartMenu(this);
		UserDeleteBox->SetUserNameText(SelectedUser->GetUserName());
	}

	PlayButtonSound();
}

void UStartMenu::OnClickedBackButton()
{
	//if (UserCreateBox)
	//{
	//	UserCreateBox->RemoveFromParent();
	//}

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

void UStartMenu::LoadUserNameFromSaveGame()
{
	// 세이브 게임 불러오기
	UDefaultGameInstance* DefaultGameInstance = Cast<UDefaultGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (DefaultGameInstance)
	{
		// 유저 이름 데이터가 저장된 세이브 파일 로드
		DefaultGameInstance->LoadDefaultSaveGame();

		TArray<FString> UserNames = DefaultGameInstance->GetAllSavedUserName();

		if (UserNames.Num() < 1) return;

		for (FString UserName : UserNames)
		{
			bool IsExist = UGameplayStatics::DoesSaveGameExist(UserName, 0);
			if (IsExist)
			{
				// 세이브 게임 파일이 존재
				USavedUser* SavedUser = Cast<USavedUser>(CreateWidget(this, SavedUserClass));
				if (SavedUser)
				{
					SavedUser->SetStartMenu(this);
					SavedUser->SetUserName(FText::FromString(UserName));
					SavedUser->SetListNumber(SavedUserList.Num() + 1);
					SavedUser->SetCreatedDate(DefaultGameInstance->GetUserCreatedDate(UserName));

					SavedUserList.Add(SavedUser);

					if (SavedGameBox)
					{
						SavedGameBox->AddChildToStackBox(SavedUser);
					}
				}
			}
			else
			{
				// 저장된 유저 이름과 실제 세이브 파일이 일치하지 않을 경우 리스트에서 삭제
				DefaultGameInstance->RemoveUserFromDefaultSaveGame(UserName);
			}
		}
	}
}

void UStartMenu::AddUser(const FText UserName)
{
	UDefaultGameInstance* DefaultGameInstance = Cast<UDefaultGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (DefaultGameInstance)
	{
		DefaultGameInstance->CreateUserSaveGame(UserName.ToString());
	}

	USavedUser* SavedUser = Cast<USavedUser>(CreateWidget(this, SavedUserClass));
	if (SavedUser)
	{
		SavedUser->SetStartMenu(this);
		SavedUser->SetUserName(UserName);
		SavedUser->SetListNumber(SavedUserList.Num() + 1);
		SavedUser->SetCreatedDate(UKismetMathLibrary::Now());
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

void UStartMenu::DeleteSelectedUser()
{
	if (SelectedUser)
	{
		UDefaultGameInstance* DefaultGameInstance = Cast<UDefaultGameInstance>(UGameplayStatics::GetGameInstance(this));
		if (DefaultGameInstance)
		{
			FString UserName = SelectedUser->GetUserName().ToString();
			DefaultGameInstance->RemoveUserSaveGame(UserName);
		}

		// 멤버 변수 데이터 업데이트
		SavedUserList.Remove(SelectedUser);

		// UI 인스턴스 제거
		SelectedUser->RemoveFromParent();

		if (SelectedUser)
		{
			SelectedUser = nullptr;
		}

		for (int32 i = 0; i < SavedUserList.Num(); ++i)
		{
			SavedUserList[i]->SetListNumber(i + 1);
		}
	}
}
