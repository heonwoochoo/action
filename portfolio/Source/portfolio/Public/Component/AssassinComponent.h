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

private:
	//==============================
	//			1번 스킬
	//==============================
	// 날아가는 투사체의 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties|SkillOne|Projectile", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AKnifeProjectile> KnifeClass;

	// 투사체에서 생성된 인스턴스
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties|SkillOne|Projectile", meta = (AllowPrivateAccess = "true"))
	AKnifeProjectile* Knife;

	// 투사체의 유도를 감지하는 거리
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties|SkillOne", meta = (AllowPrivateAccess = "true"))
	float TraceDistance = 2000.f;

	// 투사체의 유도를 감지하는 원 반경
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties|SkillOne", meta = (AllowPrivateAccess = "true"))
	float AutoDirectionRange = 300.f;

	// 투사체를 날릴 적을 찾는 함수
	AActor* FindEnemy();

	// Trace에 Overlap 된 유도 타겟 설정
	AActor* TargetEnemy;

	// 투사체 적중시 설정된 Dash 타겟
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties|SkillOne", meta = (AllowPrivateAccess = "ture"))
	AActor* DashTarget;

	// 1번 스킬의 첫 번째 동작 실행
	void SkillOne_First();

	// 1번 스킬의 두 번째 동작 실행
	void SkillOne_Second();

	// 타겟 방향으로 Motion Warping
	void RotateToTarget(AActor* Target);

	// Montage Section
	FName SectionName_First = "Assassin_Skill1_First";
	FName SectionName_Second = "Assassin_Skill1_Second";

	//==============================
	//			2번 스킬
	//==============================
	// 첫 번째 동작시 대시 거리
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties|SkillTwo", meta = (AllowPrivateAccess = "true"))
	float SkillTwoDashDistance = 1000.f;

	// 대시 동작 중 범위에 걸린 적을 체크
	void SkillTwoDashOverlap();

	// 대시 동작 시 true로 바뀌고 종료시 false
	bool bCheckSkillTwoDashOverlap = false;
	
	UFUNCTION(BlueprintCallable)
	void SetCheckSkillTwoDashOverlap(bool CanOverlap);

	// 내려찍을 때 카메라 효과를 설정하는 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "ture"))
	TSubclassOf<UCameraShakeBase> CameraShakeExplosion;

\
	//==============================
	//			3번 스킬
	//==============================
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties|SkillThree|SkillEffect", meta = (AllowPrivateAccess = "ture"))
	UNiagaraSystem* SkillThreeBloodAOE;
	
	// 기둥이 생성되어 적을 끌어당기는 시간을 조절하는 타이머 핸들
	FTimerHandle SkillThreeSpawnTimer;

	// 기둥 스폰 핸들 종료시 호출되는 함수
	void SetFalseSkillThreeAttack();

	bool bAttackSKillThree = false;

	// 기둥 생성 동안 적에게 가하는 다단히트를 조절하는 타이머 핸들
	FTimerHandle SkillThreeHitTimer;

	// 타이머 종료 후 히트를 가능한 상태로 만드는 함수
	void SkillThreeHitTimerEnd();

	// true시 적을 히트
	bool bMultiHit = true;

	// 적을 기둥이 생성된 위치 중앙으로 끌어당김
	void PullEnemyToCenter();

	// 적에게 데미지
	void AttackMultiHit(AEnemyBase* Enemy);

	FVector SkillThreeSpawnLocation;

	// 기둥 생성 후 히트가 지속되는 시간
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties|Skill", meta = (AllowPrivateAccess = "ture"))
	float SkillThreeHitDuration = 3.0f;

	// 다단히트 간격
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties|Skill", meta = (AllowPrivateAccess = "ture"))
	float MultiHitDeltaTime = 0.5f;

public:
	//==============================
	//			1번 스킬
	//==============================
	virtual void HandleSkillOne() override;

	// Anim notify를 통해 호출되는 함수
	UFUNCTION(BlueprintCallable)
	void ThrowKnife();

	void SetDashTarget(AActor* Target);
		
	//==============================
	//			2번 스킬
	//==============================
	virtual void HandleSkillTwo() override;

	// Anim notify를 통해 호출되는 함수
	UFUNCTION(BlueprintCallable)
	void SkillTwoEndEffect();

	//==============================
	//			3번 스킬
	//==============================
	virtual void HandleSkillThree() override;

	// Anim notify를 통해 호출되는 함수
	UFUNCTION(BlueprintCallable)
	void SpawnSkillThreeEffect();


	//==============================
	//			4번 스킬
	//==============================
	virtual void HandleSkillFour() override;
};
