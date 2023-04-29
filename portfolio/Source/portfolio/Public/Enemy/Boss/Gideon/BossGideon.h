﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Boss/BossBase.h"
#include "BossGideon.generated.h"

class ADarkStone;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	TSubclassOf<ADarkStone> DarkStoneClass;

public:
	// 스킬 구현
	virtual void Attack() override;
	virtual void HandleSkillOne() override;
	virtual void HandleSkillTwo() override;
	virtual void HandleSkillThree() override;

	// 기본 공격 : 다크 스톤을 생성하여 날림
	UFUNCTION(BlueprintCallable)
	void SpawnDarkStone();
};
