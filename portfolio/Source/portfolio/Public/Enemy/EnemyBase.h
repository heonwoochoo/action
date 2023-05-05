// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Types/EnemyTypes.h"
#include "EnemyBase.generated.h"

class UEnemyDataAsset;
class UEnemyHPBarWidgetComponent;
class UMotionWarpingComponent;
class ADamageText;
class UPawnSensingComponent;
class AAIController;
class ADefaultCharacter;
class UMaterialInstance;
class UDamagedComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChangedEnemyHealthSignature, const float&, CurrentHp, const float&, MaxHp);

UCLASS()
class PORTFOLIO_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();
	virtual void Tick(float DeltaTime) override;

	FOnChangedEnemyHealthSignature OnChangedHp;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	UDataTable* EnemyStatsDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Properties")
	FEnemyStats Stats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EEnemyState State = EEnemyState::EES_NoState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EEnemyName Name;

	// =================
	// Pawnsensing, AI
	// =================
	
	// 일정 범위 내로 들어온 타겟의 위치를 감지하기 위한 컴포넌트
	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;

	// 데미지를 입으면 캐릭터에 변화를 주는 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDamagedComponent* DamagedComponent;

	// AI 설정을 위한 컨트롤러
	UPROPERTY()
	AAIController* EnemyController;

	// 현재 선택된 Patrol Target (시작시 이쪽으로 우선 움직임)
	UPROPERTY(EditInstanceOnly, Category = "AI Navigation");
	AActor* PatrolTarget;

	// 랜덤으로 정해지는 Patrol Target을 담는 배열
	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	TArray<AActor*> PatrolTargets;

	// 목표 타겟 (플레이어의 캐릭터)
	UPROPERTY(BlueprintReadOnly, Category = Combat)
	AActor* CombatTarget;

	// 목표물을 향할 때 속도
	UPROPERTY(EditAnywhere, Category = Combat)
	float ChasingWalkSpeed = 300.f;

	// 패트롤 시 속도
	UPROPERTY(EditAnywhere, Category = Combat)
	float PatrolWalkSpeed = 150.f;

	// 패트롤 타겟을 재설정하기 위한 범위
	UPROPERTY(EditAnywhere)
	double PatrolRadius = 200.f;

	// 센서가 타겟 감지시 해당 함수를 호출
	UFUNCTION()
	void PawnSeen(APawn* SeenPawn);

	void ChaseTarget();

	bool CanAttack();

	// 패트롤 타겟의 포인터를 저장 후 최초 타겟 설정
	void InitPatrolTarget();

	// ==========================
	// Patrol Timer
	// ==========================
	FTimerHandle PatrolTimer;

	void PatrolTimerFinished();

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMin = 5.f;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMax = 10.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	double AcceptanceRadius = 50.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	double CombatRadius = 1000.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	double AttackRadius = 150.f;

	FTimerHandle AttackTimer;

	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMin = 0.5f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMax = 1.f;

	// 사망시 떨어질 수 있는 아이템 목록
	UPROPERTY(EditAnywhere, Category = Item)
	TArray<TSubclassOf<AActor>> DropItemList;
	
	// 아이템이 떨어질 확률
	UPROPERTY(EditAnywhere, Category = Item)
	float ItemDropRate = 0.3f;

	// 피격시 생기는 외형선이 지속되는 시간
	float HitOutlineDurationTime = 5.f;

	// 공격 애니메이션 재생
	void PlayAttackAnim();

	// 가격 타이밍에 Anim notify에서 호출되는 함수
	UFUNCTION(BlueprintCallable)
	virtual void AttackCharacter();

	// 공격 종료시 Anim notify에서 호출되는 함수
	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	void StartAttackTimer();

	void DamageToPlayer(ADefaultCharacter* Character);

	void MoveToTarget(AActor* Target);

	void CheckCombatTarget();

	void CheckPatrolTarget();

	bool InTargetRange(AActor* Target, double Radius);

	void ClearAttackTimer();

	void LoseInterest();

	void HideHealthBar();

	void ShowHealthBar();

	void StartPatrolling();

	AActor* ChoosePatrolTarget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UEnemyHPBarWidgetComponent* HPBarWidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMotionWarpingComponent* MotionWarpingComponent;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void HandleAttackTarget(AController* EventInstigator);

	void HandleDamage(AActor* DamageCauser, const float& DamageAmount, const bool& IsCritical);

	// Hit react
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float KnockBackDistance = 30.f;

	virtual void Destroyed() override;

	void DropItem();

private:

	void Die();

	FTimerHandle TakeDamageHandle;

	FTimerHandle HitOverlayTimerHandle;

	AActor* DamageCauserActor;

	void PlayHitAnimNextTick();
	void PlayHitAnim();
	void PlayDeadAnim();

public:
	FORCEINLINE FEnemyStats GetEnemyStats() const { return Stats; }
	FORCEINLINE UEnemyHPBarWidgetComponent* GetHPBarWidgetComponent() const { return HPBarWidgetComponent;}

	EEnemyState GetState() const;
	void SetState(EEnemyState NewState);

	FORCEINLINE EEnemyName GetName() const { return Name; }

	UFUNCTION(BlueprintCallable)
	void HitRotationEnd();

};
