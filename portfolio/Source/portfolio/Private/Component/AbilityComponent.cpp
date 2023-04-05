// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/AbilityComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DefaultCharacter.h"
#include "Animation/AnimInstanceBase.h"
#include "CharacterTypes.h"

// Sets default values for this component's properties
UAbilityComponent::UAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
}


void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();
	PrimaryComponentTick.SetTickFunctionEnable(true);
	PrimaryComponentTick.RegisterTickFunction(GetComponentLevel());
	Character = Cast<ADefaultCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (Character)
	{
		AnimInstance = Cast<UAnimInstanceBase>(Character->GetMesh()->GetAnimInstance());
	}
}

void UAbilityComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (SkillDataTable)
	{
		SkillOne = *SkillDataTable->FindRow<FCharacterSkills>(FName("AssassinSkillOne"), "")->CharacterSkill.Find(ECharacterClass::ECC_Assassin);
		SkillTwo = *SkillDataTable->FindRow<FCharacterSkills>(FName("AssassinSkillTwo"), "")->CharacterSkill.Find(ECharacterClass::ECC_Assassin);
		SkillThree = *SkillDataTable->FindRow<FCharacterSkills>(FName("AssassinSkillThree"), "")->CharacterSkill.Find(ECharacterClass::ECC_Assassin);
		SkillFour = *SkillDataTable->FindRow<FCharacterSkills>(FName("AssassinSkillFour"), "")->CharacterSkill.Find(ECharacterClass::ECC_Assassin);
	}
}



void UAbilityComponent::EndSkillOneTimer()
{
	bCanSkillOne = true;
}

void UAbilityComponent::SetSkillOneTimer()
{
	GetWorld()->GetTimerManager().SetTimer(SkillOneHandle, this, &UAbilityComponent::EndSkillOneTimer, SkillOne.CoolDown, false);
}

void UAbilityComponent::EndSkillTwoTimer()
{
	bCanSkillTwo = true;
}

void UAbilityComponent::SetSkillTwoTimer()
{
	GetWorld()->GetTimerManager().SetTimer(SkillTwoHandle, this, &UAbilityComponent::EndSkillTwoTimer, SkillTwo.CoolDown, false);
}

void UAbilityComponent::EndSkillThreeTimer()
{
	bCanSkillThree = true;
}

void UAbilityComponent::SetSkillThreeTimer()
{
	GetWorld()->GetTimerManager().SetTimer(SkillThreeHandle, this, &UAbilityComponent::EndSkillThreeTimer, SkillThree.CoolDown, false);
}

void UAbilityComponent::EndSkillFourTimer()
{
	bCanSkillFour = true;
}

void UAbilityComponent::SetSkillFourTimer()
{
	GetWorld()->GetTimerManager().SetTimer(SkillFourHandle, this, &UAbilityComponent::EndSkillFourTimer, SkillFour.CoolDown, false);
}

void UAbilityComponent::HandleSkillOne()
{

		SetSkillOneTimer();
	
}

void UAbilityComponent::HandleSkillTwo()
{

		SetSkillTwoTimer();
	
}

void UAbilityComponent::HandleSkillThree()
{

		SetSkillThreeTimer();
	
}

void UAbilityComponent::HandleSkillFour()
{

		SetSkillFourTimer();
	
}


// Called every frame
void UAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

