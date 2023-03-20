// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/DamageWidgetComponent.h"
#include "HUD/DamageTextWidget.h"
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

void UDamageWidgetComponent::SetDamageText(float Damage)
{
	if (DamageTextWidget)
	{
		DamageTextWidget->DamageText->SetText(FText::FromString(FString::FromInt((int)Damage)));
		UE_LOG(LogTemp, Warning, TEXT("Damage : %f"), Damage);
	}
}
