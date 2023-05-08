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

ANPCGreyStone::ANPCGreyStone()
{
	// 퀘스트 등록
	QuestServerComponent = CreateDefaultSubobject<UQuestServerComponent>(TEXT("QuestServerComponent"));
	QuestServerComponent->AddQuest(EQuestCode::EQC_0001);
}

void ANPCGreyStone::BeginPlay()
{
	Super::BeginPlay();

	if (Text3DMarkClass && QuestServerComponent)
	{
		// 미진행 퀘스트가 있는지 확인
		// 하나라도 있으면 NPC 머리위에 ? 가 나타남
		const TMap<EQuestCode, EQuestState>& QuestList = QuestServerComponent->GetQuestList();
		for (auto& Quest : QuestList)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = this;

			Text3DMark = GetWorld()->SpawnActor<AText3DMark>(Text3DMarkClass, SpawnParameters);
			if (Text3DMark)
			{
				Text3DMark->SetLocationOwnerHeadup();
			}
		}
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
				QuestBox->AddToViewport();

				const FVector2D& ScreenPosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
				QuestBox->SetLocation(ScreenPosition);
			}
		}
	}
}
