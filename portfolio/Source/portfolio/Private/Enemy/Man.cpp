﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Man.h"
#include "Types/EnemyTypes.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Animation/AnimInstanceBase.h"
#include "DefaultCharacter.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

AMan::AMan()
{

}

void AMan::BeginPlay()
{
	Super::BeginPlay();
}

void AMan::AttackCharacter()
{
	Super::AttackCharacter();

	const FName SockeName = "FootRightAttack";
	const FVector SocketLocation = GetMesh()->GetSocketLocation(SockeName);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes = { UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn) };
	TArray<AActor*> ActorsToIgnore = { this };
	TArray<AActor*> OutActors;

	UKismetSystemLibrary::SphereOverlapActors(this, SocketLocation, 50.f, ObjectTypes, nullptr, ActorsToIgnore, OutActors);

	for (AActor* Actor : OutActors)
	{
		ADefaultCharacter* Character = Cast<ADefaultCharacter>(Actor);
		if (Character)
		{
			DamageToPlayer(Character);

			// 타격 소리 재생
			if (Stats.EffectSounds.IsValidIndex(0))
			{
				USoundCue* Sound = Stats.EffectSounds[0];
				UGameplayStatics::PlaySoundAtLocation(this, Sound, GetActorLocation());
			}
		}
	}
}
