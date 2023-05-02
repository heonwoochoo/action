// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Combat/EnemyHPBarWidgetComponent.h"
#include "HUD/Combat/EnemyHPBarWidget.h"
#include "Components/ProgressBar.h"
#include "Enemy/EnemyBase.h"

void UEnemyHPBarWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	HPBarWidget = Cast<UEnemyHPBarWidget>(GetUserWidgetObject());
	AEnemyBase* EnemyBase = Cast<AEnemyBase>(GetOwner());

	if (HPBarWidget && EnemyBase)
	{
		EnemyBase->OnChangedHp.AddDynamic(HPBarWidget, &UEnemyHPBarWidget::OnChangedEnemyHP);
	}
}