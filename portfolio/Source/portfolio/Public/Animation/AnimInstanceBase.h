// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstanceBase.generated.h"

class ADefaultCharacter;
class UDataTable;

UCLASS()
class PORTFOLIO_API UAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Animation|Default")
	UAnimMontage* DefaultAttackMontage = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Animation|Default")
	UAnimSequence* DefaultJump = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Animation|Default")
	UAnimMontage* DefaultDoubleJumpMontage = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Animation|Default")
	UBlendSpace* DefaultWalkRunBlendSpace = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Animation|Default")
	UAnimSequence* DefaultEquippedIdle = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Animation|Default")
	UAnimSequence* DefaultUnequippedIdle = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Animation|Default")
	UAnimMontage* DefaultEvadeMontage = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Animation|Default")
	UAnimMontage* DefaultHitReactMontage = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Animation|Default")
	UAnimSequence* DefaultDead = nullptr;

private:
	UPROPERTY(VisibleAnywhere, category = "Character|Movement")
	float ForwardSpeed = 0.f;

	UPROPERTY(VisibleAnywhere, category = "Character|Movement")
	float SideSpeed = 0.f;

	UPROPERTY(VisibleAnywhere, category = "Character|Movement")
	FVector Velocity = FVector(0.f);

	UPROPERTY(VisibleAnywhere, category = "Character")
	ADefaultCharacter* Character = nullptr;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDataTable* DefaultAnimationDataTable;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe))
	float GetForwardSpeed() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe))
	float GetSideSpeed() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe))
	FVector GetVelocity() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe))
	ADefaultCharacter* GetCharacter() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe))
	ECharacterClass GetCharacterClass() const;
	
	UAnimMontage* GetDefaultAttackMontage() const;

	UAnimMontage* GetDefaultDoubleJumpMontage() const;

	UAnimMontage* GetDefaultEvadeMontage() const;

	UAnimMontage* GetDefaultHitReactMontage() const;

	void PlayHitReact();
};
