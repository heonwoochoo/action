// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterTypes.generated.h"

class UAnimMontage;
class UBlendSpace;
class UBlendSpace1D;
class UTexture2D;
class UParticleSystem;
class UNiagaraSystem;
class USoundCue;

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
	ECC_Assassin UMETA(DisplayName = "Assassin"),

	ECC_None UMETA(DisplayName = "None")
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
	float AbilityPower;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AbilityPowerDefense;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CoolDown;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MovementSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float HPMax;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float HP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float StaminaMax;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Stamina;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ExpMax;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Exp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Gold;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Level;
};

USTRUCT(BlueprintType)
struct FCharacterDefaultAnimation : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* DefaultAttack;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* DefaultDoubleJump;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimSequence* DefaultJump;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBlendSpace1D* EquippedWalkRun;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBlendSpace1D* UnequippedWalkRun;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimSequence* EquippedIdle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimSequence* UnequippedIdle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* Evade;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* HitReact;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimSequence* Dead;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAnimMontage* EquipWeapon;
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
	ECAS_Dead UMETA(DisplayName = "Dead"),
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
	ESN_Four UMETA(DisplayName = "Four"),
	ESN_None UMETA(DisplayName = "None")
};
ENUM_RANGE_BY_FIRST_AND_LAST(ESkillNumber, ESkillNumber::ESN_One, ESkillNumber::ESN_Four);


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

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UParticleSystem*> ParticleEffects;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UNiagaraSystem*> NiagaraEffects;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UParticleSystem*> HitImpacts;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSubclassOf<AActor>> SkillActorClasses;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<USoundCue*> SkillSounds;
};

USTRUCT(BlueprintType)
struct FCharacterDefaultEffect : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UParticleSystem* DefaultHitParticle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UParticleSystem* SlashHitParticle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USoundCue* DefaultHitSound;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USoundCue* SlashHitSound;
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

UENUM(BlueprintType)
enum class EStatUpdateType : uint8
{
	ESUT_Plus UMETA(DisplayName = "Plus"),
	ESUT_Minus UMETA(DisplayName = "Minus"),
};

UENUM(BlueprintType)
enum class EStatTarget : uint8
{
	EST_Health UMETA(DisplayName = "Health"),
	EST_Stamina UMETA(DisplayName = "Stamina"),
	EST_Exp UMETA(DisplayName = "Exp"),
	EST_Gold UMETA(DisplayName = "Gold"),
};

UENUM(BlueprintType)
enum class EHitType : uint8
{
	EHT_Default UMETA(DisplayName = "Default"),
	EHT_Slash UMETA(DisplayName = "Slash"),
};

UENUM(BlueprintType)
enum class EFoot : uint8
{
	EF_Left UMETA(DisplayName = "Left"),
	EF_Right UMETA(DisplayName = "Right"),
};

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	EMT_Walk UMETA(DisplayName = "Walk"),
	EMT_Run UMETA(DisplayName = "Run"),
	EMT_Sprint UMETA(DisplayName = "Sprint"),
	EMT_Roll UMETA(DisplayName = "Roll"),
	EMT_Rush UMETA(DisplayName = "Rush"),
	EMT_Jump UMETA(DisplayName = "Jump"),
	EMT_Land UMETA(DisplayName = "Land"),

	EMT_None UMETA(DisplayName = "None"),
};

USTRUCT(BlueprintType)
struct FMovementEmitter : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UNiagaraSystem* Walk;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UNiagaraSystem* Run;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UNiagaraSystem* Sprint;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UNiagaraSystem* Roll;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UNiagaraSystem* Rush;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UNiagaraSystem* Jump;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UNiagaraSystem* Land;
};

USTRUCT(BlueprintType)
struct FMovementSound : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USoundCue* Walk;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USoundCue* Run;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USoundCue* Sprint;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USoundCue* Roll;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USoundCue* Rush;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USoundCue* Jump;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USoundCue* Land;
};

