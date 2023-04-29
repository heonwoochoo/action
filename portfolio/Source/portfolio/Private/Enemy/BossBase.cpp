// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BossBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DefaultCharacter.h"
#include "AIController.h"
#include "Animation/BossAnimInstance.h"

// Sets default values
ABossBase::ABossBase()
{
	PrimaryActorTick.bCanEverTick = true;
	SetRootComponent(GetCapsuleComponent());

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	LoadStats();
}

void ABossBase::BeginPlay()
{
	Super::BeginPlay();
	
	Tags.Add(FName(TEXT("Enemy")));
	Tags.Add(FName(TEXT("Boss")));

	BossController = Cast<AAIController>(GetController());

	UBossAnimInstance* AnimInstance = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->PlayOpeningAnimation();
	}
}

void ABossBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	LoadStats();
}

float ABossBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return 0.0f;
}

void ABossBase::FindTarget()
{
	const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes = { UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn)};
	const TArray<AActor*> ActorsToIgnore = {this};
	TArray<AActor*> OutActors;
	bool Exist = UKismetSystemLibrary::SphereOverlapActors(this, GetActorLocation(), 1000.f, ObjectTypes, TSubclassOf<AActor>(), ActorsToIgnore, OutActors);

	if (Exist && OutActors.Num() > 0)
	{
		for (auto Actor : OutActors)
		{
			if (Actor->ActorHasTag(FName("Player")))
			{
				CombatTarget = Actor;
			}
		}
	}
}

void ABossBase::ChaseTarget()
{
	if (CombatTarget && BossController)
	{
		FAIMoveRequest AIMoveRequest;
		AIMoveRequest.SetAcceptanceRadius(50.f);
		AIMoveRequest.SetGoalActor(CombatTarget);
		BossController->MoveTo(AIMoveRequest);
	}
}

void ABossBase::LoadStats()
{
	if (BossCode.IsValid() && BossStatsDataTable)
	{
		Stats = *BossStatsDataTable->FindRow<FBossStats>(BossCode, "");
		
		USkeletalMeshComponent* SkeletalMesh = GetMesh();
		if (SkeletalMesh && BossStatsDataTable && BossCode.IsValid())
		{
			SkeletalMesh->SetSkeletalMesh(Stats.SkeletalMesh);
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimClass(Stats.AnimationClass);
		}
	}
}

void ABossBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
