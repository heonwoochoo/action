// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DefaultGameMode.generated.h"

class AEnemyBase;

UCLASS(minimalapi)
class ADefaultGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	ADefaultGameMode();

	// 리스폰 지점
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	TArray<AActor*> RespawnPoints;

	// 리스폰될 예정인 액터의 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	TArray<TSubclassOf<AEnemyBase>> Enemies;

	// 적의 최대 개체 수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	int32 EnemyMaxNumber = 10;

	FTimerHandle EnemyRespawnTimerHandle;

	int32 CheckEnemyNumber();

	void RespawnEnemy();

	bool bRespawnFlag = true;
};



