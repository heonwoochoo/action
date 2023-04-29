// Fill out your copyright notice in the Description page of Project Settings.

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


public:
	FORCEINLINE const FName& GetCode() const { return BossCode; }
	FORCEINLINE const FBossStats& GetStats() const { return Stats; }

	FORCEINLINE const EBossState& GetState() const { return State; }
	FORCEINLINE void SetState(const EBossState& NewState) { State = NewState; }

	// 플레이어 체크
	// 스킬 구현


private:
	// 데이터 테이블로부터 스탯 데이터를 불러와 저장
	void LoadStats();
};
