// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/AbilityComponent.h"
#include "AssassinComponent.generated.h"

class UCameraShakeBase;
class AEnemyBase;
class UNiagaraSystem;
class UParticleSystem;
class AKnifeProjectile;
class AArrowSpline;

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

	// 투사체가 적중하면 적을 따라 생기는 화살표 스플라인
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties|SkillOne|Projectile", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AArrowSpline> ArrowSplineClass;

	AArrowSpline* ArrowSpline;

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties|SkillOne", meta = (AllowPrivateAccess = "true"))
	AActor* DashTarget;

	// 대쉬상태 비활성화를 위한 타이머
	FTimerHandle DashTimerHandle;

	/** 1번 스킬의 첫 번째 동작 실행
	* 수리검을 던질 때 타겟이 있는지 확인합니다. ( Anim Notify에서 FindEnemy() 호출)
	* 타겟이 있다면, 캐릭터의 로테이션(Z Axis)을 해당 타겟으로 워핑합니다.
	* 수리검 방향은 타겟을, 없으면 캐릭터의 Forward를 향합니다.
	*/
	void SkillOne_First();

	/** 1번 스킬의 두 번째 동작 실행
	* 대쉬 타켓으로 지정된 대상으로 워핑합니다. (돌진 후 연타 공격)
	*/
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

	// 대시 동작 시 true로 바뀌고 종료시 false
	bool bCheckSkillTwoDashOverlap = false;

	// 내려찍을 때 카메라 효과
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> CameraShakeExplosion;

	//==============================
	//			3번 스킬
	//==============================
	// 캐릭터 주변 공격 범위
	float AttackAroundRadius = 400.f;

	// 캐릭터 전방 공격 거리
	float AttackForwardOffset = 300.f;

	// 캐릭터 전방 공격 범위
	float AttackForwardRadius = 300.f;


	//==============================
	//			4번 스킬
	//==============================
	// 적을 공중에 띄움
	void LaunchEnemy(float ZScale);

	// 공격 범위
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties|SkillFour", meta = (AllowPrivateAccess = "true"))
	float SkillFourRange = 300.f;

public:
	//==============================
	//			1번 스킬
	//==============================
	virtual void HandleSkillOne() override;

	// Anim notify를 통해 호출되는 함수
	UFUNCTION(BlueprintCallable)
	void ThrowKnife();

	FORCEINLINE AActor* GetDashTarget() const { return DashTarget; }
	void SetDashTarget(AActor* Target);
		
	// 대쉬 타이머 경과시 호출
	void OnEndDashTimer();

	//==============================
	//			2번 스킬
	//==============================
	virtual void HandleSkillTwo() override;

	// Anim notify를 통해 호출되는 함수
	UFUNCTION(BlueprintCallable)
	void SkillTwoFirstEffect();

	UFUNCTION(BlueprintCallable)
	void SkillTwoEndEffect();

	//==============================
	//			3번 스킬
	//==============================
	virtual void HandleSkillThree() override;

	UFUNCTION(BlueprintCallable)
	void SpawnSkillThreeFirstEffect();
	
	UFUNCTION(BlueprintCallable)
	void SpawnSkillThreeFinalEffect();

	UFUNCTION(BlueprintCallable)
	void AttackAroundCharacter();

	UFUNCTION(BlueprintCallable)
	void AttackForwardCharacter();

	//==============================
	//			4번 스킬
	//==============================
	virtual void HandleSkillFour() override;

	UFUNCTION(BlueprintCallable)
	void SkillFourEffect();

	// 마무리 공격시 호출
	UFUNCTION(BlueprintCallable)
	void SkillFourEndEffect();
};
