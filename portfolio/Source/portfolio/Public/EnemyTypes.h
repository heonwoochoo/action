// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyTypes.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	EES_Unoccupied UMETA(DisplayName = "Unoccupied"),
	EES_Targeted UMETA(DisplayName = "Targeted")
};

UENUM(BlueprintType)
enum class EEnemyName : uint8
{
	EEN_Man UMETA(DisplayName = "Man"),
};

USTRUCT(BlueprintType)
struct FEnemyData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Damage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxHp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Hp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RespawnTime;
};