// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterTypes.h"
#include "CharacterSkillAsset.generated.h"

class UAnimMontage;

UCLASS()
class PORTFOLIO_API UCharacterSkillAsset : public UDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TMap<ECharacterClass, FCharacterSkillMap> CharacterSkills;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TMap<ECharacterClass, FSkillReference> CharacterSkillRef;

public:
	UFUNCTION()
	UAnimMontage* GetAnimation(ECharacterClass Class, ESkillNumber SkillNumber);

	UFUNCTION()
	TMap<ECharacterClass, FCharacterSkillMap> GetCharacterSkills() const;
};