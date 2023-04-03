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

	// ������ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	TArray<AActor*> RespawnPoints;

	// �������� ������ ������ Ŭ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	TArray<TSubclassOf<AEnemyBase>> Enemies;

	// ���� �ִ� ��ü ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	int32 EnemyMaxNumber = 10;

	FTimerHandle EnemyRespawnTimerHandle;

	int32 CheckEnemyNumber();

	void RespawnEnemy();

	bool bRespawnFlag = true;
};



