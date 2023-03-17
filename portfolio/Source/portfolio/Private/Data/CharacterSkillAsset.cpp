// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/CharacterSkillAsset.h"

UAnimMontage* UCharacterSkillAsset::GetAnimation(ECharacterClass Class, ESkillNumber SkillNumber)
{
    return CharacterSkills.Find(Class)->CharacterSkill.Find(SkillNumber)->Animation;
}
