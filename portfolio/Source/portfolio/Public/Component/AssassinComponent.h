// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/AbilityComponent.h"
#include "AssassinComponent.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UAssassinComponent : public UAbilityComponent
{
	GENERATED_BODY()
	

public:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual void BeginPlay() override;

protected:
	// ���ư��� ����ü�� Ŭ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	TSubclassOf<AKnifeProjectile> KnifeClass;

	// ����ü���� ������ �ν��Ͻ�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	AKnifeProjectile* Knife;

	// ����ü�� ������ �����ϴ� �Ÿ�
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	float TraceDistance = 2000.f;

	// ����ü�� ������ �����ϴ� �� �ݰ�
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	float AutoDirectionRange = 300.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties|Montage")
	FName SectionName_First = "Assassin_Skill1_First";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties|Montage")
	FName SectionName_Second = "Assassin_Skill1_Second";

	

private:
	AActor* TargetEnemy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "ture"))
	AActor* DashTarget;

	AActor* FindEnemy();

	void SkillOne_First();

	void SkillOne_Second();

	void RotateToTarget(AActor* Target);

public:

	UFUNCTION(BlueprintCallable)
	void ThrowKnife();

	void SetDashTarget(AActor* Target);

	virtual void HandleSkillOne() override;
	virtual void HandleSkillTwo() override;
};
