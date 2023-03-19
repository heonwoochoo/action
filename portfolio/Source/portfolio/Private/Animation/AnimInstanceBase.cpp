// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimInstanceBase.h"
#include "portfolio/portfolioCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Component/AbilityComponent.h"
#include "Data/CharacterSkillAsset.h"
#include "CharacterTypes.h"

void UAnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<AportfolioCharacter>(GetOwningActor());

	// 직업 별 애니메이션 기본 값 포인터 설정
	// 타입 추가 후 데이터 에셋 파일에도 참조 애니메이션 반드시 설정해줄 것 !
	if (Character)
	{
		UAbilityComponent* AbilityComponent = Character->GetAbilityComponent();
		if (AbilityComponent && AbilityComponent->GetCharacterSkillAsset())
		{
			ECharacterClass CharacterClass = AbilityComponent->GetCharacterData().Class;
			if (UCharacterDataAsset* CharacterDataAsset = Character->GetCharacterDataAsset())
			{
				DefaultAttackMontage = CharacterDataAsset->DefaultAnimations.Find(CharacterClass)->DefaultAttack;
				DefaultJump = CharacterDataAsset->DefaultAnimations.Find(CharacterClass)->DefaultJump;
				DefaultDoubleJumpMontage = CharacterDataAsset->DefaultAnimations.Find(CharacterClass)->DefaultDoubleJump;
				DefaultWalkRunBlendSpace = CharacterDataAsset->DefaultAnimations.Find(CharacterClass)->WalkRunBlendSpace;
				DefaultEquippedIdle = CharacterDataAsset->DefaultAnimations.Find(CharacterClass)->EquippedIdle;
				DefaultUnequippedIdle = CharacterDataAsset->DefaultAnimations.Find(CharacterClass)->UnequippedIdle;
				DefaultEvadeMontage = CharacterDataAsset->DefaultAnimations.Find(CharacterClass)->Evade;
				SkillOne = AbilityComponent->GetCharacterSkillAsset()->GetAnimation(CharacterClass, ESkillNumber::ESN_One);
			}
		}
	}
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


			// Debuging
			GEngine->AddOnScreenDebugMessage(1, -1, FColor::Red, FString::Printf(TEXT("Velocity : %f"), Velocity.Size()));
			GEngine->AddOnScreenDebugMessage(2, -1, FColor::Cyan, FString::Printf(TEXT("ForwardSpeed : %f"), ForwardSpeed));
			GEngine->AddOnScreenDebugMessage(3, -1, FColor::Blue, FString::Printf(TEXT("SideSpeed : %f"), SideSpeed));
		}
	}
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

AportfolioCharacter* UAnimInstanceBase::GetCharacter() const
{
	return Character;
}

ECharacterClass UAnimInstanceBase::GetCharacterClass() const
{
	if (Character)
	{
		UAbilityComponent* CharacterAbilityComponent = Character->GetAbilityComponent();
		if (CharacterAbilityComponent)
		{
			return CharacterAbilityComponent->GetCharacterData().Class;
		}
	}

	return ECharacterClass::ECC_None;
}

ECharacterEquipState UAnimInstanceBase::GetCharacterEquipState() const
{
	if (Character)
	{
		UAbilityComponent* CharacterAbilityComponent = Character->GetAbilityComponent();
		if (CharacterAbilityComponent)
		{
			return CharacterAbilityComponent->GetCharacterData().EquipState;
		}
	}

	return ECharacterEquipState::ECES_Unquipped;
}

UAnimMontage* UAnimInstanceBase::GetDefaultAttackMontage() const
{
	return DefaultAttackMontage;
}

UAnimMontage* UAnimInstanceBase::GetDefaultDoubleJumpMontage() const
{
	return DefaultDoubleJumpMontage;
}

UAnimMontage* UAnimInstanceBase::GetDefaultDefaultEvadeMontage() const
{
	return DefaultEvadeMontage;
}

UAnimMontage* UAnimInstanceBase::GetSkillOne() const
{
	return SkillOne;
}
