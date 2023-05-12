// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/NPCDialogueComponent.h"
#include "HUD/NPC/DialogueBox.h"
#include "Controller/CharacterController.h"
#include "Kismet/GameplayStatics.h"
#include "NPC/NPCGreyStone.h"
#include "DefaultCharacter.h"
#include "HUD/NPC/QuestSelectBox.h"
#include "Component/QuestServerComponent.h"

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
						// 다이얼로그 데이터를 저장
						DialogueText = InDialogueText;

						// 페이지 초기화
						CurrentPage = 0;
						LastPage = InDialogueText.Num() - 1;
						
						// 첫번째 페이지 열기
						OpenFirstPage();

						DialogueBox->SetNPCDialogueComponent(this);

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

void UNPCDialogueComponent::OpenFirstPage()
{
	if (DialogueText.IsValidIndex(CurrentPage) && DialogueBox)
	{
		// 텍스트 설정
		const FText& PageText = DialogueText[CurrentPage];
		DialogueBox->SetDialogueText(PageText);
	}
}

void UNPCDialogueComponent::ReadNextPage()
{
	CurrentPage = FMath::Clamp(CurrentPage + 1, 0, LastPage + 1);

	// 다음 장으로 넘김
	if (DialogueText.IsValidIndex(CurrentPage) && DialogueBox)
	{
		// 텍스트 설정
		const FText& PageText = DialogueText[CurrentPage];
		DialogueBox->SetDialogueText(PageText);
	}

	if (CurrentPage > LastPage)
	{
		// 'Accept' 버튼 클릭, 플레이어에게 퀘스트 제공함
		ANPCGreyStone* NPC = Cast<ANPCGreyStone>(GetOwner());
		if (NPC)
		{
			UQuestServerComponent* QuestServeComponent = NPC->GetQuestServerComponent();
			if (QuestServeComponent && QuestCode != EQuestCode::EQC_None)
			{
				QuestServeComponent->ServeQuestToPlayer(QuestCode);
			}
		}

		// 다이얼로그 종료
		if (DialogueBox)
		{
			DialogueBox->RemoveFromParent();
		}
	}
}

void UNPCDialogueComponent::ReadPrevPage()
{
	CurrentPage = FMath::Clamp(CurrentPage - 1, 0, LastPage - 1);
	if (CurrentPage == 0)
	{
		OpenFirstPage();
	}
	else
	{
		// 이전 장으로 넘김
		if (DialogueText.IsValidIndex(CurrentPage) && DialogueBox)
		{
			// 텍스트 설정
			const FText& PageText = DialogueText[CurrentPage];
			DialogueBox->SetDialogueText(PageText);
		}
	}
}

