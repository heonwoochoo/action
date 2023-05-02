// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Boss/BossBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DefaultCharacter.h"
#include "AIController.h"
#include "Animation/BossAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "MotionWarpingComponent.h"
#include "HUD/Combat/BossHPBar.h"
#include "Controller/CharacterController.h"
#include "HUD/HUDBase.h"

// Sets default values
ABossBase::ABossBase()
{
	PrimaryActorTick.bCanEverTick = true;
	SetRootComponent(GetCapsuleComponent());

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarp"));
	MotionWarpingComponent->SetActive(true);

	LoadStats();
}

void ABossBase::BeginPlay()
{
	Super::BeginPlay();
	
	Tags.Add(FName(TEXT("Enemy")));
	Tags.Add(FName(TEXT("Boss")));

	BossController = Cast<AAIController>(GetController());

	UBossAnimInstance* AnimInstance = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->PlayOpeningAnimation();
	}
	
}

void ABossBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	LoadStats();
}

void ABossBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


float ABossBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// State가 Rest일 때만 hitreact 애니메이션 적용

	if (DamageCauser->ActorHasTag(FName(TEXT("Player"))))
	{
		ApplyHitOverlayMaterial();

		ChangeMeshOutline();

		if (State == EBossState::EBS_Resting || State == EBossState::EBS_NoState)
		{
			UBossAnimInstance* AnimInstance = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
			if (AnimInstance)
			{
				Stats.Hp = FMath::Clamp(Stats.Hp - DamageAmount, 0, Stats.MaxHp);
				OnChanged.Broadcast(Stats.Hp, Stats.MaxHp);

				if (Stats.Hp == 0)
				{
					Die();
				}
				else
				{
					SetMotionWarpRotationToTarget();
					AnimInstance->PlayHitReactAnimation();
				}
			}
		}
	}
	return 0.0f;
}

void ABossBase::FindTarget()
{
	const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes = { UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn)};
	const TArray<AActor*> ActorsToIgnore = {this};
	TArray<AActor*> OutActors;
	bool Exist = UKismetSystemLibrary::SphereOverlapActors(this, GetActorLocation(), 3000.f, ObjectTypes, TSubclassOf<AActor>(), ActorsToIgnore, OutActors);

	if (Exist && OutActors.Num() > 0)
	{
		for (auto Actor : OutActors)
		{
			if (Actor->ActorHasTag(FName("Player")))
			{
				// 타겟 설정
				CombatTarget = Actor;

				
				ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(CombatTarget);
				if (DefaultCharacter)
				{
					// 타겟이 죽었을 때를 구독
					DefaultCharacter->OnDead.AddDynamic(this, &ABossBase::OnCombatTargetDead);

					// 유저 화면에 HP Bar 생성
					ACharacterController* TargetController = Cast<ACharacterController>(DefaultCharacter->GetController());
					if (TargetController)
					{
						AHUDBase* HUD = Cast<AHUDBase>(TargetController->GetHUD());
						if (HUD)
						{
							HUD->CreateBossHPBar(this);
						}
					}
				}
			}
		}
	}
}

bool ABossBase::IsTargetInRange(const float& Radius, AActor* Target)
{
	const float Distance = (Target->GetActorLocation() - GetActorLocation()).Length();

	if (Distance < Radius)
	{
		return true;
	}
	return false;
}

bool ABossBase::HasTarget()
{
	if (CombatTarget != nullptr)
	{
		return true;
	}
	return false;
}

void ABossBase::RotateBodyToCombatTarget(float DeltaTime)
{
	if (CombatTarget)
	{
		const FVector& StartLocation = GetActorLocation();
		const FVector& TargetLocation = CombatTarget->GetActorLocation();

		const double& LookAtYaw = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation).Yaw;
		const double& CurrentYaw = GetActorRotation().Yaw;

		const double& NewYaw = FMath::FInterpTo(CurrentYaw, LookAtYaw, DeltaTime, 5.f);

		FRotator CurrentRotator = GetActorRotation();
		CurrentRotator.Yaw = NewYaw;
		SetActorRotation(CurrentRotator);
	}
}

void ABossBase::RotateBodyToCombatTarget()
{
	if (CombatTarget)
	{
		const FVector& StartLocation = GetActorLocation();
		const FVector& TargetLocation = CombatTarget->GetActorLocation();

		const double& LookAtYaw = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation).Yaw;

		FRotator CurrentRotator = GetActorRotation();
		CurrentRotator.Yaw = LookAtYaw;

		SetActorRotation(CurrentRotator);
	}
}

void ABossBase::SetMotionWarpRotationToTarget()
{
	if (CombatTarget)
	{
		// 모션워핑 업데이트
		const FVector& TargetLocation = CombatTarget->GetActorLocation();
		MotionWarpingComponent->AddOrUpdateWarpTargetFromLocation(FName("RotateToTarget"), TargetLocation);
	}
}

void ABossBase::ChaseTarget()
{
	if (CombatTarget && BossController && State != EBossState::EBS_Dead)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		FAIMoveRequest AIMoveRequest;
		AIMoveRequest.SetAcceptanceRadius(AcceptanceRadius);
		AIMoveRequest.SetGoalActor(CombatTarget);
		BossController->MoveTo(AIMoveRequest);
		SetState(EBossState::EBS_Chasing);
	}
}

void ABossBase::OnCombatTargetDead()
{
	RotateBodyToCombatTarget();

	CombatTarget = nullptr;

	State = EBossState::EBS_NoState;

	// 애니메이션 재생
	UBossAnimInstance* AnimInstance = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->PlayVictoryAnimation();
	}
}

void ABossBase::Die()
{
	CombatTarget = nullptr;
	RemoveMeshOutline();
}

void ABossBase::ApplyHitOverlayMaterial()
{
	if (GetMesh() && HitMaterialInstance)
	{
		GetMesh()->SetOverlayMaterial(HitMaterialInstance);
		GetWorld()->GetTimerManager().SetTimer(HitOverlayTimerHandle, this, &ABossBase::OnEndHitOveralyTimer, 0.1f, false);
	}
}

void ABossBase::OnEndHitOveralyTimer()
{
	GetMesh()->SetOverlayMaterial(nullptr);
}

void ABossBase::ChangeMeshOutline()
{
	// 월드에 배치된 포스트 프로세싱에 영향을 받음
	// 외형선을 빨강으로 나타냄
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(1);

	GetWorld()->GetTimerManager().ClearTimer(MeshOutlineTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(MeshOutlineTimerHandle, this, &ABossBase::RemoveMeshOutline, HitOutlineDurationTime, false);
}

void ABossBase::RemoveMeshOutline()
{
	GetMesh()->SetRenderCustomDepth(false);
}

void ABossBase::LoadStats()
{
	if (BossCode.IsValid() && BossStatsDataTable)
	{
		Stats = *BossStatsDataTable->FindRow<FBossStats>(BossCode, "");
		
		USkeletalMeshComponent* SkeletalMesh = GetMesh();
		if (SkeletalMesh && BossStatsDataTable && BossCode.IsValid())
		{
			SkeletalMesh->SetSkeletalMesh(Stats.SkeletalMesh);
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
			GetMesh()->SetAnimClass(Stats.AnimationClass);
		}
	}
}

