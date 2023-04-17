// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Types/SettingTypes.h"
#include "DefaultGameInstance.generated.h"

class USaveGame;
class UDefaultSaveGame;
class UUserSaveGame;

UCLASS()
class PORTFOLIO_API UDefaultGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

private:
	FSoundSettings SoundSettings;

	FString DefaultSlot = TEXT("Default");

	// 유저가 최초로 생성되는 월드
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "World", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UWorld> DefaultWorldLevel;

protected:
	// 생성된 유저의 고유한 슬롯 이름을 저장하고 있는 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SaveGame");
	TSubclassOf<USaveGame> DefaultSaveGameClass;
	
	UDefaultSaveGame* DefaultSaveGame;

	// 유저 데이터를 저장할 세이브 게임 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SaveGame");
	TSubclassOf<USaveGame> UserSaveGameClass;

	// 현재 플레이 중인 유저의 세이브 게임 인스턴스
	UUserSaveGame* UserSaveGame;

public:
	FSoundSettings GetSoundSettings() const;
	void SetSoundSettings(ESoundOptionsType SoundType, float Value);

	/**
	*	Default 세이브 파일을 로드
	*	저장된 유저의 리스트를 포함하고 있음
	*/
	void LoadDefaultSaveGame();

	// 유저 생성
	void AddUserToDefaultSaveGame(FString UserName);

	// 유저 리스트에서 유저 이름 삭제
	void RemoveUserFromDefaultSaveGame(FString UserName);

	// 저장된 유저 이름 얻기
	TArray<FString> GetAllSavedUserName() const;

	// 유저의 정보를 저장할 세이브 게임 인스턴스 생성
	void CreateUserSaveGame(FString UserName);

	// 유저 세이브 파일 삭제
	void RemoveUserSaveGame(FString UserName);

	// 특정 유저의 생성 날짜 얻기
	FDateTime GetUserCreatedDate(FString UserName);

	// 기본 오픈월드 열기
	void OpenDefaultWorldLevel();

	// 로드한 세이브 게임 인스턴스 저장
	void SetUserSaveGame(UUserSaveGame* SaveGame);
	
	UUserSaveGame* GetUserSaveGame() const;
};
