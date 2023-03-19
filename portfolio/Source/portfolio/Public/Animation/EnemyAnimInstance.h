// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyTypes.h"
#include "EnemyAnimInstance.generated.h"

class UEnemyAnimDataAsset;
class UAnimMontage;
class UBlendSpace1D;

UCLASS()
class PORTFOLIO_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	UAnimMontage* HitReactOnGround;

	UPROPERTY(BlueprintReadOnly)
	UBlendSpace1D* IdleWalkRun;

	UPROPERTY(BlueprintReadOnly)
	UAnimMontage* Dead;

	UPROPERTY(BlueprintReadOnly)
	float Speed;

	UPROPERTY(BlueprintReadOnly)
	EEnemyState State;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UEnemyAnimDataAsset* AnimDataAsset;


public:
	void PlayHitReactOnGround();
	void PlayDead();

};