// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterTypes.h"
#include "Assassin_SkillOne.generated.h"

class UCharacterSkillAsset;
class UAnimInstanceBase;
class AportfolioCharacter;
class AKnifeProjectile;

UCLASS()
class PORTFOLIO_API AAssassin_SkillOne : public AActor
{
	GENERATED_BODY()
	
public:	
	AAssassin_SkillOne();

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	UCharacterSkillAsset* SkillAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	FCharacterSkill SkillData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	TSubclassOf<AKnifeProjectile> KnifeClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	AKnifeProjectile* Knife;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	float TraceDistance = 2000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	float AutoDirectionRange = 300.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties|Montage")
	FName SectionName_First = "Assassin_Skill1_First";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties|Montage")
	FName SectionName_Second = "Assassin_Skill1_Second";

private:
	AportfolioCharacter* Character;

	UAnimInstanceBase* AnimInstance;

	AActor* TargetEnemy;

	AActor* DashTarget;

	AActor* FindEnemy();

	void FirstAction();

	void SecondAction();

	void RotateToTarget(AActor* Target);

public:

	UFUNCTION(BlueprintCallable)
	void ThrowKnife();

	void PlayAction();
};
