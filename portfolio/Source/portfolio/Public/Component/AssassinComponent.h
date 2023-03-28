// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/AbilityComponent.h"
#include "AssassinComponent.generated.h"

class UCameraShakeBase;
class AEnemyBase;
class UNiagaraSystem;
UCLASS()
class PORTFOLIO_API UAssassinComponent : public UAbilityComponent
{
	GENERATED_BODY()
	

public:
	UAssassinComponent();

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	/** Skill One */
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

	/** Skill Two */
	float SkillTwoDashDistance = 1000.f;

	UFUNCTION(BlueprintCallable)
	void SetCheckSkillTwoDashOverlap(bool CanOverlap);

	// �������� �� ī�޶� ȿ��
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	TSubclassOf<UCameraShakeBase> CameraShakeExplosion;

private:
	/** Skill One */
	AActor* TargetEnemy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "ture"))
	AActor* DashTarget;

	AActor* FindEnemy();

	void SkillOne_First();

	void SkillOne_Second();

	void RotateToTarget(AActor* Target);

	/** Skill Two */
	void SkillTwoDashOverlap();
	bool bCheckSkillTwoDashOverlap = false;

	/** Skill Three */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties|SkillEffect", meta = (AllowPrivateAccess = "ture"))
	UNiagaraSystem* SkillThreeBloodAOE;

	FTimerHandle SkillThreeSpawnTimer;

	FTimerHandle SkillThreeHitTimer;

	void SkillThreeHitTimerEnd();

	bool bMultiHit = true;

	void SetFalseSkillThreeAttack();

	bool bAttackSKillThree = false;

	FVector SkillThreeSpawnLocation;

	void PullEnemyToCenter();

	void AttackMultiHit(AEnemyBase* Enemy);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties|Skill", meta = (AllowPrivateAccess = "ture"))
	float SkillThreeHitDuration = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties|Skill", meta = (AllowPrivateAccess = "ture"))
	float MultiHitDeltaTime = 0.5f;

public:
	/** Skill One */
	virtual void HandleSkillOne() override;

	UFUNCTION(BlueprintCallable)
	void ThrowKnife();

	void SetDashTarget(AActor* Target);
		
	/** Skill Two */
	virtual void HandleSkillTwo() override;

	UFUNCTION(BlueprintCallable)
	void SkillTwoEndEffect();

	/** Skill Three */
	virtual void HandleSkillThree() override;
	UFUNCTION(BlueprintCallable)
	void SpawnSkillThreeEffect();


	/** Skill Four */
	virtual void HandleSkillFour() override;
};
