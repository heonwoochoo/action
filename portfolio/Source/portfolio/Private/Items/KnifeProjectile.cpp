﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/KnifeProjectile.h"
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
		ProjectileMovementComponent->InitialSpeed = 2000.0f;
		ProjectileMovementComponent->MaxSpeed = 1000.0f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.01f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
	}
	
}

// Called when the game starts or when spawned
void AKnifeProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(1.5f);
	if (CollisionComponent)
	{
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AKnifeProjectile::OnBeginOverlapped);
	}
}

// Called every frame
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

void AKnifeProjectile::OnKnifeEffect(AActor* HitActor)
{
	if (Caster)
	{
		UAssassinComponent* AssassinComponent = Cast<UAssassinComponent>(Caster->GetAbilityComponent());
		if (AssassinComponent)
		{
			AssassinComponent->SetDashTarget(HitActor);
		}
		
		float Damage = Caster->GetCharacterStats().AbilityPower + AssassinComponent->GetSkillOne().Damage;

		// Damage event call
		Caster->CheckEnemyInRange(GetActorLocation(), 100.f, Damage, EHitType::EHT_Slash);

		// Destroy instance
		Destroy();
	}
}

void AKnifeProjectile::OnBeginOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 장애물에 맞으면 제거됨
}
