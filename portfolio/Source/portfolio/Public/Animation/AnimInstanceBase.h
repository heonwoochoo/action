// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Data/CharacterDataAsset.h"
#include "AnimInstanceBase.generated.h"

class AportfolioCharacter;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Animation|Skill")
	UAnimMontage* SkillOne;

private:
	UPROPERTY(VisibleAnywhere, category = "Character|Movement")
	float ForwardSpeed = 0.f;

	UPROPERTY(VisibleAnywhere, category = "Character|Movement")
	float SideSpeed = 0.f;

	UPROPERTY(VisibleAnywhere, category = "Character|Movement")
	FVector Velocity = FVector(0.f);

	UPROPERTY(VisibleAnywhere, category = "Character")
	AportfolioCharacter* Character = nullptr;

	
	

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe))
	float GetForwardSpeed() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe))
	float GetSideSpeed() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe))
	FVector GetVelocity() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe))
	AportfolioCharacter* GetCharacter() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe))
	ECharacterClass GetCharacterClass() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe))
	ECharacterEquipState GetCharacterEquipState() const;

	UAnimMontage* GetDefaultAttackMontage() const;

	UAnimMontage* GetDefaultDoubleJumpMontage() const;

	UAnimMontage* GetDefaultDefaultEvadeMontage() const;

	UAnimMontage* GetSkillOne() const;
};
