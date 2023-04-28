// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Combat/HeadUpWidget.h"
#include "Components/StackBox.h"
#include "HUD/Combat/HeadUpText.h"
#include "Kismet/GameplayStatics.h"
#include "DefaultCharacter.h"

void UHeadUpWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (DefaultCharacter)
	{
		DefaultCharacter->OnGetGold.AddDynamic(this, &UHeadUpWidget::ShowGottenGold);
		DefaultCharacter->OnChangedLevel.AddDynamic(this, &UHeadUpWidget::ShowLevelUpText);
	}
}

void UHeadUpWidget::ShowGottenGold(const int32& Value)
{
	const FString FormatString = FString(TEXT("+")) + FString::FromInt(Value) + FString(TEXT(" Gold"));
	const FText FormatText = FText::FromString(FormatString);
	HandleHeadUpText(FormatText, FColor::Yellow);
}

void UHeadUpWidget::ShowLevelUpText(const int32& NewLevel)
{
	const FString FormatString = FString(TEXT("LEVEL UP!"));
	const FText FormatText = FText::FromString(FormatString);
	HandleHeadUpText(FormatText, FColor::Yellow);
}

void UHeadUpWidget::HandleHeadUpText(const FText& InText, const FColor& Color)
{
	if (ShowingTextClass && TextStackBox)
	{
		UHeadUpText* ShowingTextBlock = Cast<UHeadUpText>(CreateWidget(this, ShowingTextClass));
		ShowingTextBlock->SetShowingText(InText, Color);
		TextStackBox->AddChild(ShowingTextBlock);
	}
}
