// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Boss/Gideon/DarkSword.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "DefaultCharacter.h"
#include "Components/SphereComponent.h"
#include "Curves/CurveFloat.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"

ADarkSword::ADarkSword()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(SphereCollision);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->Velocity = FVector::Zero();

	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComponent"));
	ParticleComponent->SetupAttachment(GetRootComponent());

}

void ADarkSword::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void ADarkSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ElapsedTime += DeltaTime;

	// 마스크 효과
	if (!bIsMaskMax && StaticMeshComponent && MaskCurveFloat)
	{
		const float& MaskValue = MaskCurveFloat->GetFloatValue(ElapsedTime);
		StaticMeshComponent->SetScalarParameterValueOnMaterials(FName(TEXT("Mask")), MaskValue);

		if (MaskValue == -1.f)
		{
			// 마스크가 최대값에 도달
			bIsMaskMax = true;

			// 투사체 위치 설정
			if (Target)
			{
				ProjectileTargetLocation = Target->GetActorLocation();
			}
		}
	}

	// 회전
	if (!bIsRotationEnd && ElapsedTime > 2.f && !ProjectileTargetLocation.IsZero() && AlphaCurveFloat)
	{
		const FVector& StartLocation = GetActorLocation();

		const FRotator& FoundRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, ProjectileTargetLocation);
		const FRotator& CurrentRotation = GetActorRotation();

		const float& Alpha = AlphaCurveFloat->GetFloatValue(ElapsedTime);

		const FRotator& NewRotation = FMath::Lerp(CurrentRotation, FoundRotation, Alpha);
		SetActorRotation(NewRotation);

		if (Alpha >= 1.f)
		{
			// 목표 방향으로 회전 끝
			bIsRotationEnd = true;
		}
	}
}
