// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyBase.h"
#include "HUD/TargetWidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DefaultCharacter.h"
#include "Camera/CameraComponent.h"
#include "Items/KnifeProjectile.h"
#include "HUD/EnemyHPBarWidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/EnemyAnimInstance.h"
#include "MotionWarpingComponent.h"
#include "HUD/HUDBase.h"
#include "Controller/CharacterController.h"
#include "HUD/DamageText.h"
#include "HUD/TargetMark.h"
#include "EnemyTypes.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "Animation/EnemyAnimInstance.h"
#include "Animation/AnimInstanceBase.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;
	SetRootComponent(GetCapsuleComponent());
	TargetWidgetComponent = CreateDefaultSubobject<UTargetWidgetComponent>(TEXT("TargetImgComponent"));

	HPBarWidgetComponent = CreateDefaultSubobject<UEnemyHPBarWidgetComponent>(TEXT("HPBarComponent"));
	if (HPBarWidgetComponent)
	{
		HPBarWidgetComponent->SetupAttachment(GetCapsuleComponent());
		HPBarWidgetComponent->SetVisibility(true);
	}
	
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensing->SetPeripheralVisionAngle(45.f);
	PawnSensing->SightRadius = 2000.f;

	
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	GetMesh()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnBeginOverlapped);
	if (EnemyStatsDataTable)
	{
		if (Name == EEnemyName::EEN_Man)
		{
			Stats = *EnemyStatsDataTable->FindRow<FEnemyStats>(FName("Man"), "");
		}
	}

	if (PawnSensing) PawnSensing->OnSeePawn.AddDynamic(this, &AEnemyBase::PawnSeen);

	EnemyController = Cast<AAIController>(GetController());
	
	HideHealthBar();
	Tags.Add(FName("Enemy"));

	InitPatrolTarget();

	MoveToTarget(PatrolTarget);
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (State == EEnemyState::EES_Dead) return;
	if (State > EEnemyState::EES_Patrolling)
	{
		CheckCombatTarget();
	}
	else
	{
		CheckPatrolTarget();
	}

	if (State == EEnemyState::EES_Engaged && MotionWarpingComponent && CombatTarget)
	{
		const FName WarpName = "RotateToTarget";
		const FVector WarpLocation = CombatTarget->GetActorLocation();
		MotionWarpingComponent->AddOrUpdateWarpTargetFromLocation(WarpName, WarpLocation);
	}
}

void AEnemyBase::PawnSeen(APawn* SeenPawn)
{
	const bool bShouldChaseTarget =
		State != EEnemyState::EES_Dead &&
		State != EEnemyState::EES_Chasing &&
		State < EEnemyState::EES_Attacking &&
		SeenPawn->ActorHasTag(FName("Player"));

	if (bShouldChaseTarget)
	{
		CombatTarget = SeenPawn;

		ChaseTarget();
	}
}

void AEnemyBase::ChaseTarget()
{
	if (State == EEnemyState::EES_Dead) return;
	State = EEnemyState::EES_Chasing;
	GetCharacterMovement()->MaxWalkSpeed = ChasingWalkSpeed;
	MoveToTarget(CombatTarget);
}

bool AEnemyBase::CanAttack()
{
	bool bCanAttack =
		InTargetRange(CombatTarget, AttackRadius) &&
		State != EEnemyState::EES_Attacking &&
		State != EEnemyState::EES_Engaged &&
		State != EEnemyState::EES_Dead;
	return bCanAttack;
}

void AEnemyBase::InitPatrolTarget()
{
	UGameplayStatics::GetAllActorsWithTag(this, FName("Patrol"), PatrolTargets);
	const int32 RandIdx = FMath::RandRange(0, PatrolTargets.Num() - 1);
	PatrolTarget = PatrolTargets[RandIdx];
}

void AEnemyBase::PatrolTimerFinished()
{
	if (State == EEnemyState::EES_Dead) return;
	MoveToTarget(PatrolTarget);
}

void AEnemyBase::PlayAttackAnim()
{
	if (CombatTarget && CombatTarget->ActorHasTag(FName("Dead")))
	{
		CombatTarget = nullptr;
	}
	if (CombatTarget == nullptr) return;

	if (State == EEnemyState::EES_Dead) return;

	State = EEnemyState::EES_Engaged;
	UEnemyAnimInstance* EnemyAnimInstance = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (EnemyAnimInstance)
	{
		EnemyAnimInstance->PlayAttack();
	}
}

void AEnemyBase::AttackCharacter()
{
	const FName SockeName = "FootRightAttack";
	const FVector SocketLocation = GetMesh()->GetSocketLocation(SockeName);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes = { UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn) };
	TArray<AActor*> ActorsToIgnore = { this };
	TArray<AActor*> OutActors;

	UKismetSystemLibrary::SphereOverlapActors(this, SocketLocation, 50.f, ObjectTypes, nullptr, ActorsToIgnore, OutActors);
	DrawDebugSphere(GetWorld(), SocketLocation, 50.f, 16, FColor::Red, false, 1.f);

	for (AActor* Actor : OutActors)
	{
		ADefaultCharacter* Character = Cast<ADefaultCharacter>(Actor);
		if (Character)
		{
			UAnimInstanceBase* AnimInstance = Cast<UAnimInstanceBase>(Character->GetMesh()->GetAnimInstance());
			if (AnimInstance)
			{
				AnimInstance->PlayHitReact();
			}

			DamageToPlayer(Character);
		}
	}
}

void AEnemyBase::AttackEnd()
{
	State = EEnemyState::EES_NoState;
	CheckCombatTarget();
}

void AEnemyBase::StartAttackTimer()
{
	if (State == EEnemyState::EES_Dead) return;
	State = EEnemyState::EES_Attacking;
	const float AttackTime = FMath::RandRange(AttackMin, AttackMax);
	GetWorldTimerManager().SetTimer(AttackTimer, this, &AEnemyBase::PlayAttackAnim, AttackTime);
}

void AEnemyBase::DamageToPlayer(ADefaultCharacter* Character)
{
	TSubclassOf<UDamageType> DamageType;
	UGameplayStatics::ApplyDamage(Character, Stats.Damage, EnemyController, this, DamageType);
}



// AIController가 target으로 이동
void AEnemyBase::MoveToTarget(AActor* Target)
{
	if (EnemyController == nullptr || Target == nullptr || State == EEnemyState::EES_Dead) return;
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(Target);
	MoveRequest.SetAcceptanceRadius(AcceptanceRadius);
	EnemyController->MoveTo(MoveRequest);
}

void AEnemyBase::CheckCombatTarget()
{
	if (State == EEnemyState::EES_Dead) return;
	if (!InTargetRange(CombatTarget, CombatRadius))
	{
		ClearAttackTimer();
		LoseInterest();
		if (State != EEnemyState::EES_Engaged) StartPatrolling();
	}
	else if (!InTargetRange(CombatTarget, AttackRadius) && State != EEnemyState::EES_Chasing)
	{
		ClearAttackTimer();
		if (State != EEnemyState::EES_Engaged) ChaseTarget();
	}
	else if (CanAttack())
	{
		StartAttackTimer();
	}
}

void AEnemyBase::CheckPatrolTarget()
{
	if (InTargetRange(PatrolTarget, PatrolRadius))
	{
		PatrolTarget = ChoosePatrolTarget();
		const float WaitTime = FMath::FRandRange(PatrolWaitMin, PatrolWaitMax);
		GetWorldTimerManager().SetTimer(PatrolTimer, this, &AEnemyBase::PatrolTimerFinished, WaitTime);
	}
}

// Enemy와 타겟의 거리가 Radius 이하면 TRUE를 반환
bool AEnemyBase::InTargetRange(AActor* Target, double Radius)
{
	if (Target == nullptr) return false;
	const double DistanceToTarget = (Target->GetActorLocation() - GetActorLocation()).Size();
	return DistanceToTarget <= Radius;
}

void AEnemyBase::ClearAttackTimer()
{
	GetWorldTimerManager().ClearTimer(AttackTimer);
}

void AEnemyBase::LoseInterest()
{
	CombatTarget = nullptr;
	HideHealthBar();
}

void AEnemyBase::HideHealthBar()
{
	if (HPBarWidgetComponent)
	{
		HPBarWidgetComponent->SetVisibility(false);
	}
}

void AEnemyBase::ShowHealthBar()
{
	if (HPBarWidgetComponent)
	{
		HPBarWidgetComponent->SetVisibility(true);
	}
}

void AEnemyBase::StartPatrolling()
{
	State = EEnemyState::EES_Patrolling;
	GetCharacterMovement()->MaxWalkSpeed = PatrolWalkSpeed;
	MoveToTarget(PatrolTarget);
}

AActor* AEnemyBase::ChoosePatrolTarget()
{
	TArray<AActor*> ValidTargets;
	for (AActor* Target : PatrolTargets)
	{
		if (Target != PatrolTarget)
		{
			ValidTargets.AddUnique(Target);
		}
	}

	const int32 NumPatrolTargets = ValidTargets.Num();
	if (NumPatrolTargets > 0)
	{
		const int32 TargetSelection = FMath::FRandRange(0.f, NumPatrolTargets - 1);
		return ValidTargets[TargetSelection];
	}
	return nullptr;
}

float AEnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	HandleDamage(DamageCauser, DamageAmount);

	HandleAttackTarget(EventInstigator);

	return DamageAmount;
}

void AEnemyBase::HandleAttackTarget(AController* EventInstigator)
{
	if (State == EEnemyState::EES_Dead) return;
	CombatTarget = EventInstigator->GetPawn();
	if (InTargetRange(CombatTarget, AttackRadius))
	{
		State = EEnemyState::EES_Attacking;
	}
	else if (!InTargetRange(CombatTarget, AttackRadius))
	{
		ChaseTarget();
	}
}

void AEnemyBase::HandleDamage(AActor* DamageCauser, float DamageAmount)
{
	DamageCauserActor = DamageCauser;
	Stats.Hp -= DamageAmount;

	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController)
	{
		AHUDBase* HUDBase = Cast<AHUDBase>(CharacterController->GetHUD());
		if (HUDBase) HUDBase->ShowDamageOnScreen(this, DamageAmount);
	}

	if (Stats.Hp <= 0.f)
	{
		Die();
	}
	else
	{
		UpdateHPBar();
		PlayHitAnimNextTick();
	}
}

void AEnemyBase::Destroyed()
{
	Super::Destroyed();
	DropItem();
}

void AEnemyBase::DropItem()
{
	if (FMath::FRand() < ItemDropRate && DropItemList.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Drop Item"));
		int32 RandNum = FMath::RandRange(0, DropItemList.Num() - 1);
		const FVector Location{ GetActorLocation() };
		const FRotator Rotation{ GetActorRotation() };
		GetWorld()->SpawnActor<AActor>(DropItemList[RandNum], Location, Rotation);
	};
}

void AEnemyBase::Die()
{
	State = EEnemyState::EES_Dead;

	HPBarWidgetComponent->SetVisibility(false);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	LoseInterest();

	PlayDeadAnim();

	SetLifeSpan(3.f);
}

void AEnemyBase::PlayHitAnimNextTick()
{
	GetWorld()->GetTimerManager().SetTimer(TakeDamageHandle, this, &AEnemyBase::PlayHitAnim, 0.01f);
}

void AEnemyBase::PlayHitAnim()
{
	UEnemyAnimInstance* AnimInstance = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance && State != EEnemyState::EES_Dead)
	{
		if (!GetCharacterMovement()->IsFalling())
		{
			ShowHealthBar();
			AnimInstance->PlayHitReactOnGround();
			MotionWarpingComponent->AddOrUpdateWarpTargetFromLocation(FName("HitReactRotation"), DamageCauserActor->GetActorLocation());

		}
		else
		{
			ShowHealthBar();
			AnimInstance->PlayHitReactOnAir();
		}
	}
}

void AEnemyBase::PlayDeadAnim()
{
	UEnemyAnimInstance* AnimInstance = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{

		AnimInstance->PlayDead();
	}
}


EEnemyState AEnemyBase::GetState() const
{
	return State;
}

void AEnemyBase::SetState(EEnemyState NewState)
{
	State = NewState;
}

void AEnemyBase::SetTargetImgVisibie(bool NewState)
{
	if (TargetWidgetComponent)
	{
		NewState ? TargetWidgetComponent->SetVisibility(true) : TargetWidgetComponent->SetVisibility(false);
	}
}

void AEnemyBase::OnBeginOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName("KnifeProjectile")))
	{
		AKnifeProjectile* KnifeProjectile = Cast<AKnifeProjectile>(OtherActor);
		if (KnifeProjectile)
		{
			KnifeProjectile->OnKnifeEffect(this);
			ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
			if (CharacterController)
			{
				AHUDBase* HUDBase = Cast<AHUDBase>(CharacterController->GetHUD());
				if (HUDBase) HUDBase->ShowTargetMark(this, KnifeProjectile->Caster);
			}
		}
	}
}

void AEnemyBase::HitRotationEnd()
{
	MotionWarpingComponent->AddOrUpdateWarpTargetFromLocation(FName("HitReactLocation"), GetActorLocation() - GetActorForwardVector() * KnockBackDistance);
}

void AEnemyBase::UpdateHPBar()
{
	const float CurrentHP = GetEnemyStats().Hp;
	const float MaxHP = GetEnemyStats().MaxHp;
	HPBarWidgetComponent->SetHPBar(CurrentHP / MaxHP);
}

void AEnemyBase::SetHeadUpMark(AActor* NewMark)
{
	HeadUpMark = NewMark;
}

void AEnemyBase::RemoveMark()
{
	if (HeadUpMark) HeadUpMark->Destroy();
}



void AEnemyBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (EnemyStatsDataTable)
	{
		if (Name == EEnemyName::EEN_Man)
		{
			Stats = *EnemyStatsDataTable->FindRow<FEnemyStats>(FName("Man"), "");
		}
	}
}
