// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/BossAnimInstance.h"
#include "Enemy/BossBase.h"

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

void UBossAnimInstance::OnEndMontage(UAnimMontage* Montage, bool bInterrupted)
{
	const FBossAnimation& Animations = GetAnimation();
	if (Montage == Animations.Opening)
	{
		ABossBase* Boss = Cast<ABossBase>(TryGetPawnOwner());
		if (Boss)
		{
			Boss->FindTarget();
			Boss->ChaseTarget();
		}
	}
}
