// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BossBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABossBase::ABossBase()
{
	PrimaryActorTick.bCanEverTick = true;
	SetRootComponent(GetCapsuleComponent());

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	LoadStats();
}

void ABossBase::BeginPlay()
{
	Super::BeginPlay();
	
	Tags.Add(FName(TEXT("Enemy")));
	Tags.Add(FName(TEXT("Boss")));
}

void ABossBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	LoadStats();

	USkeletalMeshComponent* Mesh = GetMesh();
	if (Mesh && BossStatsDataTable && BossCode.IsValid())
	{
		Mesh->SetSkeletalMesh(Stats.SkeletalMesh);
	}
}

float ABossBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return 0.0f;
}

void ABossBase::LoadStats()
{
	if (BossCode.IsValid() && BossStatsDataTable)
	{
		Stats = *BossStatsDataTable->FindRow<FBossStats>(BossCode, "");
	}
}

void ABossBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
