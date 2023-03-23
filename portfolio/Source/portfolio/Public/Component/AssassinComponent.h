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
	// 날아가는 투사체의 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	TSubclassOf<AKnifeProjectile> KnifeClass;

	// 투사체에서 생성된 인스턴스
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	AKnifeProjectile* Knife;

	// 투사체의 유도를 감지하는 거리
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	float TraceDistance = 2000.f;

	// 투사체의 유도를 감지하는 원 반경
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
};
