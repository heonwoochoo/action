// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/InGame/QuestInfo.h"
#include "Kismet/GameplayStatics.h"
#include "Controller/CharacterController.h"
#include "Components/VerticalBox.h"

void UQuestInfo::NativeConstruct()
{
	Super::NativeConstruct();

	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController)
	{
		CharacterController->OnChangedInputMode.AddDynamic(this, &UQuestInfo::OnChangedInputMode);
	}
}

void UQuestInfo::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UQuestInfo::NativeDestruct()
{
	Super::NativeDestruct();

}

void UQuestInfo::OnChangedInputMode(const EInputMode& Mode)
{
	if (Mode == EInputMode::EIM_Game)
	{
		RemoveFromParent();
	}
}