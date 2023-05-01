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
#include "Kismet/KismetSystemLibrary.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraShakeBase.h"
#include "Enemy/Boss/Gideon/BossGideon.h"

ADarkSword::ADarkSword()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(SphereCollision);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	DamageBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DamageBox"));
	DamageBox->SetupAttachment(StaticMeshComponent);

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
	
	if (SphereCollision && DamageBox)
	{
		SphereCollision->OnComponentHit.AddDynamic(this, &ADarkSword::OnHitCollision);
		DamageBox->OnComponentBeginOverlap.AddDynamic(this, &ADarkSword::OnOverlappedDamageBox);

		DamageBox->SetGenerateOverlapEvents(false);
	}
}

void ADarkSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!StaticMeshComponent) return;

	ElapsedTime += DeltaTime;

	// 마스크 효과
	ChangeMeshMask();

	// 회전
	RotateMesh(DeltaTime);

	// ThresHold 알파 타이머가 세팅된 후
	ChangeMeshThresHold();

	// Rune opacity 타이머가 세팅된 후
	ChangeRuneOpacity();
}

void ADarkSword::OnHitCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 충돌체가 블락 (World Static에만 해당)
	// ThresHold 알파값을 변화시켜 오브젝트 제거함
	const bool IsBlockedWorldStatic = OtherComp->GetCollisionObjectType() == ECollisionChannel::ECC_WorldStatic;
	if (IsBlockedWorldStatic)
	{
		const float& ChangedRate = 2.f;
		GetWorld()->GetTimerManager().SetTimer(AlphaTimerHandle, this, &ADarkSword::OnEndThresHoldChange, ChangedRate, false);
		
		if (HitBlockedParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitBlockedParticle, Hit.ImpactPoint);
		}

		// 카메라 쉐이크
		ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(Target);
		if (DefaultCharacter)
		{
			DefaultCharacter->PlayCameraShake(HitGroundImapctCameraShake);
		}

		// 데미지 오버랩 해제
		DamageBox->SetGenerateOverlapEvents(false);
	}
}

void ADarkSword::OnOverlappedDamageBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const bool& IsPlayer = OtherActor->ActorHasTag(FName(TEXT("Player")));
	const bool& IsDead = OtherActor->ActorHasTag(FName(TEXT("Dead")));

	if (IsPlayer && !IsDead && DamageBox)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, Owner, TSubclassOf<UDamageType>());	
		
		if (HitImpactParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitImpactParticle, OtherActor->GetActorLocation());
		}

		// 데미지 오버랩 해제
		DamageBox->SetGenerateOverlapEvents(false);
	}
}

void ADarkSword::ActivateProjectile()
{
	DamageBox->SetGenerateOverlapEvents(true);
	ProjectileMovementComponent->Velocity = ProjectileDirection * MoveSpeed;
}

void ADarkSword::OnEndThresHoldChange()
{
	Destroy();
}

void ADarkSword::OnEndRuneOpacityChange()
{
	MagicCircle->DestroyComponent();
}

void ADarkSword::MoveToTarget()
{
	const FVector& Start = GetActorLocation();
	const FVector& End = GetActorLocation() + GetActorForwardVector() * 3000.f;
	const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes = { UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic)};
	const TArray<AActor*>& ActorsToIgnore = {Target, Owner};

	TArray<FHitResult> OutHits;
	UKismetSystemLibrary::LineTraceMultiForObjects(this, Start, End, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::Persistent, OutHits, true);

	// 바닥에 룬 파티클 생성
	for (const FHitResult& OutHit : OutHits)
	{
		const bool IsHitFloor = OutHit.GetComponent()->ComponentHasTag(FName(TEXT("Floor")));
		if (IsHitFloor && CircleRuneParticle)
		{
			const FVector& CircleLocation = OutHit.Location;
			SpawnCircleRune(CircleLocation);
		}
	}

	// 움직일 방향 설정
	ProjectileDirection = (End - Start).GetSafeNormal();
	
	// 타겟 설정 후 딜레이
	GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle, this, &ADarkSword::ActivateProjectile, MoveDelayRate, false);
}

void ADarkSword::SpawnCircleRune(const FVector& Location)
{
	MagicCircle = UGameplayStatics::SpawnEmitterAtLocation(this, CircleRuneParticle, Location);

	UMaterialInterface* CircleMaterial = MagicCircle->GetMaterial(1);

	CircleMaterialInstance = MagicCircle->CreateNamedDynamicMaterialInstance(FName(TEXT("Circle")), CircleMaterial);

	if (CircleMaterialInstance)
	{
		MagicCircle->SetMaterial(1, CircleMaterialInstance);
	}

	GetWorld()->GetTimerManager().SetTimer(RuneOpacityTimerHandle, this, &ADarkSword::OnEndRuneOpacityChange, 2.f, false);
}

void ADarkSword::ChangeMeshMask()
{
	if (!bIsMaskMax && MaskCurveFloat)
	{
		const float& MaskValue = MaskCurveFloat->GetFloatValue(ElapsedTime);
		StaticMeshComponent->SetScalarParameterValueOnMaterials(FName(TEXT("Mask")), MaskValue);

		if (MaskValue == -1.f)
		{
			// 마스크가 최대값에 도달
			bIsMaskMax = true;
		}
	}
}

void ADarkSword::RotateMesh(float DeltaTime)
{
	if (!bIsRotationEnd && ElapsedTime > 1.5f && Target)
	{
		// 메쉬의 회전
		const double& MeshPitch = StaticMeshComponent->GetRelativeRotation().Pitch;
		const double& NewMeshPitch = FMath::FInterpTo(MeshPitch, -90, DeltaTime, 5.f);
		FRotator MeshRotation = StaticMeshComponent->GetRelativeRotation();
		MeshRotation.Pitch = NewMeshPitch;
		StaticMeshComponent->SetRelativeRotation(MeshRotation);


		// 루트 컴포넌트의 회전
		const FVector& StartLocation = GetActorLocation();
		FVector TargetLocation = Target->GetActorLocation();
		TargetLocation.Z -= 30.f;	// 높이 보정

		const FRotator& FoundRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation);
		const FRotator& CurrentRotation = GetActorRotation();

		const double& Pitch = FMath::FInterpTo(CurrentRotation.Pitch, FoundRotation.Pitch, DeltaTime, 5.f);
		const double& Yaw = FMath::FInterpTo(CurrentRotation.Yaw, FoundRotation.Yaw, DeltaTime, 5.f);
		const double& Roll = FMath::FInterpTo(CurrentRotation.Roll, FoundRotation.Roll, DeltaTime, 5.f);

		const FRotator& NewRotation = FRotator(Pitch, Yaw, Roll);

		SetActorRotation(NewRotation);

		// 캐스팅 동안 시전자의 시선은 타겟을 바라보게 모션워핑을 업데이트
		if (Owner)
		{
			ABossGideon* Caster = Cast<ABossGideon>(Owner);
			if (Caster)
			{
				Caster->SetMotionWarpRotationToTarget();
			}
		}

		if (ElapsedTime > 2.5f)
		{
			bIsRotationEnd = true;
			MoveToTarget();
		}
	}
}

void ADarkSword::ChangeMeshThresHold()
{
	if (AlphaTimerHandle.IsValid() && AlphaCurveFloat)
	{
		const FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		const float& AlphaTimerElapsed = TimerManager.GetTimerElapsed(AlphaTimerHandle);
		const float& AlphaValue = AlphaCurveFloat->GetFloatValue(AlphaTimerElapsed);

		StaticMeshComponent->SetScalarParameterValueOnMaterials(FName(TEXT("AlphaThreshold")), AlphaValue);
	}
}

void ADarkSword::ChangeRuneOpacity()
{
	if (RuneOpacityTimerHandle.IsValid() && RuneOpacityCurveFloat && CircleMaterialInstance)
	{
		const FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		const float& OpacityTimerElapsed = TimerManager.GetTimerElapsed(RuneOpacityTimerHandle);
		const float& OpacityValue = RuneOpacityCurveFloat->GetFloatValue(OpacityTimerElapsed);

		CircleMaterialInstance->SetScalarParameterValue(FName(TEXT("Opacity")), OpacityValue);
	}
}
