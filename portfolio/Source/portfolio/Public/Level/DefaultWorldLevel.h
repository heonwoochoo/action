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

	// �������� ������ ������ Ŭ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy")
	TArray<TSubclassOf<AEnemyBase>> Enemies;

	// ���� �ִ� ��ü ��
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy")
	int32 EnemyMaxNumber = 2;

private:
	// ������ ����
	TArray<AActor*> RespawnPoints;

	FTimerHandle EnemyRespawnTimerHandle;

	bool bRespawnFlag = true;

	int32 CheckEnemyNumber();

	void RespawnEnemy();
	
};
