// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "DefaultWorldLevel.generated.h"

class AEnemyBase;

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

	// 적의 최대 개체 수
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy")
	int32 EnemyMaxNumber = 2;

private:
	// 리스폰 지점
	TArray<AActor*> RespawnPoints;

	FTimerHandle EnemyRespawnTimerHandle;

	bool bRespawnFlag = true;

	int32 CheckEnemyNumber();

	void RespawnEnemy();
	
};
