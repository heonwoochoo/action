// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/MinionLane.h"

AMinionLane::AMinionLane()
{
}

void AMinionLane::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (EnemyStatsDataTable)
	{
		if (Name == EEnemyName::EEN_MinionLane)
		{
			Stats = *EnemyStatsDataTable->FindRow<FEnemyStats>(FName("MinionLane"), "");
		}
		
		GetMesh()->SetAnimClass(Stats.AnimationClass);
		GetMesh()->SetSkeletalMeshAsset(Stats.SkeletalMesh);
	}
}

void AMinionLane::BeginPlay()
{
	Super::BeginPlay();

	if (EnemyStatsDataTable)
	{
		if (Name == EEnemyName::EEN_MinionLane)
		{
			Stats = *EnemyStatsDataTable->FindRow<FEnemyStats>(FName("MinionLane"), "");
		}
	}
}

void AMinionLane::AttackCharacter()
{
	Super::AttackCharacter();
}
