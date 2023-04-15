// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Types/CharacterTypes.h"
#include "ItemTypes.generated.h"

UENUM(BlueprintType)
enum class EItemName : uint8
{
	EIN_None UMETA(DisplayName = "None"),
	EIN_HealthPotion UMETA(DisplayName = "HealthPotion"),
	EIN_StaminaPotion UMETA(DisplayName = "StaminaPotion"),
};

USTRUCT(BlueprintType)
struct FPotionInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EItemName Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName UIName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Description;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EStatTarget StatTarget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CoolDown;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AbilityPoint;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	uint8 AmountMax;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* Image;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMesh* Mesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UParticleSystem* ConsumeParticle;
};

UENUM(BlueprintType)
enum class EItemNumber : uint8
{
	EIN_1 UMETA(DisplayName = "Item1"),
	EIN_2 UMETA(DisplayName = "Item2"),
	EIN_3 UMETA(DisplayName = "Item3"),
	EIN_4 UMETA(DisplayName = "Item4"),
	EIN_5 UMETA(DisplayName = "Item5"),
	EIN_6 UMETA(DisplayName = "Item6"),
};