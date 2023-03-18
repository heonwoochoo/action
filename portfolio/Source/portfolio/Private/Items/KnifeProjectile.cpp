// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/KnifeProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "portfolio/portfolioCharacter.h"
#include "Component/AbilityComponent.h"


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
		ProjectileMovementComponent->InitialSpeed = 1000.0f;
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

void AKnifeProjectile::OnBeginOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// enenmy가 수리검에 맞으면 캐스터의 Dash 타겟을 설정합니다.
	if (OtherActor->ActorHasTag(FName("Enemy")))
	{
		if (Caster)
		{
			Caster->GetAbilityComponent()->SetDashTarget(OtherActor);
			
			// 파티클 생성
			
			// 사운드 플레이

			// 인스턴스 제거
			Destroy();
		}
	}
}
