// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Boss/Gideon/DarkStone.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DefaultCharacter.h"
#include "Sound/SoundCue.h"
#include "Kismet/KismetMathLibrary.h"

ADarkStone::ADarkStone()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SetRootComponent(SphereCollision);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;

	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComponent"));
	ParticleComponent->SetupAttachment(GetRootComponent());
}


void ADarkStone::BeginPlay()
{
	Super::BeginPlay();
	
	if (SphereCollision)
	{
		SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ADarkStone::OnOverlapped);
	}

	SetLifeSpan(2.f);
}

void ADarkStone::OnOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const bool IsPlayer = OtherActor->ActorHasTag(FName("Player"));
	const FVector& ImpactPoint = SweepResult.ImpactPoint;
	if (IsPlayer)
	{
		// 데미지 적용
		UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, Owner, TSubclassOf<UDamageType>());	
		// 파티클 생성
		if (HitImpactParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitImpactParticle, ImpactPoint);
		}
		// 소리 재생
		if (HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, ImpactPoint);
		}
	}
	else
	{
		// 파티클 생성
		if (HitImpactParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitImpactParticle, ImpactPoint);
		}
	}
	Destroy();
}

void ADarkStone::SetTarget(AActor* InTarget)
{
	Target = InTarget;

	if (Target)
	{
		FVector TargetLocation = Target->GetActorLocation();
		const FVector& ObjectLocation = GetActorLocation();

		const FRotator& NewRotation = UKismetMathLibrary::FindLookAtRotation(ObjectLocation, TargetLocation);
		
		SetActorRotation(NewRotation);

		const FVector& Direction = (TargetLocation - ObjectLocation).GetSafeNormal();

		ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;
	}
}