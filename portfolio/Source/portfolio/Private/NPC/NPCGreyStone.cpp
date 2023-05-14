// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/NPCGreyStone.h"
#include "NPC/Text3DMark.h"
#include "Component/QuestServerComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Controller/CharacterController.h"
#include "HUD/HUDBase.h"
#include "HUD/NPC/QuestSelectBox.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Component/NPCDialogueComponent.h"
#include "DefaultCharacter.h"

ANPCGreyStone::ANPCGreyStone()
{
	// 퀘스트 등록
	QuestServerComponent = CreateDefaultSubobject<UQuestServerComponent>(TEXT("QuestServerComponent"));
	QuestServerComponent->AddQuest(EQuestCode::EQC_0001);

	// 다이얼로그 컴포넌트 추가
	DialogueComponent = CreateDefaultSubobject<UNPCDialogueComponent>(TEXT("DialogueComponent"));

}

void ANPCGreyStone::BeginPlay()
{
	Super::BeginPlay();

	if (Text3DMarkClass && QuestServerComponent)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		Text3DMark = GetWorld()->SpawnActor<AText3DMark>(Text3DMarkClass, SpawnParameters);
	}
}

void ANPCGreyStone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Text3DMark)
	{
		Text3DMark->Update();
		Text3DMark->SetLocationOwnerHeadup();
	}
}

void ANPCGreyStone::BeginOverlappedSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::BeginOverlappedSphere(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (OtherActor->ActorHasTag(FName(TEXT("Player"))))
	{
		// 가이드 메세지 표시
		ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (CharacterController)
		{
			AHUDBase* HUDBase = Cast<AHUDBase>(CharacterController->GetHUD());
			if (HUDBase)
			{
				const FText& Message = FText::FromString(TEXT("'Z'키를 눌러 대화를 할 수 있습니다."));
				HUDBase->ShowGuideMessage(Message);
			}
		}
	}
}

void ANPCGreyStone::EndOverlappedSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::EndOverlappedSphere(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	// 가이드 메세지 숨김
	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (CharacterController)
	{
		AHUDBase* HUDBase = Cast<AHUDBase>(CharacterController->GetHUD());
		if (HUDBase)
		{
			HUDBase->HideGuideMessage();
		}
	}
}

void ANPCGreyStone::OnChangedInputMode(const EInputMode& InMode)
{
	if (InMode == EInputMode::EIM_Game)
	{
		if (QuestBox && bIsNearPlayer)
		{
			QuestBox->RemoveFromParent();
		}
	}
}

void ANPCGreyStone::OnSelectedQuest(const EQuestCode& SelectedCode)
{
	if (DialogueComponent && QuestServerComponent)
	{
		const TMap<EQuestCode, EQuestState>& QuestList = QuestServerComponent->GetQuestList();
		if (QuestList.Contains(SelectedCode))
		{
			if (QuestList[SelectedCode] == EQuestState::EQS_Unserved)
			{
				const FQuest* QuestData = QuestServerComponent->GetQuestData(SelectedCode);
				if (QuestData)
				{
					const TArray<FText>& DialogueText = QuestData->Dialogue;
					DialogueComponent->OpenDialogueBox(DialogueText);
					DialogueComponent->SetQuestCode(SelectedCode);
				}
			}
			else if (QuestList[SelectedCode] == EQuestState::EQS_Complete && NearPlayer)
			{
				UE_LOG(LogTemp, Warning, TEXT("퀘스트 완료"));
				QuestServerComponent->ClearQuest(SelectedCode, NearPlayer);

				// 클리어시 UI모드를 게임모드로 변경
				if (NearPlayer)
				{
					NearPlayer->HandleShowMouse();
				}
			}
		}
	}
}

void ANPCGreyStone::TalkWithPlayer(ADefaultCharacter* PlayerCharacter)
{
	if (QuestBoxClass && PlayerCharacter)
	{
		PlayerCharacter->HandleShowMouse();

		ACharacterController* CharacterController = Cast<ACharacterController>(PlayerCharacter->GetController());
		if (CharacterController)
		{
			if (QuestBox)
			{
				QuestBox->RemoveFromParent();
				QuestBox = nullptr;
			}

			QuestBox = Cast<UQuestSelectBox>(CreateWidget(CharacterController, QuestBoxClass));
			if (QuestBox)
			{
				// 오너 설정
				QuestBox->SetOwner(this);

				// 뷰포트에 추가
				QuestBox->AddToViewport();

				// 위치 설정
				FVector2D ScreenPosition;
				UGameplayStatics::ProjectWorldToScreen(CharacterController, GetActorLocation(), ScreenPosition);
				QuestBox->SetLocation(ScreenPosition);

				// 리스트 설정
				if (QuestServerComponent)
				{
					QuestBox->Init(QuestServerComponent);
				}

				// 인풋모드의 변경을 구독
				CharacterController->OnChangedInputMode.AddDynamic(this, &ANPCGreyStone::OnChangedInputMode);
			}
		}
	}
}