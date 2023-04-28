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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties|SkillOne", meta = (AllowPrivateAccess = "true"))
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

	// 대시 동작 시 true로 바뀌고 종료시 false
	bool bCheckSkillTwoDashOverlap = false;

	// 내려찍을 때 카메라 효과
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> CameraShakeExplosion;


	//==============================
	//			3번 스킬
	//==============================
	// 파티클이 부착될 컴포넌트의 로테이션을 조절하기 위한 값을 담은 배열
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties|SkillThree", meta = (AllowPrivateAccess = "true"))
	TArray<float> SkillThreeEffectRotationValues;

	// 게임 시작 시 호출
	void InitSkillThreeEffectRotationValues();

	// 콤보 카운트
	uint8 SkillThreeCombo = 0;

	// 콤보 카운트에 따른 컴포넌트 로테이션 조정
	void AdjustCompRotationByCombo(uint8 ComboCount);

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

	void SetDashTarget(AActor* Target);
		
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

	// Anim notify를 통해 호출되는 함수
	UFUNCTION(BlueprintCallable)
	void SpawnSkillThreeEffect();

	// 콤보 초기화, 스킬 첫 동작시 호출
	UFUNCTION(BlueprintCallable)
	void InitSkillThreeComboCount();

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
