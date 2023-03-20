// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/DamageText.h"
#include "HUD/DamageWidgetComponent.h"

// Sets default values
ADamageText::ADamageText()
{
 	PrimaryActorTick.bCanEverTick = false;
	DamageWidgetComponent = CreateDefaultSubobject<UDamageWidgetComponent>(TEXT("DamageWidgetComponent"));
	if (DamageWidgetComponent)
	{
		SetRootComponent(DamageWidgetComponent);
	}
}

void ADamageText::Initialize(const float Damage)
{
	if (DamageWidgetComponent)
	{
		DamageWidgetComponent->SetDamageText(Damage);
	}
}


void ADamageText::BeginPlay()
{
	Super::BeginPlay();
	if (DamageWidgetComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("BeginPlay in"));
	}
	SetLifeSpan(LifeSpanTime);
}



void ADamageText::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


