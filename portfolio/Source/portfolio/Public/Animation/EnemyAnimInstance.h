// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* HitReactMontage;

public:
	UAnimMontage* GetHitReactMontage() const;

	void PlayHitReactMontage();
};
