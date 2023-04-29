// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Boss/Gideon/BossGideon.h"
#include "Animation/BossAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Enemy/Boss/Gideon/DarkStone.h"

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

	if (State == EBossState::EES_Chasing && GetVelocity().Length() == 0.f)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		Attack();
	}
	else if (State == EBossState::EES_Resting && CombatTarget)
	{
		RotateBodyToCombatTarget(DeltaTime);
	}
}

void ABossGideon::Attack()
{
	Super::Attack();

	UBossAnimInstance* AnimInstance = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->PlayAttackAnimation();
	}
}

void ABossGideon::HandleSkillOne()
{
	Super::HandleSkillOne();
}

void ABossGideon::HandleSkillTwo()
{
	Super::HandleSkillTwo();
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