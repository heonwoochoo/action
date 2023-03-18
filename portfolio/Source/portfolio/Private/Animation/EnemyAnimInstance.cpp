// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyAnimInstance.h"

UAnimMontage* UEnemyAnimInstance::GetHitReactMontage() const
{
	return nullptr;
}

void UEnemyAnimInstance::PlayHitReactMontage()
{
	if (HitReactMontage)
	{
		Montage_Play(HitReactMontage);
	}
}
