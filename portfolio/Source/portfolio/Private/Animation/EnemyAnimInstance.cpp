// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyAnimInstance.h"
#include "Enemy/EnemyBase.h"
#include "Types/EnemyTypes.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AEnemyBase* Enemy = Cast<AEnemyBase>(GetOwningActor());
	if (Enemy)
	{
		const FName& EnemyCode = Enemy->GetEnemyCode();
		if (Enemy && EnemyDefaultAnimationsDataTable && EnemyCode.IsValid())
		{
			HitReactOnGround = EnemyDefaultAnimationsDataTable->FindRow<FEnemyDefaultAnimation>(EnemyCode, "")->HitReactOnGround;
			HitReactOnAir = EnemyDefaultAnimationsDataTable->FindRow<FEnemyDefaultAnimation>(EnemyCode, "")->HitReactOnAir;
			IdleWalkRun = EnemyDefaultAnimationsDataTable->FindRow<FEnemyDefaultAnimation>(EnemyCode, "")->IdleWalkRun;
			Dead = EnemyDefaultAnimationsDataTable->FindRow<FEnemyDefaultAnimation>(EnemyCode, "")->Dead;
			Attack = EnemyDefaultAnimationsDataTable->FindRow<FEnemyDefaultAnimation>(EnemyCode, "")->Attack;
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
