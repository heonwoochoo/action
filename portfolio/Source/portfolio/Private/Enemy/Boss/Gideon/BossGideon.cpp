// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Boss/Gideon/BossGideon.h"
#include "Animation/BossAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Enemy/Boss/Gideon/DarkStone.h"
#include "MotionWarpingComponent.h"
#include "Enemy/Boss/Gideon/DarkWave.h"
#include "Enemy/Boss/Gideon/DarkSword.h"

ABossGideon::ABossGideon()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABossGideon::BeginPlay()
{
	Super::BeginPlay();
}

void ABossGideon::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void ABossGideon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (State == EBossState::EBS_Chasing && GetVelocity().Length() == 0.f)
	{
		//Attack();
		//HandleSkillOne();
		HandleSkillTwo();
	}
}

void ABossGideon::Attack()
{
	Super::Attack();
	SetState(EBossState::EBS_Attacking);
	SetMotionWarpRotationToTarget();

	UBossAnimInstance* AnimInstance = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->PlayAttackAnimation();
	}
}

void ABossGideon::BackStep()
{
	Super::BackStep();
	if (CombatTarget)
	{
		// 모션워핑 업데이트
		SetMotionWarpRotationToTarget();

		// 뒤로
		const FVector& BackLocation = GetActorLocation() - GetActorForwardVector() * 300.f;
		MotionWarpingComponent->AddOrUpdateWarpTargetFromLocation(FName("MoveBackward"), BackLocation);
	}

	UBossAnimInstance* AnimInstance = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->PlayBackStepAnimation();
	}
}

void ABossGideon::HandleSkillOne()
{
	Super::HandleSkillOne();
	SetState(EBossState::EBS_Attacking);

	SetMotionWarpRotationToTarget();

	UBossAnimInstance* AnimInstance = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->PlaySkillOneAnimation();
	}
}

void ABossGideon::HandleSkillTwo()
{
	Super::HandleSkillTwo();
	SetState(EBossState::EBS_Attacking);

	SetMotionWarpRotationToTarget();

	UBossAnimInstance* AnimInstance = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->PlaySkillTwoAnimation();
	}
}

void ABossGideon::HandleSkillThree()
{
	Super::HandleSkillThree();
}

void ABossGideon::SpawnDarkStone()
{
	const FVector& Location = GetMesh()->GetSocketLocation(FName("RightHandSocket"));

	ADarkStone* DarkStone = GetWorld()->SpawnActor<ADarkStone>(DarkStoneClass, Location, GetActorRotation());
	if (DarkStone)
	{
		DarkStone->SetOwner(this);
		DarkStone->SetDamage(Stats.Damage);
		DarkStone->SetTarget(CombatTarget);
	}
}

void ABossGideon::SpawnDarkWave()
{
	const TArray<FName>& SocketNames = { FName(TEXT("AttackSocket1")),FName(TEXT("AttackSocket2")) ,FName(TEXT("AttackSocket3")) };

	for (const auto& SocketName : SocketNames)
	{
		ADarkWave* DarkWave = GetWorld()->SpawnActor<ADarkWave>(DarkWaveClass);
		if (DarkWave)
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
			DarkWave->AttachToComponent(GetMesh(), AttachmentRules, SocketName);
			DarkWave->SetOwner(this);
			DarkWave->SetDamage(Stats.Damage * 0.3f);
		}
	}
}

void ABossGideon::SpawnDarkSword()
{
	if (CombatTarget)
	{
		const FVector& SpawnLocation = GetActorLocation() + GetActorUpVector() * DarkSwordSpawnHeight;

		ADarkSword* DarkSword = GetWorld()->SpawnActor<ADarkSword>(DarkSwordClass, SpawnLocation, GetActorRotation());
		if (DarkSword)
		{
			DarkSword->SetOwner(this);
			DarkSword->SetTarget(CombatTarget);
			DarkSword->SetDamage(Stats.Damage);
		}
	}
}
