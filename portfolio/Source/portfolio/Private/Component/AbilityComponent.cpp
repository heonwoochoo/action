// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/AbilityComponent.h"
#include "Data/CharacterDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "portfolio/portfolioCharacter.h"
#include "Data/CharacterSkillAsset.h"
#include "Animation/AnimInstanceBase.h"
#include "Items/KnifeProjectile.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "Component/CharacterMotionWarpingComponent.h"
#include "Enemy/EnemyBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Skill/Assassin_SkillOne.h"

// Sets default values for this component's properties
UAbilityComponent::UAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	Character = Cast<AportfolioCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	
	if (SkillOneClass)
	{
		SkillOne = GetWorld()->SpawnActor<AAssassin_SkillOne>(SkillOneClass);
	}
}


void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();
	PrimaryComponentTick.SetTickFunctionEnable(false);
	PrimaryComponentTick.RegisterTickFunction(GetComponentLevel());
}

void UAbilityComponent::InitializeComponent()
{
	Super::InitializeComponent();

	Character = Cast<AportfolioCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (Character)
	{
		CharacterData = Character->GetCharacterDataAsset()->CharacterData;
	}

	if (SkillOneClass)
	{
		SkillOne = GetWorld()->SpawnActor<AAssassin_SkillOne>(SkillOneClass);
	}
}

const FCharacterData UAbilityComponent::GetCharacterData()
{
	return CharacterData;
}

void UAbilityComponent::HandleSkillOne()
{
	switch (CharacterData.Class)
	{
	case ECharacterClass::ECC_Assassin:
		SkillOne->PlayAction();
		break;
	}
}

void UAbilityComponent::HandleSkillTwo()
{
}

void UAbilityComponent::HandleSkillThree()
{
}

void UAbilityComponent::HandleSkillFour()
{
}

AAssassin_SkillOne* UAbilityComponent::GetSkillOne() const
{
	return SkillOne;
}


// Called every frame
void UAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

