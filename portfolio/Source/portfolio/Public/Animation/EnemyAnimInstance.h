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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	UAnimMontage* HitReactOnGround;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	UAnimMontage* HitReactOnAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	UBlendSpace1D* IdleWalkRun;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	UAnimMontage* Dead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	UAnimMontage* Attack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	EEnemyState State;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Properties")
	UDataTable* EnemyDefaultAnimationsDataTable;
	

public:
	void PlayHitReactOnGround();
	void PlayHitReactOnAir();
	void PlayDead();
	void PlayAttack();
};