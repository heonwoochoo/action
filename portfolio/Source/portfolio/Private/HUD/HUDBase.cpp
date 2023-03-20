// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/HUDBase.h"
#include "GameFramework/Character.h"
#include "HUD/DamageText.h"
#include "HUD/TargetMark.h"
#include "Components/CapsuleComponent.h"

AHUDBase::AHUDBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHUDBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AHUDBase::ShowDamageOnScreen(ACharacter* Actor, float Damage)
{
	if (DamageTextClass)
	{
		const FVector Location = Actor->GetActorLocation() + Actor->GetActorUpVector() * Actor->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		const FRotator Rotation = Actor->GetActorRotation();
		FActorSpawnParameters SpawnInfo;
		ADamageText* DamageText = GetWorld()->SpawnActor<ADamageText>(DamageTextClass, Location, Rotation, SpawnInfo);
		DamageText->Initialize(Damage);
	}
}

void AHUDBase::ShowTargetMark(ACharacter* Enemy, ACharacter* Caster)
{
	if (TargetMarkClass)
	{
		const FVector Location = Enemy->GetActorLocation() + Enemy->GetActorUpVector() * Enemy->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		const FRotator Rotation = Enemy->GetActorRotation();
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = Enemy;
		SpawnInfo.Instigator = Caster;
		ATargetMark* TargetMark = GetWorld()->SpawnActor<ATargetMark>(TargetMarkClass, Location, Rotation, SpawnInfo);
	}
}
