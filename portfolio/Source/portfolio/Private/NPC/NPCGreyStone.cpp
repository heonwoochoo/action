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

	USkeletalMeshComponent* MeshComponent = GetMesh();
	if (MeshComponent)
	{
		MeshComponent->OnBeginCursorOver.AddDynamic(this, &ANPCGreyStone::OnBeginCursorOverMesh);
		MeshComponent->OnEndCursorOver.AddDynamic(this, &ANPCGreyStone::OnEndCursorOverMesh);
		MeshComponent->OnClicked.AddDynamic(this, &ANPCGreyStone::OnClickedMesh);
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

void ANPCGreyStone::OnBeginCursorOverMesh(UPrimitiveComponent* TouchedComponent)
{
	if (OverlayMaterial && bIsNearPlayer)
	{
		USkeletalMeshComponent* MeshComponent = GetMesh();
		if (MeshComponent)
		{
			MeshComponent->SetOverlayMaterial(OverlayMaterial);
		}

		// 가이드 메세지 표시
		ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (CharacterController)
		{
			AHUDBase* HUDBase = Cast<AHUDBase>(CharacterController->GetHUD());
			if (HUDBase)
			{
				const FText& Message = FText::FromString(TEXT("클릭하여 퀘스트를 확인할 수 있습니다."));
				HUDBase->ShowGuideMessage(Message);
			}
		}
	}
}

void ANPCGreyStone::OnEndCursorOverMesh(UPrimitiveComponent* TouchedComponent)
{
	if (OverlayMaterial && bIsNearPlayer)
	{
		USkeletalMeshComponent* MeshComponent = GetMesh();
		if (MeshComponent)
		{
			MeshComponent->SetOverlayMaterial(nullptr);
		}

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
}

void ANPCGreyStone::OnClickedMesh(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	if (QuestBoxClass)
	{
		ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (CharacterController)
		{
			if (QuestBox)
			{
				QuestBox->RemoveFromParent();
			}

			QuestBox = Cast<UQuestSelectBox>(CreateWidget(CharacterController, QuestBoxClass));
			if (QuestBox)
			{
				// 오너 설정
				QuestBox->SetOwner(this);

				// 뷰포트에 추가
				QuestBox->AddToViewport();

				// 위치 설정
				const FVector2D& ScreenPosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
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

void ANPCGreyStone::OnChangedInputMode(const EInputMode& InMode)
{
	if (InMode == EInputMode::EIM_Game)
	{
		if (QuestBox)
		{
			QuestBox->RemoveFromParent();
		}
	}
}

void ANPCGreyStone::OnSelectedQuest(const EQuestCode& SelectedCode)
{
	if (DialogueComponent && QuestServerComponent)
	{
		const FQuest* QuestData = QuestServerComponent->GetQuestData(SelectedCode);
		if (QuestData)
		{
			const TArray<FText>& DialogueText = QuestData->Dialogue;
			DialogueComponent->OpenDialogueBox(DialogueText);
		}
	}
}