// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterTypes.h"
#include "CharacterSkillAsset.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UCharacterSkillAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<ECharacterClass, FCharacterSkill> CharacterSkillOne;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<ECharacterClass, FCharacterSkill> CharacterSkillTwo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<ECharacterClass, FCharacterSkill> CharacterSkillThree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<ECharacterClass, FCharacterSkill> CharacterSkillFour;
};