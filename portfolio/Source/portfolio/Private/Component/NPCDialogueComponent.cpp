// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/NPCDialogueComponent.h"
#include "HUD/NPC/DialogueBox.h"
#include "Controller/CharacterController.h"
#include "Kismet/GameplayStatics.h"
#include "NPC/NPCGreyStone.h"
#include "DefaultCharacter.h"
#include "HUD/NPC/QuestSelectBox.h"

UNPCDialogueComponent::UNPCDialogueComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

}


void UNPCDialogueComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UNPCDialogueComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UNPCDialogueComponent::OpenDialogueBox(const TArray<FText>& InDialogueText)
{
	if (DialogueBoxClass)
	{
		ANPCGreyStone* NPC = Cast<ANPCGreyStone>(GetOwner());
		if (NPC)
		{
			ADefaultCharacter* PlayerCharacter = NPC->GetNearPlayer();
			if (PlayerCharacter)
			{
				ACharacterController* PlayerController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(PlayerCharacter, 0));
				if (PlayerController)
				{
					DialogueBox = Cast<UDialogueBox>(CreateWidget(PlayerController, DialogueBoxClass));
					if (DialogueBox)
					{
						// 인풋모드가 게임으로 바뀔 때 알림 구독 -> 호출시 다이얼로그 닫음
						PlayerController->OnChangedInputMode.AddDynamic(DialogueBox, &UDialogueBox::OnChangedInputMode);

						// 뷰포트에 추가
						DialogueBox->AddToViewport();

						// NPC가 만들어낸 퀘스트 박스 위젯 닫기
						UQuestSelectBox* QuestSelectBox = NPC->GetQuestBox();
						if (QuestSelectBox)
						{
							QuestSelectBox->RemoveFromParent();
						}
					}
				}
			}
		}
	}
}

