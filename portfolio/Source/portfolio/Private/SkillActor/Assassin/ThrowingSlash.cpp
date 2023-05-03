// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillActor/Assassin/ThrowingSlash.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DefaultCharacter.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

AThrowingSlash::AThrowingSlash()
{

	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("SlashCollision"));
	BoxCollision->SetGenerateOverlapEvents(true);
	SetRootComponent(BoxCollision);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	ProjectileMovementComponent->InitialSpeed = SlashSpeed;
	ProjectileMovementComponent->MaxSpeed = SlashSpeed;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;

}

void AThrowingSlash::BeginPlay()
{
	Super::BeginPlay();
	
	if (BoxCollision)
	{
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AThrowingSlash::OnOverlapped);
	}

	SetLifeSpan(1.5f);
}

void AThrowingSlash::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AThrowingSlash::OnOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName(TEXT("Enemy"))) && Owner)
	{
		// 증복 체크
		if (DamagedActors.Contains(OtherActor))
		{
			return;
		}

		ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(Owner);
		if (DefaultCharacter)
		{
			// 데미지 적용
			DefaultCharacter->DamageToEnemy(OtherActor, Damage);
			DamagedActors.Add(OtherActor);

			// Hit Impact 생성
			if (HitImpactEmitter)
			{
				const FVector& ImpactLocation = Owner->GetActorLocation();
				UGameplayStatics::SpawnEmitterAtLocation(this, HitImpactEmitter, ImpactLocation);
			}
		}
	}
}