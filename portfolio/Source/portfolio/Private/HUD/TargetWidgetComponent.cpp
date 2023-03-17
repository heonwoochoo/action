// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/TargetWidgetComponent.h"
#include "HUD/TargetWidget.h"

void UTargetWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	TargetWidget = Cast<UTargetWidget>(GetUserWidgetObject());
	if (TargetWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("TargetWidget"));
	}
}
