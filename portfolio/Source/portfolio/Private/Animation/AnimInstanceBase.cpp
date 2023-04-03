// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimInstanceBase.h"
#include "DefaultCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Component/AbilityComponent.h"
#include "CharacterTypes.h"

void UAnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ADefaultCharacter>(GetOwningActor());

	// ���� �� �ִϸ��̼� �⺻ �� ������ ����
	if (Character && DefaultAnimationDataTable)
	{
		ECharacterClass CharacterClass = Character->GetCharacterClass();
		if (CharacterClass == ECharacterClass::ECC_Assassin)
		{
			DefaultAttackMontage = DefaultAnimationDataTable->FindRow<FCharacterDefaultAnimation>(FName("Assassin"), "")->DefaultAttack;
			DefaultJump = DefaultAnimationDataTable->FindRow<FCharacterDefaultAnimation>(FName("Assassin"), "")->DefaultJump;
			DefaultDoubleJumpMontage = DefaultAnimationDataTable->FindRow<FCharacterDefaultAnimation>(FName("Assassin"), "")->DefaultDoubleJump;
			DefaultWalkRunBlendSpace = DefaultAnimationDataTable->FindRow<FCharacterDefaultAnimation>(FName("Assassin"), "")->WalkRunBlendSpace;
			DefaultEquippedIdle = DefaultAnimationDataTable->FindRow<FCharacterDefaultAnimation>(FName("Assassin"), "")->EquippedIdle;
			DefaultUnequippedIdle = DefaultAnimationDataTable->FindRow<FCharacterDefaultAnimation>(FName("Assassin"), "")->UnequippedIdle;
			DefaultEvadeMontage = DefaultAnimationDataTable->FindRow<FCharacterDefaultAnimation>(FName("Assassin"), "")->Evade;
			DefaultHitReactMontage = DefaultAnimationDataTable->FindRow< FCharacterDefaultAnimation>(FName("Assassin"), "")->HitReact;
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

ADefaultCharacter* UAnimInstanceBase::GetCharacter() const
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
			return Character->GetCharacterClass();
		}
	}

	return ECharacterClass::ECC_None;
}

UAnimMontage* UAnimInstanceBase::GetDefaultAttackMontage() const
{
	return DefaultAttackMontage;
}

UAnimMontage* UAnimInstanceBase::GetDefaultDoubleJumpMontage() const
{
	return DefaultDoubleJumpMontage;
}

UAnimMontage* UAnimInstanceBase::GetDefaultEvadeMontage() const
{
	return DefaultEvadeMontage;
}

UAnimMontage* UAnimInstanceBase::GetDefaultHitReactMontage() const
{
	return DefaultHitReactMontage;
}

void UAnimInstanceBase::PlayHitReact()
{
	if (DefaultHitReactMontage)
	{
		Montage_Play(DefaultHitReactMontage);
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
