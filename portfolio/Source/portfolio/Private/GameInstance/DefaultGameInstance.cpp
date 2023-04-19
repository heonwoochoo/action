// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/DefaultGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/DefaultSaveGame.h"
#include "SaveGame/UserSaveGame.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/GameState.h"
#include "DefaultCharacter.h"

void UDefaultGameInstance::Init()
{
	Super::Init();

	LoadDefaultSaveGame();
}

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
	const bool IsExist = UGameplayStatics::DoesSaveGameExist(DefaultSlot, 0);
	if (IsExist)
	{
		DefaultSaveGame = Cast<UDefaultSaveGame>(UGameplayStatics::LoadGameFromSlot(DefaultSlot, 0));
	}
	else
	{
		DefaultSaveGame = Cast<UDefaultSaveGame>(UGameplayStatics::CreateSaveGameObject(DefaultSaveGameClass));
		UGameplayStatics::SaveGameToSlot(DefaultSaveGame, DefaultSlot, 0);
	}
}

void UDefaultGameInstance::AddUserToDefaultSaveGame(FString UserName)
{
	if (DefaultSaveGame)
	{
		DefaultSaveGame->UserNames.Add(UserName);
		UGameplayStatics::SaveGameToSlot(DefaultSaveGame, DefaultSlot, 0);
	}
}

void UDefaultGameInstance::RemoveUserFromDefaultSaveGame(FString UserName)
{
	if (DefaultSaveGame)
	{
		DefaultSaveGame->UserNames.Remove(UserName);
		UGameplayStatics::SaveGameToSlot(DefaultSaveGame, DefaultSlot, 0);
	}
}

TArray<FString> UDefaultGameInstance::GetAllSavedUserName() const
{
	if (DefaultSaveGame)
	{
		return DefaultSaveGame->UserNames;
	}
	return TArray<FString>();
}

void UDefaultGameInstance::CreateUserSaveGame(FString UserName)
{
	const bool IsExist = UGameplayStatics::DoesSaveGameExist(UserName, 0);
	if (!IsExist)
	{
		UUserSaveGame* NewUserSaveGame = Cast<UUserSaveGame>(UGameplayStatics::CreateSaveGameObject(UserSaveGameClass));
		if (NewUserSaveGame)
		{
			NewUserSaveGame->SlotName = UserName;
			NewUserSaveGame->SystemInfo.CreatedDate = UKismetMathLibrary::Now();
			const bool IsSuccess = UGameplayStatics::SaveGameToSlot(NewUserSaveGame, UserName, 0);
			if (IsSuccess)
			{
				// Default 세이브 게임에 유저 리스트 업데이트
				AddUserToDefaultSaveGame(UserName);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Exist username"));
	}
}

void UDefaultGameInstance::RemoveUserSaveGame(FString UserName)
{
	const bool IsExist = UGameplayStatics::DoesSaveGameExist(UserName, 0);
	if (IsExist)
	{
		const bool IsSuccess = UGameplayStatics::DeleteGameInSlot(UserName, 0);
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

void UDefaultGameInstance::OpenDefaultWorldLevel()
{
	// 유저명 저장
	PlayingUserName = UserSaveGame->SlotName;

	// 오픈월드 열기
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->SetShowMouseCursor(false);

		UGameplayStatics::OpenLevelBySoftObjectPtr(this, DefaultWorldLevel);
	}
}

void UDefaultGameInstance::SetUserSaveGame(UUserSaveGame* SaveGame)
{
	UserSaveGame = SaveGame;
}

UUserSaveGame* UDefaultGameInstance::GetUserSaveGame() const
{
	return UserSaveGame;
}

void UDefaultGameInstance::OpenGameStartLevel()
{
	// 게임시작 창 열기
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, GameStartLevel);
	}
}

bool UDefaultGameInstance::SaveGame()
{
	if (UserSaveGame)
	{
		const bool IsExist = UGameplayStatics::DoesSaveGameExist(PlayingUserName, 0);
		if (IsExist)
		{
			const bool IsSuccess = UGameplayStatics::SaveGameToSlot(UserSaveGame, PlayingUserName, 0);
			if (IsSuccess)
			{
				return true;
			}
		}
	}
	return false;
}

void UDefaultGameInstance::UpdateSaveGame()
{
	if (!PlayingUserName.IsEmpty())
	{
		const bool IsExist = UGameplayStatics::DoesSaveGameExist(PlayingUserName, 0);
		if (IsExist)
		{
			UserSaveGame = Cast<UUserSaveGame>(UGameplayStatics::LoadGameFromSlot(PlayingUserName, 0));
			if (UserSaveGame)
			{
				UpdateSaveGameSystemInfo();
				UpdateSaveGameInGameInfo();
			}
		}
	}
}

void UDefaultGameInstance::UpdateSaveGameSystemInfo()
{
	// 이름 업데이트
	UserSaveGame->SlotName = PlayingUserName;

	// 마지막 플레이 시간 업데이트
	FDateTime Now = UKismetMathLibrary::Now();
	UserSaveGame->SystemInfo.RecentDate = Now;

	// 플레이 시간 누적
	AGameState* GameState = Cast<AGameState>(UGameplayStatics::GetGameState(this));
	if (GameState)
	{
		APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
		const float PlaySeconds = GameState->GetPlayerStartTime(Controller);
		UserSaveGame->SystemInfo.PlayTime += PlaySeconds;
	}
}

void UDefaultGameInstance::UpdateSaveGameInGameInfo()
{
	// 위치 업데이트
	ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (DefaultCharacter)
	{
		const FTransform Transform = DefaultCharacter->GetActorTransform();
		UserSaveGame->InGameInfo.Transform = Transform;
	}
}

FString UDefaultGameInstance::GetUserName() const
{
	return PlayingUserName;
}
