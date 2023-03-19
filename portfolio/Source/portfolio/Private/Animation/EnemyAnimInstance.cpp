// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyAnimInstance.h"
#include "Data/EnemyAnimDataAsset.h"
#include "Enemy/EnemyBase.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	if (AnimDataAsset)
	{
		AEnemyBase* Enemy = Cast<AEnemyBase>(GetOwningActor());
		if (Enemy)
		{
			const EEnemyName Name = Enemy->GetName();
			HitReactOnGround = AnimDataAsset->EnemyAnimDatas.Find(Name)->HitReactOnGround;
			IdleWalkRun = AnimDataAsset->EnemyAnimDatas.Find(Name)->IdleWalkRun;
			Dead = AnimDataAsset->EnemyAnimDatas.Find(Name)->Dead;
			
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

void UEnemyAnimInstance::PlayDead()
{
	if (Dead)
	{
		Montage_Play(Dead);
	}
}
