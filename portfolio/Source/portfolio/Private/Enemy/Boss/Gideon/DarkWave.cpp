// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Boss/Gideon/DarkWave.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Kismet/KismetSystemLibrary.h"

ADarkWave::ADarkWave()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(BoxComponent);

	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComponent"));
	ParticleComponent->SetupAttachment(GetRootComponent());
}

void ADarkWave::BeginPlay()
{
	Super::BeginPlay();
	
	if (BoxComponent)
	{
		BoxComponent->SetGenerateOverlapEvents(true);
	}
	
	// 오버랩 타이머 설정
	GetWorld()->GetTimerManager().SetTimer(OverlapTimerHandle, this, &ADarkWave::CheckOverlapping, OverlapRate, false);

	SetLifeSpan(3.f);
}

void ADarkWave::CheckOverlapping()
{
	if (BoxComponent)
	{
		TArray<AActor*> OverlappingActors;
		BoxComponent->GetOverlappingActors(OverlappingActors);

		for (auto Actor : OverlappingActors)
		{
			const bool IsPlayer = Actor->ActorHasTag(FName("Player"));
			const bool IsDead = Actor->ActorHasTag(FName("Dead"));

			if (IsPlayer && !IsDead)
			{
				const FVector& HitLocation = Actor->GetActorLocation();

				// 데미지 적용
				UGameplayStatics::ApplyDamage(Actor, Damage, nullptr, Owner, TSubclassOf<UDamageType>());

				// 파티클 생성
				if (HitImpactParticle)
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitImpactParticle, HitLocation);
				}
				// 소리 재생
				if (HitSound)
				{
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, HitLocation);
				}
			}
		}
	}
}