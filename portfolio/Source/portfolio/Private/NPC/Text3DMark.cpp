// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/Text3DMark.h"
#include "Materials/Material.h"
#include "Text3DComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Component/QuestServerComponent.h"
#include "NPC/NPCGreyStone.h"

AText3DMark::AText3DMark()
{
	 
}

void AText3DMark::SetTextColor(const ETextMaterialColor& MaterialColor)
{
	if (!BlueColor || !GreyColor || !YellowColor) return;
	
	UMaterial* Selected{};

	switch (MaterialColor)
	{
	case ETextMaterialColor::ETMC_Blue:
		Selected = BlueColor;
		break;
	case ETextMaterialColor::ETMC_Grey:
		Selected = GreyColor;
		break;
	case ETextMaterialColor::ETMC_Yellow:
		Selected = YellowColor;
		break;
	default:
		return;
	}

	if (Selected)
	{
		UText3DComponent* Text3DComponenet = GetText3DComponent();
		if (Text3DComponenet)
		{
			Text3DComponenet->SetFrontMaterial(Selected);
			Text3DComponenet->SetBevelMaterial(Selected);
			Text3DComponenet->SetExtrudeMaterial(Selected);
			Text3DComponenet->SetBackMaterial(Selected);
		}
	}
}

void AText3DMark::SetLocationOwnerHeadup()
{
	 ACharacter* Character = Cast<ACharacter>(GetOwner());
	 if (Character)
	 {
		 UCapsuleComponent* CapsuleComponenet = Character->GetCapsuleComponent();
		 if (CapsuleComponenet)
		 {
			const float& HalfHeight = CapsuleComponenet->GetScaledCapsuleHalfHeight();
			
			FVector Location = CapsuleComponenet->GetComponentLocation();
			Location.Z += HalfHeight + 50.f;

			SetActorLocation(Location);
		 }
	 }
}

void AText3DMark::SetText(const FText& InText)
{
	UText3DComponent* Text3DComponenet = GetText3DComponent();
	if (Text3DComponenet)
	{
		Text3DComponenet->SetText(InText);
	}
}

void AText3DMark::Update()
{
	ANPCGreyStone* NPC = Cast<ANPCGreyStone>(GetOwner());
	if (NPC)
	{
		UQuestServerComponent* QuestServerComponent = NPC->GetQuestServerComponent();
		if (QuestServerComponent)
		{
			const TMap<EQuestCode, EQuestState>& QuestList = QuestServerComponent->GetQuestList();

			TArray<EQuestState> QuestStates;
			QuestList.GenerateValueArray(QuestStates);

			if (QuestStates.Contains(EQuestState::EQS_Complete))
			{
				SetActorHiddenInGame(false);
				SetText(FText::FromString(TEXT("!")));
				SetTextColor(ETextMaterialColor::ETMC_Yellow);
				return;
			}
			else if (QuestStates.Contains(EQuestState::EQS_Unserved))
			{
				SetActorHiddenInGame(false);
				SetText(FText::FromString(TEXT("?")));
				SetTextColor(ETextMaterialColor::ETMC_Blue);
				return;
			}
			else if (QuestStates.Contains(EQuestState::EQS_Progress))
			{
				SetActorHiddenInGame(false);
				SetText(FText::FromString(TEXT("?")));
				SetTextColor(ETextMaterialColor::ETMC_Grey);
				return;
			}
			else
			{
				// 아무런 퀘스트 상태가 없을 경우 숨김처리
				SetActorHiddenInGame(true);
			}
		}
	}
}
