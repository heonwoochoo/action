// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillActor/Assassin/ThrowingSlash.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DefaultCharacter.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy/EnemyBase.h"

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
		AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
		if (!Enemy) return;

		// ���� �������� ���� ī��Ʈ üũ
		if (DamagedActors.Contains(Enemy))
		{
			uint8 Count = DamagedActors[Enemy];
			if (SlashType == ESlashType::EST_Single)
			{
				if (Count >= 1)
				{
					return;
				}
			}
			else if (SlashType == ESlashType::EST_Multi)
			{
				if (Count >= 3)
				{
					return;
				}
			}
		}
		else
		{
			DamagedActors.Add(Enemy);
			DamagedActors[Enemy] = 0;
		}

		ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(Owner);
		if (DefaultCharacter)
		{
			// ���
			if (SlashType == ESlashType::EST_Multi)
			{
				Enemy->LaunchCharacter(FVector(0.f, 0.f, 100.f), false, true);
			}

			// ������ ����
			DefaultCharacter->DamageToEnemy(Enemy, Damage);

			DamagedActors[Enemy] += 1;

			// Hit Impact ����
			if (HitImpactEmitter)
			{
				const FVector& ImpactLocation = Enemy->GetActorLocation();
				UGameplayStatics::SpawnEmitterAtLocation(this, HitImpactEmitter, ImpactLocation);
			}
		}
	}
}

void AThrowingSlash::SetSlashType(const ESlashType& NewType)
{
	if (!BoxCollision) return;

	// Ÿ�Կ� ���� �浹ü ũ�⸦ �ٸ��� ����
	if (NewType == ESlashType::EST_Single)
	{
		BoxCollision->SetBoxExtent(FVector(1.f, 200.f, 16.f));
	}
	else if (NewType == ESlashType::EST_Multi)
	{
		BoxCollision->SetBoxExtent(FVector(1.f, 300.f, 300.f));
	}

	SlashType = NewType;
}
