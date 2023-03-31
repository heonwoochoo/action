// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyAnimInstance.h"
#include "Enemy/EnemyBase.h"
#include "EnemyTypes.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AEnemyBase* Enemy = Cast<AEnemyBase>(GetOwningActor());
	if (Enemy && EnemyDefaultAnimationsDataTable)
	{
		HitReactOnGround = EnemyDefaultAnimationsDataTable->FindRow<FEnemyDefaultAnimation>(FName("Man"), "")->HitReactOnGround;
		HitReactOnAir = EnemyDefaultAnimationsDataTable->FindRow<FEnemyDefaultAnimation>(FName("Man"), "")->HitReactOnAir;
		IdleWalkRun = EnemyDefaultAnimationsDataTable->FindRow<FEnemyDefaultAnimation>(FName("Man"), "")->IdleWalkRun;
		Dead = EnemyDefaultAnimationsDataTable->FindRow<FEnemyDefaultAnimation>(FName("Man"), "")->Dead;
		Attack = EnemyDefaultAnimationsDataTable->FindRow<FEnemyDefaultAnimation>(FName("Man"), "")->Attack;
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
		UE_LOG(LogTemp, Warning, TEXT("play Dead Animation"));
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
