// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/DefaultGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/DefaultSaveGame.h"
#include "SaveGame/UserSaveGame.h"
#include "Kismet/KismetMathLibrary.h"

FSoundSettings UDefaultGameInstance::GetSoundSettings() const
{
	return SoundSettings;
}

void UDefaultGameInstance::SetSoundSettings(ESoundOptionsType SoundType, float Value)
{
	switch (SoundType)
	{
	case ESoundOptionsType::ESOT_Master:
		SoundSettings.MasterVolume = Value;
		break;
	case ESoundOptionsType::ESOT_Effect:
		SoundSettings.EffectVolume = Value;
		break;
	case ESoundOptionsType::ESOT_Music:
		SoundSettings.MusicVolume = Value;
		break;
	}
}

void UDefaultGameInstance::LoadDefaultSaveGame()
{
	bool IsExist = UGameplayStatics::DoesSaveGameExist(DefaultSlot, 0);
	if (IsExist)
	{
		DefaultSaveGame = Cast<UDefaultSaveGame>(UGameplayStatics::LoadGameFromSlot(DefaultSlot, 0));
		SaveDefaultSaveGame();
	}
	else
	{
		DefaultSaveGame = Cast<UDefaultSaveGame>(UGameplayStatics::CreateSaveGameObject(DefaultSaveGameClass));
	}
}

void UDefaultGameInstance::SaveDefaultSaveGame()
{
	if (DefaultSaveGame)
	{
		UGameplayStatics::SaveGameToSlot(DefaultSaveGame, DefaultSlot, 0);
	}
}

void UDefaultGameInstance::AddUserToDefaultSaveGame(FString UserName)
{
	if (DefaultSaveGame)
	{
		DefaultSaveGame->AddUser(UserName);
		SaveDefaultSaveGame();
	}
}

void UDefaultGameInstance::RemoveUserFromDefaultSaveGame(FString UserName)
{
	if (DefaultSaveGame)
	{
		DefaultSaveGame->RemoveUser(UserName);
		SaveDefaultSaveGame();
	}
}

TArray<FString> UDefaultGameInstance::GetAllSavedUserName() const
{
	if (DefaultSaveGame)
	{
		return DefaultSaveGame->GetAllUserName();
	}
	else
	{
		return TArray<FString>();
	}
}

void UDefaultGameInstance::CreateUserSaveGame(FString UserName)
{
	bool IsExist = UGameplayStatics::DoesSaveGameExist(UserName, 0);
	if (!IsExist)
	{
		UUserSaveGame* NewUserSaveGame = Cast<UUserSaveGame>(UGameplayStatics::CreateSaveGameObject(UserSaveGameClass));
		if (NewUserSaveGame)
		{
			NewUserSaveGame->SetSlotName(UserName);
			NewUserSaveGame->SetCreatedDate(UKismetMathLibrary::Now());
			bool IsSuccess = UGameplayStatics::SaveGameToSlot(NewUserSaveGame, UserName, 0);
			if (IsSuccess)
			{
				// Default 세이브 게임에 유저 리스트 업데이트
				AddUserToDefaultSaveGame(UserName);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Exist username already"));
	}
}

void UDefaultGameInstance::RemoveUserSaveGame(FString UserName)
{
	bool IsExist = UGameplayStatics::DoesSaveGameExist(UserName, 0);
	if (IsExist)
	{
		bool IsSuccess = UGameplayStatics::DeleteGameInSlot(UserName, 0);
		if (IsSuccess)
		{
			// Default 세이브 게임에 유저 리스트 업데이트
			RemoveUserFromDefaultSaveGame(UserName);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Does not deleted user"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Does not exist username"));
	}
}

FDateTime UDefaultGameInstance::GetUserCreatedDate(FString UserName)
{
	bool IsExist = UGameplayStatics::DoesSaveGameExist(UserName, 0);
	if (IsExist)
	{
		UUserSaveGame* LoadedUserSaveGame = Cast<UUserSaveGame>(UGameplayStatics::LoadGameFromSlot(UserName, 0));
		if (LoadedUserSaveGame)
		{
			return LoadedUserSaveGame->GetCreatedDate();
		}
	}
	return FDateTime();
}
