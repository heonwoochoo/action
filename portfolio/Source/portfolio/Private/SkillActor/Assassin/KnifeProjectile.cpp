// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillActor/Assassin/KnifeProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DefaultCharacter.h"
#include "Component/AbilityComponent.h"
#include "Component/AssassinComponent.h"


// Sets default values
AKnifeProjectile::AKnifeProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	if (CollisionComponent)
	{
		RootComponent = CollisionComponent;
		CollisionComponent->SetGenerateOverlapEvents(true);
	}
	
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	if (SkeletalMesh)
	{
		SkeletalMesh->SetupAttachment(GetRootComponent());
	}

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	if (ProjectileMovementComponent)
	{
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 3000.0f;
		ProjectileMovementComponent->MaxSpeed = 3000.0f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
	}	
}

void AKnifeProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(1.5f);
	if (CollisionComponent)
	{
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AKnifeProjectile::OnBeginOverlapped);
	}
}

void AKnifeProjectile::Destroyed()
{
	// 히트되지 않았다면 쿨타임 적용
	if (Caster)
	{
		UAbilityComponent* AbilityComponent = Caster->GetAbilityComponent();
		if (AbilityComponent)
		{
			UAssassinComponent* AssassinComponent = Cast<UAssassinComponent>(AbilityComponent);
			if (AssassinComponent)
			{
				AActor* Target = AssassinComponent->GetDashTarget();
				if (Target == nullptr)
				{
					AssassinComponent->SetCanSkillOne(false);
					AssassinComponent->SetSkillOneTimer();
				}
			}
		}
	}
}

void AKnifeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKnifeProjectile::SetMovementDirection(const FVector& Direction)
{
	if (ProjectileMovementComponent)
	{
		ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;
	}
}

void AKnifeProjectile::OnBeginOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName(TEXT("Enemy"))))
	{
		// 대쉬 타겟으로 설정
		UAssassinComponent* AssassinComponent = Cast<UAssassinComponent>(Caster->GetAbilityComponent());
		if (AssassinComponent)
		{
			AssassinComponent->SetDashTarget(OtherActor);
		}

		Caster->CheckEnemyInRange(GetActorLocation(), 50.f, Damage, EHitType::EHT_Slash);

		Destroy();
	}	
}
