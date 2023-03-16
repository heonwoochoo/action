// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterTypes.h"
#include "CharacterSkillDataTable.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UCharacterSkillDataTable : public UDataTable
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<ECharacterClass, FCharacterSkill> CharacterSkillData;
};
