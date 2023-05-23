// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimInstanceBase.h"
#include "DefaultCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Component/AbilityComponent.h"
#include "Types/CharacterTypes.h"
#include "Component/AssassinComponent.h"

void UAnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ADefaultCharacter>(GetOwningActor());

	// 직업 별 애니메이션 기본 값 포인터 설정
	if (Character && DefaultAnimationDataTable)
	{
		ECharacterClass CharacterClass = Character->GetCharacterClass();
		if (CharacterClass == ECharacterClass::ECC_Assassin)
		{
			DefaultAnimations = *DefaultAnimationDataTable->FindRow<FCharacterDefaultAnimation>(FName("Assassin"), "");
		}

		UAssassinComponent* AssassinComponent = Cast<UAssassinComponent>(Character->GetAbilityComponent());
		if (AssassinComponent)
		{
			OnMontageEnded.AddDynamic(AssassinComponent, &UAssassinComponent::OnEndMontage);
		}
	}

	OnMontageEnded.AddDynamic(this, &UAnimInstanceBase::OnEndMontage);
}

void UAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Character)
	{
		if (UCharacterMovementComponent* CharacterMovementComponent = Character->GetCharacterMovement())
		{

			Velocity = CharacterMovementComponent->Velocity;
			ForwardSpeed = UKismetMathLibrary::Quat_UnrotateVector(Character->GetActorQuat(), Velocity).X;
			SideSpeed = UKismetMathLibrary::Quat_UnrotateVector(Character->GetActorQuat(), Velocity).Y;
		}

		ActionState = Character->GetActionState();
		EquipState = Character->GetEquipState();
	}
}

void UAnimInstanceBase::OnEndMontage(UAnimMontage* AnimMontage, bool bInterrupted)
{
	UAnimMontage* HitReact = DefaultAnimations.HitReact;
	if (AnimMontage == HitReact)
	{
		if (Character)
		{
			const ECharacterActionState CurrentState = Character->GetActionState();
			if (CurrentState != ECharacterActionState::ECAS_Dead)
			{
				Character->SetActionState(ECharacterActionState::ECAS_Unoccupied);
			}
		}
	}
}

FName UAnimInstanceBase::GetChangedWeaponItemCode() const
{
	return ChangedWeaponItemCode;
}

float UAnimInstanceBase::GetForwardSpeed() const
{
	return ForwardSpeed;
}

float UAnimInstanceBase::GetSideSpeed() const
{
	return SideSpeed;
}

FVector UAnimInstanceBase::GetVelocity() const
{
	return Velocity;
}

ADefaultCharacter* UAnimInstanceBase::GetCharacter() const
{
	return Character;
}

ECharacterActionState UAnimInstanceBase::GetCharacterActionState() const
{
	return ActionState;
}

ECharacterEquipState UAnimInstanceBase::GetCharacterEquipState() const
{
	return EquipState;
}

ECharacterClass UAnimInstanceBase::GetCharacterClass() const
{
	if (Character)
	{
		UAbilityComponent* CharacterAbilityComponent = Character->GetAbilityComponent();
		if (CharacterAbilityComponent)
		{
			return Character->GetCharacterClass();
		}
	}

	return ECharacterClass::ECC_None;
}

UAnimMontage* UAnimInstanceBase::GetDefaultAttackMontage() const
{
	return DefaultAnimations.DefaultAttack;

}

UAnimMontage* UAnimInstanceBase::GetDefaultDoubleJumpMontage() const
{
	return DefaultAnimations.DefaultDoubleJump;
}

UAnimMontage* UAnimInstanceBase::GetDefaultEvadeMontage() const
{
	return DefaultAnimations.Evade;
}

UAnimMontage* UAnimInstanceBase::GetDefaultHitReactMontage() const
{
	return DefaultAnimations.HitReact;
}

FCharacterDefaultAnimation UAnimInstanceBase::GetDefaultAnimations() const
{
	return DefaultAnimations;
}

void UAnimInstanceBase::PlayHitReact()
{
	UAnimMontage* HitReact = DefaultAnimations.HitReact;
	if (HitReact)
	{
		Montage_Play(HitReact);
		FName SectionName;
		const int32 RandNum = FMath::RandRange(0, 1);
		switch (RandNum)
		{
		case 0:
			SectionName = "HitReact1";
			break;
		case 1:
			SectionName = "HitReact2";
			break;
		}
		Montage_JumpToSection(SectionName);
	}
}

void UAnimInstanceBase::PlayEquipWeapon()
{
	UAnimMontage* EquipWeapon = DefaultAnimations.EquipWeapon;
	Montage_Play(EquipWeapon);
}
