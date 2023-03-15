// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterTypes.generated.h"

class UAnimMontage;
class UBlendSpace;

UENUM(BlueprintType)
enum class ECharacterEquipState : uint8
{
	ECES_Equipped UMETA(DisplayName = "Equipped"),
	ECES_Unquipped UMETA(DisplayName = "Unequipped"),

	ECES_None UMETA(DisplayName = "None")
};

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	ECC_Assassin UMETA(DisplayName = "Assasin"),

	ECC_None UMETA(DisplayName = "None")
};

USTRUCT(BlueprintType)
struct FCharacterData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ECharacterEquipState EquipState;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ECharacterClass Class;
};

USTRUCT(BlueprintType)
struct FCharacterDefaultAnimation
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* DefaultAttack;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* DefaultDoubleJump;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimSequence* DefaultJump;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBlendSpace* WalkRunBlendSpace;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimSequence* EquippedIdle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimSequence* UnequippedIdle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* Evade;
};

UENUM(BlueprintType)
enum class ECharacterDirection : uint8
{
	ECD_Forward UMETA(DisplayName = "Forward"),
	ECD_Back UMETA(DisplayName = "Back"),
	ECD_Left UMETA(DisplayName = "Left"),
	ECD_Right UMETA(DisplayName = "Right")
};

UENUM(BlueprintType)
enum class ECharacterActionState : uint8
{
	ECAS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	ECAS_MoveForward UMETA(DisplayName = "MoveForward"),
	ECAS_MoveBack UMETA(DisplayName = "MoveBack"),
	ECAS_MoveLeft UMETA(DisplayName = "MoveLeft"),
	ECAS_MoveRight UMETA(DisplayName = "MoveRight"),
	ECAS_Jump UMETA(DisplayName = "Jump"),
	ECAS_Evade UMETA(DisplayName = "Evade"),
	ECAS_Sprint UMETA(DisplayName = "Sprint"),
	ECAS_Attack UMETA(DisplayName = "Attack"),
	ECAS_AttackCombo UMETA(DisplayName = "AttackCombo"),
};