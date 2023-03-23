// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/AbilityComponent.h"
#include "Kismet/GameplayStatics.h"
#include "portfolio/portfolioCharacter.h"
#include "Animation/AnimInstanceBase.h"
#include "CharacterTypes.h"

// Sets default values for this component's properties
UAbilityComponent::UAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}


void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();
	PrimaryComponentTick.SetTickFunctionEnable(false);
	PrimaryComponentTick.RegisterTickFunction(GetComponentLevel());
	Character = Cast<AportfolioCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
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
		UE_LOG(LogTemp, Warning, TEXT("Hello world"));
		SkillOne = *SkillDataTable->FindRow<FCharacterSkills>(FName("AssassinSkillOne"), "")->CharacterSkill.Find(ECharacterClass::ECC_Assassin);
	}
}

void UAbilityComponent::HandleSkillOne()
{
}


// Called every frame
void UAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

