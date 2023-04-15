// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyAnimInstance.h"
#include "Enemy/EnemyBase.h"
#include "Types/EnemyTypes.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AEnemyBase* Enemy = Cast<AEnemyBase>(GetOwningActor());
	
	FName RowName = "";
	if (Enemy)
	{
		EEnemyName EnemyName = Enemy->GetName();
		switch (EnemyName)
		{
		case EEnemyName::EEN_Man:
			RowName = "Man";
			break;
		case EEnemyName::EEN_MinionLane:
			RowName = "MinionLane";
			break;
		case EEnemyName::EEN_None:
			RowName = "";
			break;
		}

		if (Enemy && EnemyDefaultAnimationsDataTable && EnemyName != EEnemyName::EEN_None)
		{
			HitReactOnGround = EnemyDefaultAnimationsDataTable->FindRow<FEnemyDefaultAnimation>(RowName, "")->HitReactOnGround;
			HitReactOnAir = EnemyDefaultAnimationsDataTable->FindRow<FEnemyDefaultAnimation>(RowName, "")->HitReactOnAir;
			IdleWalkRun = EnemyDefaultAnimationsDataTable->FindRow<FEnemyDefaultAnimation>(RowName, "")->IdleWalkRun;
			Dead = EnemyDefaultAnimationsDataTable->FindRow<FEnemyDefaultAnimation>(RowName, "")->Dead;
			Attack = EnemyDefaultAnimationsDataTable->FindRow<FEnemyDefaultAnimation>(RowName, "")->Attack;
		}
	}
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AEnemyBase* Enemy = Cast<AEnemyBase>(GetOwningActor());
	if (Enemy)
	{
		Speed = Enemy->GetVelocity().Length();
		State = Enemy->GetState();
	}
}

void UEnemyAnimInstance::PlayHitReactOnGround()
{
	if (HitReactOnGround)
	{
		Montage_Play(HitReactOnGround);
	}
}

void UEnemyAnimInstance::PlayHitReactOnAir()
{
	if (HitReactOnAir)
	{
		Montage_Play(HitReactOnAir);
	}
}

void UEnemyAnimInstance::PlayDead()
{
	if (Dead)
	{
		Montage_Play(Dead);
	}
}

void UEnemyAnimInstance::PlayAttack()
{
	if (Attack)
	{
		Montage_Play(Attack);
	}
}
