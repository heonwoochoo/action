// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Combat/HeadUpWidget.h"
#include "Components/StackBox.h"
#include "HUD/Combat/HeadUpText.h"

void UHeadUpWidget::NativeConstruct()
{
	Super::NativeConstruct();

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
