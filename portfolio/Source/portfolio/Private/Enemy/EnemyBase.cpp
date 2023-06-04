// Fill out your copyright notice in the DescrUKismetiption page of Project Settings.


#include "Enemy/EnemyBase.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DefaultCharacter.h"
#include "Camera/CameraComponent.h"
#include "SkillActor/Assassin/KnifeProjectile.h"
#include "HUD/Combat/EnemyHPBarWidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/EnemyAnimInstance.h"
#include "MotionWarpingComponent.h"
#include "HUD/HUDBase.h"
#include "Controller/CharacterController.h"
#include "HUD/Combat/DamageText.h"
#include "Types/EnemyTypes.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "Component/DamagedComponent.h"
#include "HelperFunction.h"
#include "Component/QuestClientComponent.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;
	SetRootComponent(GetCapsuleComponent());

	HPBarWidgetComponent = CreateDefaultSubobject<UEnemyHPBarWidgetComponent>(TEXT("HPBarComponent"));
	if (HPBarWidgetComponent)
	{
		HPBarWidgetComponent->SetupAttachment(GetCapsuleComponent());
		HPBarWidgetComponent->SetVisibility(true);
	}
	
	DamagedComponent = CreateDefaultSubobject<UDamagedComponent>(TEXT("DamagedComponent"));

	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensing->SetPeripheralVisionAngle(45.f);
	PawnSensing->SightRadius = 2000.f;

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (PawnSensing) PawnSensing->OnSeePawn.AddDynamic(this, &AEnemyBase::PawnSeen);

	EnemyController = Cast<AAIController>(GetController());
	
	HideHealthBar();
	Tags.Add(FName("Enemy"));

	InitPatrolTarget();

	MoveToTarget(PatrolTarget);
}

void AEnemyBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (EnemyStatsDataTable)
	{
		if (EnemyCode.IsValid())
		{
			Stats = *EnemyStatsDataTable->FindRow<FEnemyStats>(EnemyCode, "");
		}

		GetMesh()->SetAnimClass(Stats.AnimationClass);
		GetMesh()->SetSkeletalMeshAsset(Stats.SkeletalMesh);
	}
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (State == EEnemyState::EES_Dead) return;

	if (State == EEnemyState::EES_Dead)
	{
		UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
		if (!MovementComponent->IsFalling())
		{
			MovementComponent->SetMovementMode(EMovementMode::MOVE_None);
		}
	}

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
	UGameplayStatics::GetAllActorsWithTag(this, FName(TEXT("Patrol")), PatrolTargets);

	if (PatrolTargets.Num() > 1)
	{
		const int32 RandIdx = FMath::RandRange(0, PatrolTargets.Num() - 1);
		PatrolTarget = PatrolTargets[RandIdx];
		MoveToTarget(PatrolTarget);
	}
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
	
	DamageAmount = UHelperFunction::GetRandomDamage(DamageAmount);

	if (!DamagedComponent) return DamageAmount;
	
	DamagedComponent->ApplyHitOverlayMaterial();
	DamagedComponent->ChangeMeshOutline();

	//크리티컬 적용
	const bool& IsCritical = DamagedComponent->IsDamagedCritical(DamageCauser);
	if (IsCritical)
	{
		DamageAmount *= 1.5f;
	}

	HandleDamage(DamageCauser, DamageAmount, IsCritical);

	HandleAttackTarget(EventInstigator);

	// 경직 효과
	ADefaultCharacter* PlayerCharacter = Cast<ADefaultCharacter>(DamageCauser);
	if (PlayerCharacter && DamagedComponent)
	{
		const float& HitTimeDilation = PlayerCharacter->GetHitTimeDilation();
		const float& HitTimeDilationDelay = PlayerCharacter->GetHitTimeDilationDelay();
		DamagedComponent->SetTimeDilation(HitTimeDilation, HitTimeDilationDelay);
	}

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

void AEnemyBase::HandleDamage(AActor* DamageCauser, const float& DamageAmount, const bool& IsCritical)
{
	DamageCauserActor = DamageCauser;
	Stats.Hp = FMath::Clamp(Stats.Hp - DamageAmount, 0.f, Stats.MaxHp);

	OnChangedHp.Broadcast(Stats.Hp, Stats.MaxHp);

	if (DamagedComponent)
	{
		DamagedComponent->ShowDamageText(DamageAmount, IsCritical);
	}

	if (Stats.Hp <= 0.f)
	{
		Die();
	}
	else
	{
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
		int32 RandNum = FMath::RandRange(0, DropItemList.Num() - 1);
		
		const FVector Location{ GetMesh()->GetComponentLocation() };
		const FRotator Rotation{ GetActorRotation() };
		GetWorld()->SpawnActor<AActor>(DropItemList[RandNum], Location, Rotation);
	};
}

void AEnemyBase::Die()
{
	State = EEnemyState::EES_Dead;
	Tags.Add(FName("Dead"));
	
	if (CombatTarget)
	{
		ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(CombatTarget);
		if (DefaultCharacter)
		{
			// 유저가 경험치를 획득
			DefaultCharacter->UpdateStatManager(EStatTarget::EST_Exp, EStatUpdateType::ESUT_Plus, Stats.Exp);
			
			// 유저의 퀘스트 목록에 존재하면 업데이트
			UQuestClientComponent* QuestClientComponent = DefaultCharacter->GetQuestClientComponent();
			if (QuestClientComponent)
			{
				bool IsExist = QuestClientComponent->IsExistEnemyInQuestList(EnemyCode);
				if (IsExist)
				{
					// 유저의 상태를 업데이트
					QuestClientComponent->AddEnemyKillCount(FName(EnemyCode), 1);
				}
			}
		}
	}

	if (DamagedComponent)
	{
		DamagedComponent->RemoveMeshOutline();
	}

	HPBarWidgetComponent->SetVisibility(false);

	MotionWarpingComponent->Deactivate();

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

void AEnemyBase::HitRotationEnd()
{
	MotionWarpingComponent->AddOrUpdateWarpTargetFromLocation(FName("HitReactLocation"), GetActorLocation() - GetActorForwardVector() * KnockBackDistance);
}