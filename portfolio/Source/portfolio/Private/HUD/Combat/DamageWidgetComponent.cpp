// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Combat/DamageWidgetComponent.h"
#include "HUD/Combat/DamageTextWidget.h"
#include "Components/TextBlock.h"

void UDamageWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	DamageTextWidget = Cast<UDamageTextWidget>(GetUserWidgetObject());
	if (DamageTextWidget)
	{
		this->SetWidgetSpace(EWidgetSpace::Screen);
	}
	
}

void UDamageWidgetComponent::SetDamageText(const float& InDamage, const bool& IsCritical)
{
	if (DamageTextWidget)
	{
		DamageTextWidget->DamageText->SetText(FText::FromString(FString::FromInt((int)InDamage)));
	
		if (IsCritical)
		{
			// ��Ʈ ������ ��
			FSlateFontInfo FontInfo = DamageTextWidget->DamageText->GetFont();
			FontInfo.Size = 48;
			DamageTextWidget->DamageText->SetFont(FontInfo);

			// ���� ����
			DamageTextWidget->DamageText->ColorAndOpacity = FLinearColor(FColor::Purple);
		}
	}
}
