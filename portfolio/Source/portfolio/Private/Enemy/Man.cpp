// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Man.h"
#include "Types/EnemyTypes.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Animation/AnimInstanceBase.h"
#include "DefaultCharacter.h"

AMan::AMan()
{

}

void AMan::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (EnemyStatsDataTable)
	{
		if (Name == EEnemyName::EEN_Man)
		{
			Stats = *EnemyStatsDataTable->FindRow<FEnemyStats>(FName("Man"), "");
		}

		GetMesh()->SetAnimClass(Stats.AnimationClass);
		GetMesh()->SetSkeletalMeshAsset(Stats.SkeletalMesh);
	}
}

void AMan::BeginPlay()
{
	Super::BeginPlay();

	if (EnemyStatsDataTable)
	{
		if (Name == EEnemyName::EEN_Man)
		{
			Stats = *EnemyStatsDataTable->FindRow<FEnemyStats>(FName("Man"), "");
		}
	}
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
	DrawDebugSphere(GetWorld(), SocketLocation, 50.f, 16, FColor::Red, false, 1.f);

	for (AActor* Actor : OutActors)
	{
		ADefaultCharacter* Character = Cast<ADefaultCharacter>(Actor);
		if (Character)
		{
			DamageToPlayer(Character);
		}
	}
}
