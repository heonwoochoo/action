// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/HUDBase.h"
#include "Enemy/EnemyBase.h"
#include "EnemyTypes.h"
#include "HUD/EnemyHPBarWidgetComponent.h"

AHUDBase::AHUDBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHUDBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AHUDBase::SetEnemyHpBar(AEnemyBase* Enemy)
{

	if (Enemy->GetState() != EEnemyState::EES_Dead)
	{

		UEnemyHPBarWidgetComponent* HPWidgetComponent = Enemy->GetHPBarWidgetComponent();
		if (HPWidgetComponent)
		{
			const float CurrentHP = Enemy->GetEnemyData().Hp;
			const float MaxHP = Enemy->GetEnemyData().MaxHp;
			HPWidgetComponent->SetHPBar(CurrentHP / MaxHP);
		}
	}
}