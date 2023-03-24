// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EnemyTypes.generated.h"

class UAnimMontage;
class UBlendSpace1D;

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	EES_Unoccupied UMETA(DisplayName = "Unoccupied"),
	EES_Dead UMETA(DisplayName = "Dead"),
	EES_Patrolling UMETA(DisplayName = "Patrolling"),
	EES_Chasing UMETA(DisplayName = "Chasing"),
	EES_Attacking UMETA(DisplayName = "Attacking"),
	EES_Engaged UMETA(DisplayName = "Engaged")
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

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Exp;
};

USTRUCT(BlueprintType)
struct FEnemyAnimData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* HitReactOnGround;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBlendSpace1D* IdleWalkRun;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* Dead;
};

USTRUCT(BlueprintType)
struct FEnemyStats : public FTableRowBase
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

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Exp;
};

USTRUCT(BlueprintType)
struct FEnemyDefaultAnimation : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* HitReactOnGround;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBlendSpace1D* IdleWalkRun;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* Dead;
};