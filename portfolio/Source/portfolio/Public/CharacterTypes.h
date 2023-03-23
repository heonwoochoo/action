// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterTypes.generated.h"

class UAnimMontage;
class UBlendSpace;
class UTexture2D;

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

UENUM(BlueprintType)
enum class ECharacterLevel : uint8
{
	ECL_Level1 UMETA(DisplayName = "Level1"),
	ECL_Level2 UMETA(DisplayName = "Level2"),
	ECL_Level3 UMETA(DisplayName = "Level3"),
	ECL_Level4 UMETA(DisplayName = "Level4"),
	ECL_Level5 UMETA(DisplayName = "Level5"),
	ECL_Level6 UMETA(DisplayName = "Level6"),
	ECL_Level7 UMETA(DisplayName = "Level7"),
	ECL_Level8 UMETA(DisplayName = "Level8"),
	ECL_Level9 UMETA(DisplayName = "Level9"),
	ECL_Level10 UMETA(DisplayName = "Level10")
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
struct FCharacterStats : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AttackDamage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AttackDamageDefense;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AttackSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Critical;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AbilityPoint;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AbilityPointDefense;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CoolDown;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MovementSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float HPMax;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float StaminaMax;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ExpMax;
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
	ECAS_SkillCasting UMETA(DisplayName = "ECAS_SkillCasting"),
};

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	EST_Attack UMETA(DisplayName = "Attack"),
	EST_Buff UMETA(DisplayName = "Buff"),
};

UENUM(BlueprintType)
enum class ESkillNumber : uint8
{
	ESN_One UMETA(DisplayName = "One"),
	ESN_Two UMETA(DisplayName = "Two"),
	ESN_Three UMETA(DisplayName = "Three"),
	ESN_Four UMETA(DisplayName = "Four")
};

USTRUCT(BlueprintType)
struct FCharacterSkill : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ESkillNumber Number;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Description;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CoolDown;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Damage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Stamina;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ESkillType Type;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* Image;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* Animation;
};

USTRUCT(BlueprintType)
struct FCharacterSkillMap
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<ESkillNumber, FCharacterSkill> CharacterSkill;
};

USTRUCT(BlueprintType)
struct FSkillReference
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<ESkillNumber, AActor*> Skills;
};

USTRUCT(BlueprintType)
struct FCharacterSkills : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<ECharacterClass, FCharacterSkill> CharacterSkill;
};

USTRUCT(BlueprintType)
struct FCharacterDefaultAnimations : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FCharacterDefaultAnimation DefaultAnimations;
};