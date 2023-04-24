// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Types/CharacterTypes.h"
#include "ItemTypes.generated.h"

class AItemBase;

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

UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	EET_None UMETA(DisplayName = "None"),
	EET_Weapon UMETA(DisplayName = "Weapon"),
	EET_SubWeapon UMETA(DisplayName = "SubWeapon"),
	EET_Armour UMETA(DisplayName = "Armour"),
	EET_Helmet UMETA(DisplayName = "Helmet"),
	EET_Shoes UMETA(DisplayName = "Shoes"),
	EET_Accessory UMETA(DisplayName = "Accessory"),
	EET_Shield UMETA(DisplayName = "Shield"),
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	EIT_Equipment UMETA(DisplayName = "Equipment"),
	EIT_Consumable UMETA(DisplayName = "Consumable"),
};

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	EIR_Normal UMETA(DisplayName = "Normal"),
	EIR_Rare UMETA(DisplayName = "Rare"),
	EIR_Unique UMETA(DisplayName = "Unique"),
	EIR_Epic UMETA(DisplayName = "Epic"),
};

USTRUCT(BlueprintType)
struct FItemSpec : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EItemType Type;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EEquipmentType EquipmentType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Description;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FCharacterStats Stats;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ECharacterClass Class;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	uint8 AmountMax;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EItemRarity Rarity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* Image;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMesh* StaticMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USkeletalMesh* SkeletalMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UParticleSystem* EffectParticle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AItemBase> ItemClass;
};

UENUM(BlueprintType)
enum class EEquippedState : uint8
{
	EES_Equipped UMETA(DisplayName = "Equipped"),
	EES_Unequipped UMETA(DisplayName = "Unequipped"),
};

USTRUCT(BlueprintType)
struct FEquippedItem
{
	GENERATED_USTRUCT_BODY()

	FEquippedItem(EEquippedState InState = EEquippedState::EES_Unequipped, FName InItemCode = FName())
		: State(InState), ItemCode(InItemCode)
	{
	}
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EEquippedState State;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName ItemCode;
};