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

UQuestClientComponent::UQuestClientComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UQuestClientComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UQuestClientComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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

	// 채팅창에 메세지 출력
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
				const FString& FormatString = FString(TEXT("\"")) + Message.ToString() + FString(TEXT("\" 퀘스트를 수락하였습니다."));
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

void UQuestClientComponent::AddEnemyKillCount(const FName& InEnemyCode, const int32& InCount)
{
	for (auto& QuestData : QuestList)
	{
		TArray<FEnemyCondition>& EnemyCondition = QuestData.Quest.EnemyConditions;
		for (auto& Condition : EnemyCondition)
		{
			if (Condition.EnemyCode == InEnemyCode)
			{
				Condition.CurrentKillCount = FMath::Clamp(Condition.CurrentKillCount + InCount, 0, Condition.MaxKillCount);

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
