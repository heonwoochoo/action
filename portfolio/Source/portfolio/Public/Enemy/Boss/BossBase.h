﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Types/EnemyTypes.h"
#include "BossBase.generated.h"

class AAIController;


UCLASS()
class PORTFOLIO_API ABossBase : public ACharacter
{
	GENERATED_BODY()

public:
	ABossBase();

protected:
	virtual void BeginPlay() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// AI 설정을 위한 컨트롤러
	UPROPERTY()
	AAIController* BossController;

	// 기본 스탯이 저장된 데이터 테이블
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	UDataTable* BossStatsDataTable;
	
	// 고유 넘버
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	FName BossCode;

	// 데이터 테이블에서 보스코드를 참조하여 데이터가 복사되어 저장됨
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	FBossStats Stats;

	// 움직임 상태
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	EBossState State = EBossState::EES_NoState;

	// 목표 타겟 (전투하는 플레이어)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	AActor* CombatTarget;

	// 해당 거리 이내로 타겟이 들어오면 이동을 멈춤
	float AcceptanceRadius = 1000.f;
	


public:
	FORCEINLINE const FName& GetCode() const { return BossCode; }
	FORCEINLINE const FBossStats& GetStats() const { return Stats; }

	FORCEINLINE const EBossState& GetState() const { return State; }
	FORCEINLINE void SetState(const EBossState& NewState) { State = NewState; }


	// 범위 내 플레이어를 찾아 타겟으로 저장
	void FindTarget();

	// 범위 내 타겟이 있는지 체크
	bool IsTargetInRange(const float& Radius, AActor* Target);

	// 몸체의 Z축을 타겟 방향으로 천천히 회전시킴
	void RotateBodyToCombatTarget(float DeltaTime);

	// 타겟을 향해 이동
	void ChaseTarget();

	// 스킬 구현
	virtual void Attack();
	virtual void HandleSkillOne();
	virtual void HandleSkillTwo();
	virtual void HandleSkillThree();

	

private:
	// 데이터 테이블로부터 스탯 데이터를 불러와 저장
	void LoadStats();
};