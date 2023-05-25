// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "DefaultWorldLevel.generated.h"

class AEnemyBase;
class USoundCue;
class UAudioComponent;
class ABossBase;

UCLASS()
class PORTFOLIO_API ADefaultWorldLevel : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	ADefaultWorldLevel();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	// 리스폰될 예정인 액터의 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy")
	TArray<TSubclassOf<AEnemyBase>> Enemies;

	// 맵에 존재하는 몹의 최대 개체 수
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy")
	int32 EnemyMaxNumber = 2;

	// 보스의 액터클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy|Boss")
	TSubclassOf<ABossBase> BossClass;

	// 보스가 스폰될 위치
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy|Boss")
	AActor* BossSpawnPoint;

	// 소환된 보스의 포인터
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy|Boss")
	ABossBase* SpawnedBoss;

private:
	// 리스폰 지점
	TArray<AActor*> RespawnPoints;

	FTimerHandle EnemyRespawnTimerHandle;

	bool bRespawnFlag = true;

	bool bIsBossSpawn = false;

	int32 CheckEnemyNumber();

	void RespawnEnemy();

public:
	// 보스 생성
	void SpawnBoss();

	// 잔몹 제거
	void RemoveAllEnemies();
};
