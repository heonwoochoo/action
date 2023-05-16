// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Overlay/SpotNameNotify.h"
#include "Components/TextBlock.h"

void USpotNameNotify::NativeConstruct()
{
	Super::NativeConstruct();

	EndAnimationEvent.BindDynamic(this, &USpotNameNotify::OnEndShowAndHideAnimation);
		
	BindToAnimationFinished(ShowAndHide, EndAnimationEvent);
}

void USpotNameNotify::OnEndShowAndHideAnimation()
{
	RemoveFromParent();
	Destruct();
}

void USpotNameNotify::SetSpotText(const FText& InName)
{
	if (SpotText)
	{
		SpotText->SetText(InName);
	}
}

void USpotNameNotify::PlayShowAndHideAnimation()
{
	if (ShowAndHide)
	{
		PlayAnimationForward(ShowAndHide);
	}
}