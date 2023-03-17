// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyBase.h"
#include "Data/EnemyDataAsset.h"
#include "HUD/TargetWidgetComponent.h"
#include "Components/CapsuleComponent.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = false;

	if (DataAsset)
	{
		EnemyData = DataAsset->EnemyDatas[Name];
	}

	SetRootComponent(GetCapsuleComponent());
	TargetWidgetComponent = CreateDefaultSubobject<UTargetWidgetComponent>(TEXT("TargetImgComponent"));
	if (TargetWidgetComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("TargetWidget"));
		TargetWidgetComponent->SetupAttachment(GetCapsuleComponent());
		TargetWidgetComponent->SetVisibility(true);
	}

	Tags.Add(FName("Enemy"));
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	

}

EEnemyState AEnemyBase::GetState() const
{
	return State;
}

void AEnemyBase::SetState(EEnemyState NewState)
{
	State = NewState;
}

void AEnemyBase::SetTargetImgVisibie(bool NewState)
{
	if (TargetWidgetComponent)
	{
		NewState ? TargetWidgetComponent->SetVisibility(true) : TargetWidgetComponent->SetVisibility(false);
	}
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

