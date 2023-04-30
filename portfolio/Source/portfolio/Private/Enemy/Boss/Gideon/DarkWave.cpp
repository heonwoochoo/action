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
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADarkWave::OnOverlapped);
		BoxComponent->SetGenerateOverlapEvents(false);
	}
	
	// 오버랩 타이머 설정
	GetWorld()->GetTimerManager().SetTimer(OverlapActivateTimerHandle, this, &ADarkWave::ActivateOverlap, OverlapStartTime, false);
	GetWorld()->GetTimerManager().SetTimer(OverlapDeactivateTimerHandle, this, &ADarkWave::ActivateOverlap, OverlapEndTime, false);

	SetLifeSpan(3.f);
}

void ADarkWave::ActivateOverlap()
{
	if (BoxComponent)
	{
		BoxComponent->SetGenerateOverlapEvents(true);
	}
}

void ADarkWave::DeactivateOverlap()
{
	if (BoxComponent)
	{
		BoxComponent->SetGenerateOverlapEvents(false);
	}
}

void ADarkWave::OnOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	const bool IsPlayer = OtherActor->ActorHasTag(FName("Player"));
	const bool IsDead = OtherActor->ActorHasTag(FName("Dead"));

	if (IsPlayer && !IsDead)
	{
		const FVector& HitLocation = OtherActor->GetActorLocation();

		// 데미지 적용
		UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, Owner, TSubclassOf<UDamageType>());
		
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

		// 오버랩 비활성화
		BoxComponent->SetGenerateOverlapEvents(false);
	}
}
