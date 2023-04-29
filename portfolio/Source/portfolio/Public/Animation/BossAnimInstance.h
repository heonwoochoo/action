﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Types/EnemyTypes.h"
#include "BossAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UBossAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Properties")
	UDataTable* AnimDataTable;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	float Speed = 0.f;


public:
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe))
	FBossAnimation GetAnimation();

	UFUNCTION()
	virtual void OnEndMontage(UAnimMontage* Montage, bool bInterrupted);

	void PlayOpeningAnimation();
};
