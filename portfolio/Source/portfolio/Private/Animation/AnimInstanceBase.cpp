// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimInstanceBase.h"
#include "portfolio/portfolioCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Component/AbilityComponent.h"
#include "CharacterTypes.h"

void UAnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<AportfolioCharacter>(GetOwningActor());

	// 게임 시작시 직업에 따른 애니메이션 기본 값 포인터 설정
	if (Character)
	{
		if (UAbilityComponent* AbilityComponent = Character->GetAbilityComponent())
		{
			ECharacterClass CharacterClass = AbilityComponent->GetCharacterData().Class;
			if (UCharacterDataAsset* CharacterDataAsset = Character->GetCharacterDataAsset())
			{
				DefaultAttackMontage = CharacterDataAsset->DefaultAnimations.Find(CharacterClass)->DefaultAttack;
				DefaultWalkRunBlendSpace = CharacterDataAsset->DefaultAnimations.Find(CharacterClass)->WalkRunBlendSpace;
				DefaultEquippedIdle = CharacterDataAsset->DefaultAnimations.Find(CharacterClass)->EquippedIdle;
				DefaultUnequippedIdle = CharacterDataAsset->DefaultAnimations.Find(CharacterClass)->UnequippedIdle;
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
