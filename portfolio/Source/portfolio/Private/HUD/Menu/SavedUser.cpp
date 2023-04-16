// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/SavedUser.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/DefaultGameMode.h"
#include "Components/TextBlock.h"
#include "HUD/Menu/StartMenu.h"
#include "Styling/SlateColor.h"
#include "Kismet/KismetMathLibrary.h"

void USavedUser::NativeConstruct()
{
	Super::NativeConstruct();

	InitSelectButton();
}

void USavedUser::OnHoveredSelectButton()
{
	if (SelectImage && !IsSelected)
	{
		SelectImage->SetOpacity(1.f);
	}
}

void USavedUser::OnUnhoveredSelectButton()
{
	if (SelectImage && !IsSelected)
	{
		SelectImage->SetOpacity(0.f);
	}
}

void USavedUser::OnClickedSelectButton()
{
	IsSelected = true;

	ChangeTextColor(FColor::Yellow);

	if (StartMenu)
	{
		USavedUser* PrevSelectedUser = StartMenu->GetSelectedUser();

		if (PrevSelectedUser == nullptr)
		{
			StartMenu->SetSelectedUser(this);
			StartMenu->SetEnableLoadButton(true);
			StartMenu->SetEnableDeleteButton(true);
		}
		else if (PrevSelectedUser != this)
		{
			// 리스트 중 체크된 유저가 있다면 해당 유저의 선택을 해제
			PrevSelectedUser->UnCheckedButton();
			StartMenu->SetSelectedUser(this);
		}
	}

	PlaySelectButtonClickSound();
}

void USavedUser::InitSelectButton()
{
	if (SelectButton)
	{
		SelectButton->OnHovered.AddDynamic(this, &USavedUser::OnHoveredSelectButton);
		SelectButton->OnUnhovered.AddDynamic(this, &USavedUser::OnUnhoveredSelectButton);
		SelectButton->OnClicked.AddDynamic(this, &USavedUser::OnClickedSelectButton);
	}
}

void USavedUser::ChangeTextColor(FColor Color)
{
	if (ListNumberText && UserNameText && CreatedDateText && RecentDateText && PlayTimeText)
	{
		FSlateColor NewColor(Color);
		ListNumberText->SetColorAndOpacity(NewColor);
		UserNameText->SetColorAndOpacity(NewColor);
		CreatedDateText->SetColorAndOpacity(NewColor);
		RecentDateText->SetColorAndOpacity(NewColor);
		PlayTimeText->SetColorAndOpacity(NewColor);
	}
}

void USavedUser::PlaySelectButtonClickSound()
{
	ADefaultGameMode* DefaultGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this));
	if (DefaultGameMode)
	{
		DefaultGameMode->PlayChangeButtonClickSound();
	}
}

void USavedUser::UnCheckedButton()
{
	IsSelected = false;
	
	ChangeTextColor(FColor::White);

	if (SelectImage && !IsSelected)
	{
		SelectImage->SetOpacity(0.f);
	}
}

void USavedUser::SetStartMenu(UStartMenu* UserWidget)
{
	StartMenu = UserWidget;
}

FText USavedUser::GetUserName() const
{
	return UserName;
}

void USavedUser::SetUserName(FText Name)
{
	UserName = Name;

	if (UserNameText)
	{
		UserNameText->SetText(UserName);
	}
}

void USavedUser::SetListNumber(int32 Num)
{
	ListNumber = Num;

	if (ListNumberText)
	{
		ListNumberText->SetText(FText::FromString(FString::FromInt(ListNumber)));
	}
}

void USavedUser::SetCreatedDate(FDateTime Date)
{
	CreatedDate = Date;
	FString Year = FString::FromInt(CreatedDate.GetYear());
	FString Month = FString::FromInt(CreatedDate.GetMonth());
	FString Day = FString::FromInt(CreatedDate.GetDay());

	FString DateText = Year + "/" + Month + "/" + Day;

	if (CreatedDateText)
	{
		CreatedDateText->SetText(FText::FromString(DateText));
	}
}