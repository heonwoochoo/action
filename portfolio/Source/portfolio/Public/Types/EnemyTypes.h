// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EnemyTypes.generated.h"

class UAnimMontage;
class UBlendSpace1D;
class USkeletalMesh;
class UAnimInstance;
class USoundCue;

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	EES_NoState UMETA(DisplayName = "NoState"),
	EES_Dead UMETA(DisplayName = "Dead"),
	EES_Patrolling UMETA(DisplayName = "Patrolling"),
	EES_Chasing UMETA(DisplayName = "Chasing"),
	EES_Attacking UMETA(DisplayName = "Attacking"),
	EES_Engaged UMETA(DisplayName = "Engaged")
};

UENUM(BlueprintType)
enum class EEnemyName : uint8
{
	EEN_None UMETA(DisplayName = "None"),
	EEN_Man UMETA(DisplayName = "Man"),
	EEN_MinionLane UMETA(DisplayName = "MinionLane"),
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

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USkeletalMesh* SkeletalMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UAnimInstance> AnimationClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<USoundCue*> EffectSounds;
};

USTRUCT(BlueprintType)
struct FEnemyDefaultAnimation : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* HitReactOnGround;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* HitReactOnAir;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBlendSpace1D* IdleWalkRun;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* Dead;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* Attack;
};

USTRUCT(BlueprintType)
struct FBossStats : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Name;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Level;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Damage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxHp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Hp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Exp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USkeletalMesh* SkeletalMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UAnimInstance> AnimationClass;
};

USTRUCT(BlueprintType)
struct FBossAnimation : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* HitReact;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBlendSpace1D* IdleWalkRun;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* Dead;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* Attack;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* BackStep;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* SkillOne;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* SkillTwo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* SkillThree;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* Opening;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* Victory;
};

UENUM(BlueprintType)
enum class EBossState : uint8
{
	EBS_NoState UMETA(DisplayName = "NoState"),
	EBS_Dead UMETA(DisplayName = "Dead"),
	EBS_Casting UMETA(DisplayName = "Patrolling"),
	EBS_Chasing UMETA(DisplayName = "Chasing"),
	EBS_Attacking UMETA(DisplayName = "Attacking"),
	EBS_Resting UMETA(DisplayName = "Resting"),
	EBS_SuperArmour UMETA(DisplayName = "SuperArmour"),
	EBS_Evade UMETA(DisplayName = "Evade"),
};