// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/AbilityComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DefaultCharacter.h"
#include "Animation/AnimInstanceBase.h"
#include "Types/CharacterTypes.h"
#include "Sound/SoundCue.h"

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
	OnEndSkillOne.Broadcast();
}

void UAbilityComponent::SetSkillOneTimer()
{
	GetWorld()->GetTimerManager().SetTimer(SkillOneHandle, this, &UAbilityComponent::EndSkillOneTimer, SkillOne.CoolDown, false);
}

void UAbilityComponent::EndSkillTwoTimer()
{
	bCanSkillTwo = true;
	OnEndSkillTwo.Broadcast();
}

void UAbilityComponent::SetSkillTwoTimer()
{
	GetWorld()->GetTimerManager().SetTimer(SkillTwoHandle, this, &UAbilityComponent::EndSkillTwoTimer, SkillTwo.CoolDown, false);
}

void UAbilityComponent::EndSkillThreeTimer()
{
	bCanSkillThree = true;
	OnEndSkillThree.Broadcast();
}

void UAbilityComponent::SetSkillThreeTimer()
{
	GetWorld()->GetTimerManager().SetTimer(SkillThreeHandle, this, &UAbilityComponent::EndSkillThreeTimer, SkillThree.CoolDown, false);
}

void UAbilityComponent::EndSkillFourTimer()
{
	bCanSkillFour = true;
	OnEndSkillFour.Broadcast();
}

void UAbilityComponent::SetSkillFourTimer()
{
	GetWorld()->GetTimerManager().SetTimer(SkillFourHandle, this, &UAbilityComponent::EndSkillFourTimer, SkillFour.CoolDown, false);
}

void UAbilityComponent::HandleSkillOne()
{
	
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

void UAbilityComponent::SpawnParticleEffect(UParticleSystem* Particle)
{
	if (Particle)
	{
		UGameplayStatics::SpawnEmitterAttached(Particle, Character->GetEmitterComponent());
	}
}

void UAbilityComponent::SpawnHitParticle(EHitType HitType, const FVector& Location, const FRotator& Rotation)
{
	if (DefaultEffectDataTable)
	{
		FName RowClassName{ GetRowClassName() };

		FCharacterDefaultEffect* DefaultEffect = DefaultEffectDataTable->FindRow<FCharacterDefaultEffect>(RowClassName, "");

		if (DefaultEffect)
		{
			UParticleSystem* Particle = nullptr;
			switch (HitType)
			{
			case EHitType::EHT_Default:
				Particle = DefaultEffect->DefaultHitParticle;
				break;
			case EHitType::EHT_Slash:
				Particle = DefaultEffect->SlashHitParticle;
				break;
			}

			if (Particle != nullptr)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, Location, Rotation);
			}
		}
	}
}

void UAbilityComponent::PlayHitSound(EHitType HitType, const FVector& Location)
{
	if (DefaultEffectDataTable)
	{
		FName RowClassName{ GetRowClassName() };

		FCharacterDefaultEffect* DefaultEffect = DefaultEffectDataTable->FindRow<FCharacterDefaultEffect>(RowClassName, "");

		if (DefaultEffect)
		{
			USoundCue* SoundCue = nullptr;

			switch (HitType)
			{
			case EHitType::EHT_Default:
				SoundCue = DefaultEffect->DefaultHitSound;
				break;
			case EHitType::EHT_Slash:
				SoundCue = DefaultEffect->SlashHitSound;
				break;
			}

			if (SoundCue)
			{
				UGameplayStatics::PlaySoundAtLocation(this, SoundCue, Location);
			}
		}
	}
}

FName UAbilityComponent::GetRowClassName()
{
	FName RowClassName = "";
	ECharacterClass CharacterClass = Character->GetCharacterClass();
	switch (CharacterClass)
	{
	case ECharacterClass::ECC_Assassin:
		RowClassName = "Assassin";
		break;
	}
	return RowClassName;
}

void UAbilityComponent::NotifyCoolDown(const FTimerHandle& TimerHandle, const FOnProgressSkillCoolDownSignature& Delegate)
{
	const FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	const float& Remaining = TimerManager.GetTimerRemaining(TimerHandle);
	const float& Rate = TimerManager.GetTimerRate(TimerHandle);

	Delegate.Broadcast(Remaining, Rate);
}

// Called every frame
void UAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bCanSkillOne)
	{
		NotifyCoolDown(SkillOneHandle, OnProgressSkillOne);
	}
	if (!bCanSkillTwo)
	{
		NotifyCoolDown(SkillTwoHandle, OnProgressSkillTwo);
	}
	if (!bCanSkillThree)
	{
		NotifyCoolDown(SkillThreeHandle, OnProgressSkillThree);
	}
	if (!bCanSkillFour)
	{
		NotifyCoolDown(SkillFourHandle, OnProgressSkillFour);
	}
}

