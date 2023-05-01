// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/BossAbilityComponent.h"
#include "Enemy/Boss/Gideon/BossGideon.h"
#include "Animation/BossAnimInstance.h"
#include "MotionWarpingComponent.h"
#include "Enemy/Boss/Gideon/DarkStone.h"
#include "Enemy/Boss/Gideon/DarkWave.h"
#include "Enemy/Boss/Gideon/DarkSword.h"
UBossAbilityComponent::UBossAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UBossAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	BossGideon = Cast<ABossGideon>(GetOwner());
}



void UBossAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBossAbilityComponent::Attack()
{
	if (BossGideon)
	{
		BossGideon->SetState(EBossState::EBS_Attacking);
		BossGideon->SetMotionWarpRotationToTarget();

		UBossAnimInstance* AnimInstance = Cast<UBossAnimInstance>(BossGideon->GetMesh()->GetAnimInstance());
		if (AnimInstance)
		{
			AnimInstance->PlayAttackAnimation();
		}
	}
}

void UBossAbilityComponent::BackStep()
{
	if (BossGideon && BossGideon->GetCombatTarget())
	{
		// 모션워핑 업데이트
		BossGideon->SetMotionWarpRotationToTarget();


		// 4방향 중 랜덤 이동
		const FVector& Forward = BossGideon->GetActorLocation() + BossGideon->GetActorForwardVector() * StepOffset;
		const FVector& Backward = BossGideon->GetActorLocation() - BossGideon->GetActorForwardVector() * StepOffset;
		const FVector& Right = BossGideon->GetActorLocation() + BossGideon->GetActorRightVector() * StepOffset;
		const FVector& Left = BossGideon->GetActorLocation() - BossGideon->GetActorRightVector() * StepOffset;

		const TArray<FVector>& Directions = { Forward, Backward, Right, Left };
		const int32 RandNum = FMath::RandRange(0, 3);

		const FVector& SelectedLocation = Directions[RandNum];

		UMotionWarpingComponent* MotionWarpingComponent = BossGideon->GetMotionWarpingComponent();
		if (MotionWarpingComponent)
		{
			MotionWarpingComponent->AddOrUpdateWarpTargetFromLocation(FName("MoveRandomDirection"), SelectedLocation);
		}	

		UBossAnimInstance* AnimInstance = Cast<UBossAnimInstance>(BossGideon->GetMesh()->GetAnimInstance());
		if (AnimInstance)
		{
			AnimInstance->PlayBackStepAnimation();
		}
	}
}

void UBossAbilityComponent::HandleSkillOne()
{
	if (BossGideon)
	{
		BossGideon->SetState(EBossState::EBS_Attacking);
		BossGideon->SetMotionWarpRotationToTarget();

		UBossAnimInstance* AnimInstance = Cast<UBossAnimInstance>(BossGideon->GetMesh()->GetAnimInstance());
		if (AnimInstance)
		{
			AnimInstance->PlaySkillOneAnimation();
		}
	}
}

void UBossAbilityComponent::HandleSkillTwo()
{
	if (BossGideon)
	{
		BossGideon->SetState(EBossState::EBS_Attacking);
		BossGideon->SetMotionWarpRotationToTarget();

		UBossAnimInstance* AnimInstance = Cast<UBossAnimInstance>(BossGideon->GetMesh()->GetAnimInstance());
		if (AnimInstance)
		{
			AnimInstance->PlaySkillTwoAnimation();
		}
	}
}

void UBossAbilityComponent::HandleSkillThree()
{

}

void UBossAbilityComponent::SpawnDarkStone()
{
	if (BossGideon && BossGideon->GetCombatTarget())
	{
		const FVector& Location = BossGideon->GetMesh()->GetSocketLocation(FName("RightHandSocket"));

		ADarkStone* DarkStone = GetWorld()->SpawnActor<ADarkStone>(DarkStoneClass, Location, BossGideon->GetActorRotation());
		if (DarkStone)
		{
			DarkStone->SetOwner(BossGideon);
			DarkStone->SetDamage(BossGideon->GetStats().Damage);
			DarkStone->SetTarget(BossGideon->GetCombatTarget());
		}
	}
}

void UBossAbilityComponent::SpawnDarkWave()
{
	if (BossGideon)
	{
		const TArray<FName>& SocketNames = { FName(TEXT("AttackSocket1")),FName(TEXT("AttackSocket2")) ,FName(TEXT("AttackSocket3")) };

		for (const auto& SocketName : SocketNames)
		{
			ADarkWave* DarkWave = GetWorld()->SpawnActor<ADarkWave>(DarkWaveClass);
			if (DarkWave)
			{
				FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
				DarkWave->AttachToComponent(BossGideon->GetMesh(), AttachmentRules, SocketName);
				DarkWave->SetOwner(BossGideon);
				DarkWave->SetDamage(BossGideon->GetStats().Damage * 0.3f);
			}
		}
	}
}

void UBossAbilityComponent::SpawnDarkSword()
{
	if (BossGideon && BossGideon->GetCombatTarget())
	{
		const FVector& Location1 = BossGideon->GetActorLocation() + BossGideon->GetActorUpVector() * DarkSwordSpawnHeight;
		const FVector& Location2 = Location1 + BossGideon->GetActorRightVector() * DarkSwordSideOffset;
		const FVector& Location3 = Location1 - BossGideon->GetActorRightVector() * DarkSwordSideOffset;

		const TArray<FVector>& Locations = { Location1, Location2, Location3 };

		for (const auto& Location : Locations)
		{
			ADarkSword* DarkSword = GetWorld()->SpawnActor<ADarkSword>(DarkSwordClass, Location, BossGideon->GetActorRotation());
			if (DarkSword)
			{
				DarkSword->SetOwner(BossGideon);
				DarkSword->SetTarget(BossGideon->GetCombatTarget());
				DarkSword->SetDamage(BossGideon->GetStats().Damage);
			}
		}
	}
}

void UBossAbilityComponent::ClearTimerHandle()
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}
