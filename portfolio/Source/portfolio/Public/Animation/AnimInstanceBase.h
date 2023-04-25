// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Types/CharacterTypes.h"
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

	UFUNCTION()
	void OnEndMontage(UAnimMontage* AnimMontage, bool bInterrupted);

private:
	UPROPERTY(VisibleAnywhere, category = "Character|Movement")
	float ForwardSpeed = 0.f;

	UPROPERTY(VisibleAnywhere, category = "Character|Movement")
	float SideSpeed = 0.f;

	UPROPERTY(VisibleAnywhere, category = "Character|Movement")
	FVector Velocity = FVector(0.f);

	UPROPERTY(VisibleAnywhere, category = "Character")
	ADefaultCharacter* Character = nullptr;

	UPROPERTY(VisibleAnywhere, category = "Character")
	FCharacterDefaultAnimation DefaultAnimations;

	FName ChangedWeaponItemCode;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDataTable* DefaultAnimationDataTable;

	UFUNCTION(BlueprintCallable)
	FName GetChangedWeaponItemCode() const;
	
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
	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe))
	FCharacterDefaultAnimation GetDefaultAnimations() const;

	UAnimMontage* GetDefaultAttackMontage() const;

	UAnimMontage* GetDefaultDoubleJumpMontage() const;

	UAnimMontage* GetDefaultEvadeMontage() const;

	UAnimMontage* GetDefaultHitReactMontage() const;

	void PlayHitReact();

	void PlayEquipWeapon();
};
