// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/BossAnimInstance.h"
#include "Enemy/Boss/Gideon/BossGideon.h"
#include "Component/BossAbilityComponent.h"

void UBossAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OnMontageEnded.AddDynamic(this, &UBossAnimInstance::OnEndMontage);
}

void UBossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ABossBase* Boss = Cast<ABossBase>(TryGetPawnOwner());
	if (Boss)
	{
		Speed = Boss->GetVelocity().Length();
	}
}

FBossAnimation UBossAnimInstance::GetAnimation()
{
	ABossBase* Boss = Cast<ABossBase>(TryGetPawnOwner());
	if (Boss && AnimDataTable)
	{
		const FName& BossCode = Boss->GetCode();
		if (BossCode.IsValid())
		{
			const FBossAnimation& BossAnimation = *AnimDataTable->FindRow<FBossAnimation>(BossCode, "");
			return BossAnimation;
		}
	}
	return FBossAnimation();
}

void UBossAnimInstance::PlayOpeningAnimation()
{
	const FBossAnimation& Animations = GetAnimation();
	UAnimMontage* Montage = Animations.Opening;
	if (Montage)
	{
		Montage_Play(Montage);
	}
}

void UBossAnimInstance::PlayAttackAnimation()
{
	const FBossAnimation& Animations = GetAnimation();
	UAnimMontage* Montage = Animations.Attack;
	if (Montage)
	{
		Montage_Play(Montage);
	}
}

void UBossAnimInstance::PlaySkillOneAnimation()
{
	const FBossAnimation& Animations = GetAnimation();
	UAnimMontage* Montage = Animations.SkillOne;
	if (Montage)
	{
		Montage_Play(Montage);
	}
}

void UBossAnimInstance::PlaySkillTwoAnimation()
{
	const FBossAnimation& Animations = GetAnimation();
	UAnimMontage* Montage = Animations.SkillTwo;
	if (Montage)
	{
		Montage_Play(Montage);
	}
}

void UBossAnimInstance::PlaySkillThreeAnimation()
{
	const FBossAnimation& Animations = GetAnimation();
	UAnimMontage* Montage = Animations.SkillThree;
	if (Montage)
	{
		Montage_Play(Montage);
	}
}

void UBossAnimInstance::PlayVictoryAnimation()
{
	const FBossAnimation& Animations = GetAnimation();
	UAnimMontage* Montage = Animations.Victory;
	if (Montage)
	{
		Montage_Play(Montage);
	}
}

void UBossAnimInstance::PlayBackStepAnimation()
{
	const FBossAnimation& Animations = GetAnimation();
	UAnimMontage* Montage = Animations.BackStep;
	if (Montage)
	{
		Montage_Play(Montage);
	}
}

void UBossAnimInstance::PlayHitReactAnimation()
{
	const FBossAnimation& Animations = GetAnimation();
	UAnimMontage* Montage = Animations.HitReact;
	if (Montage)
	{
		Montage_Play(Montage);
	}
}

void UBossAnimInstance::PlayDeadAnimation()
{
	const FBossAnimation& Animations = GetAnimation();
	UAnimMontage* Montage = Animations.Dead;
	if (Montage)
	{
		Montage_Play(Montage);
	}
}

void UBossAnimInstance::OnEndAttackTimer()
{
	ABossGideon* Boss = Cast<ABossGideon>(TryGetPawnOwner());
	if (Boss && Boss->HasTarget())
	{
		UBossAbilityComponent* AbilityComponent =Boss->GetAbilityComponent();
		if (AbilityComponent)
		{
			AbilityComponent->BackStep();
		}
	}
}

void UBossAnimInstance::OnEndHitReactTimer()
{
	ABossGideon* Boss = Cast<ABossGideon>(TryGetPawnOwner());
	if (Boss && Boss->HasTarget())
	{
		UBossAbilityComponent* AbilityComponent = Boss->GetAbilityComponent();
		if (AbilityComponent)
		{
			AbilityComponent->BackStep();
		}
	}
}

void UBossAnimInstance::ClearTimerHandle()
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void UBossAnimInstance::OnEndMontage(UAnimMontage* Montage, bool bInterrupted)
{
	ABossBase* Boss = Cast<ABossBase>(TryGetPawnOwner());
	if (Boss == nullptr) return;

	const FBossAnimation& Animations = GetAnimation();
	if (Montage == Animations.Opening)
	{
		Boss->FindTarget();
		Boss->ChaseTarget();
	}
	else if (Montage == Animations.Attack)
	{
		Boss->SetState(EBossState::EBS_Resting);
		GetWorld()->GetTimerManager().SetTimer(EndAttackTimer,this, &UBossAnimInstance::OnEndAttackTimer, AttackTimerRate, false);
	}
	else if (Montage == Animations.BackStep)
	{
		Boss->ChaseTarget();
	}
	else if (Montage == Animations.SkillOne)
	{
		Boss->SetState(EBossState::EBS_Resting);
		GetWorld()->GetTimerManager().SetTimer(EndAttackTimer, this, &UBossAnimInstance::OnEndAttackTimer, AttackTimerRate, false);
	}
	else if (Montage == Animations.SkillTwo)
	{
		Boss->SetState(EBossState::EBS_Resting);
		GetWorld()->GetTimerManager().SetTimer(EndAttackTimer, this, &UBossAnimInstance::OnEndAttackTimer, AttackTimerRate, false);
	}
	else if (Montage == Animations.HitReact)
	{
		Boss->SetState(EBossState::EBS_Resting);
		GetWorld()->GetTimerManager().SetTimer(EndHitReactTimer, this, &UBossAnimInstance::OnEndHitReactTimer, HitReactTimerRate, false);
	}
}