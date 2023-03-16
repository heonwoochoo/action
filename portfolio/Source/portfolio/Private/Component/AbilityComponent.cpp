// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/AbilityComponent.h"
#include "Data/CharacterDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "portfolio/portfolioCharacter.h"
#include "Data/CharacterSkillAsset.h"
#include "Animation/AnimInstanceBase.h"
#include "Items/KnifeProjectile.h"

// Sets default values for this component's properties
UAbilityComponent::UAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	Character = Cast<AportfolioCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (Character)
	{
		CharacterData = Character->GetCharacterDataAsset()->CharacterData;
	}
}


// Called when the game starts
void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	PrimaryComponentTick.SetTickFunctionEnable(false);
	PrimaryComponentTick.RegisterTickFunction(GetComponentLevel());


}

void UAbilityComponent::InitializeComponent()
{
	Super::InitializeComponent();

	// 데이터 에셋을 참조하여 스킬 애니메이션 포인터 초기화
	if (CharacterSkillAsset)
	{
		SkillOneAnimation = CharacterSkillAsset->CharacterSkillOne.Find(CharacterData.Class)->Animation;
	}
	
	if (Character && Character->GetMesh())
	{
		AnimInstance = Cast<UAnimInstanceBase>(Character->GetMesh()->GetAnimInstance());
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
		HandleAssassinSkillOne();
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

void UAbilityComponent::HandleAssassinSkillOne()
{
	UE_LOG(LogTemp, Warning, TEXT("Assassin skill1 called"));
	if (AnimInstance)
	{
		AnimInstance->Montage_Play(SkillOneAnimation);
		FName SectionName = "Assassin_Skill1_First";
		AnimInstance->Montage_JumpToSection(SectionName);
		if (KinfeProjectileClass)
		{
			const FTransform Transform = Character->GetActorTransform();
			GetWorld()->SpawnActor<AKnifeProjectile>(KinfeProjectileClass, Transform);
		}
	}
}

void UAbilityComponent::HandleAssassinSkillTwo()
{
}

void UAbilityComponent::HandleAssassinSkillThree()
{
}

void UAbilityComponent::HandleAssassinSkillFour()
{
}



// Called every frame
void UAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UE_LOG(LogTemp, Warning, TEXT("Tick Ability Comp"));
}

