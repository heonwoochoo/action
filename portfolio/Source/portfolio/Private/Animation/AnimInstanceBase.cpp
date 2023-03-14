// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimInstanceBase.h"
#include "portfolio/portfolioCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Component/AbilityComponent.h"


void UAnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<AportfolioCharacter>(GetOwningActor());

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
