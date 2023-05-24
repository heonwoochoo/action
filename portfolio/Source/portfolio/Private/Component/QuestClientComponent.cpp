// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/QuestClientComponent.h"
#include "DefaultCharacter.h"
#include "HUD/HUDBase.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/Overlay/ChatBox.h"
#include "Sound/SoundCue.h"
#include "Controller/CharacterController.h"
#include "HUD/HUDBase.h"
#include "HelperFunction.h"
#include "GameInstance/DefaultGameInstance.h"
#include "SaveGame/UserSaveGame.h"

UQuestClientComponent::UQuestClientComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UQuestClientComponent::BeginPlay()
{
	Super::BeginPlay();

	LoadDataFromSaveGame();
}


void UQuestClientComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UQuestClientComponent::LoadDataFromSaveGame()
{
	UDefaultGameInstance* DefaultGameInstance = Cast<UDefaultGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (DefaultGameInstance)
	{
		const FString UserName = DefaultGameInstance->GetUserName();
		bool IsExist = UGameplayStatics::DoesSaveGameExist(UserName, 0);
		if (IsExist)
		{
			UUserSaveGame* UserSaveGame = Cast<UUserSaveGame>(UGameplayStatics::LoadGameFromSlot(UserName, 0));
			if (UserSaveGame)
			{
				QuestList = UserSaveGame->InGameInfo.QuestList;
				ClearedQuests = UserSaveGame->InGameInfo.ClearedQuests;
			}
		}
	}
}

void UQuestClientComponent::AddQuest(const EQuestCode& InQuestCode, const FQuest& InQuest)
{
	// 기존에 수락한 퀘스트인지 중복을 검사
	for (auto& Data : QuestList)
	{
		if (Data.QuestCode == InQuestCode) return;
	}

	FQuestClientData NewData;
	NewData.QuestCode = InQuestCode;
	NewData.Quest = InQuest;
	NewData.QuestState = EQuestState::EQS_Progress;

	// 퀘스트 추가
	QuestList.Add(NewData);

	// 채팅창에 수락 메세지 출력
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		AHUDBase* HUDBase = Cast<AHUDBase>(PlayerController->GetHUD());
		if (HUDBase)
		{
			UChatBox* ChatBox = HUDBase->GetChatBox();
			if (ChatBox)
			{
				const FText& Message = InQuest.Title;
				const FString& FormatString = FString(TEXT("\'")) + Message.ToString() + FString(TEXT("\' 퀘스트를 수락하였습니다."));
				ChatBox->PrintMessageOnChat(FText::FromString(FormatString), FColor::Cyan);
			}
		}
	}

	// 효과음 재생
	if (QuestAcceptSound)
	{
		UGameplayStatics::PlaySound2D(this, QuestAcceptSound);
	}
}

void UQuestClientComponent::ClearQuest(const EQuestCode& InQuestCode)
{
	// 퀘스트 데이터 상의 퀘스트 목록 제거
	int32 TargetIndex{};
	for (int32 i = 0; i < QuestList.Num(); ++i)
	{
		if (QuestList[i].QuestCode == InQuestCode)
		{
			TargetIndex = i;
			break;
		}
	}
	if (QuestList.IsValidIndex(TargetIndex))
	{
		const FText& Title = QuestList[TargetIndex].Quest.Title;
		// 채팅창에 완료 메세지 출력
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (PlayerController)
		{
			AHUDBase* HUDBase = Cast<AHUDBase>(PlayerController->GetHUD());
			if (HUDBase)
			{
				UChatBox* ChatBox = HUDBase->GetChatBox();
				if (ChatBox)
				{
					const FString& FormatString = FString(TEXT("\'")) + Title.ToString() + FString(TEXT("\' 퀘스트를 완료하였습니다."));
					ChatBox->PrintMessageOnChat(FText::FromString(FormatString), FColor::Cyan);
				}
			}
		}

		// 목록에서 제거
		QuestList.RemoveAt(TargetIndex);
	}
	// 완료 목록에 추가
	ClearedQuests.Add(InQuestCode);

	// 효과음 재생
	if (QuestClearSound)
	{
		UGameplayStatics::PlaySound2D(this, QuestClearSound);
	}
}

void UQuestClientComponent::AddEnemyKillCount(const FName& InEnemyCode, const int32& InCount)
{
	for (auto& QuestData : QuestList)
	{
		if (QuestData.QuestState == EQuestState::EQS_Progress)
		{
			TArray<FEnemyCondition>& EnemyCondition = QuestData.Quest.EnemyConditions;
			int32 ConditionNum = EnemyCondition.Num();
			int32 CheckNum = 0;
			for (auto& Condition : EnemyCondition)
			{
				if (Condition.EnemyCode == InEnemyCode)
				{
					Condition.CurrentKillCount = FMath::Clamp(Condition.CurrentKillCount + InCount, 0, Condition.MaxKillCount);

					if (Condition.CurrentKillCount == Condition.MaxKillCount)
					{
						CheckNum++;
						// 킬 카운트 조건이 모두 최대치에 도달하면 퀘스트 상태를 완료로 바꿉니다.
						if (CheckNum == ConditionNum)
						{
							QuestData.QuestState = EQuestState::EQS_Complete;

							OnChangedState.Broadcast(QuestData.QuestCode, EQuestState::EQS_Complete);
						}
					}
					// 화면 중앙 상단에 메세지 출력
					ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
					if (CharacterController)
					{
						AHUDBase* HUDBase = Cast<AHUDBase>(CharacterController->GetHUD());
						if (HUDBase)
						{
							const FString& FormatString =
								UHelperFunction::GetNameFromEnemyCode(InEnemyCode).ToString() + FString(TEXT(" ")) +
								FString::FromInt(Condition.CurrentKillCount) + FString(TEXT("/")) +
								FString::FromInt(Condition.MaxKillCount);

							HUDBase->NotifyMessageToUser(FText::FromString(FormatString));
						}
					}
				}
			}
		}
	}
}

bool UQuestClientComponent::IsExistEnemyInQuestList(const FName& InEnemyCode)
{
	for (auto& QuestData : QuestList)
	{
		if (QuestData.QuestState == EQuestState::EQS_Progress)
		{
			const TArray<FEnemyCondition>& Conditions = QuestData.Quest.EnemyConditions;
			for (auto& Condition : Conditions)
			{
				if (Condition.EnemyCode == InEnemyCode)
				{
					return true;
				}
			}
		}
	}
	return false;
}
