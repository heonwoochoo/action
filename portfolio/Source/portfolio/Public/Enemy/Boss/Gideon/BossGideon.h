// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Boss/BossBase.h"
#include "BossGideon.generated.h"

class ADarkStone;
class ADarkWave;
class ADarkSword;

/**
 * < 공격 패턴 >
 * 등장 -> 추격 -> (사거리 도달시) 공격 -> 휴식 -> 추격 -> 공격 ...
 */
UCLASS()
class PORTFOLIO_API ABossGideon : public ABossBase
{
	GENERATED_BODY()
	
public:
	ABossGideon();

protected:
	virtual void BeginPlay() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual void Tick(float DeltaTime) override;

	// 기본 공격시 생성될 오브젝트의 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	TSubclassOf<ADarkStone> DarkStoneClass;

	// 스킬 1 사용시 생성될 오브젝트의 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	TSubclassOf<ADarkWave> DarkWaveClass;

	// 스킬 2 사용시 생성될 오브젝트의 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	TSubclassOf<ADarkSword> DarkSwordClass;

public:
	// 스킬 구현
	virtual void Attack() override;
	virtual void BackStep() override;
	virtual void HandleSkillOne() override;
	virtual void HandleSkillTwo() override;
	virtual void HandleSkillThree() override;

	// 기본 공격 : 다크 스톤을 생성하여 날림
	UFUNCTION(BlueprintCallable)
	void SpawnDarkStone();

	// 스킬 1번 : 바닥에서 분출되는 빔을 3갈래로 생성
	UFUNCTION(BlueprintCallable)
	void SpawnDarkWave();

	// 스킬 2번 : 투검 생성
	UFUNCTION(BlueprintCallable)
	void SpawnDarkSword();
};
