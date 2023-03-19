// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyBase.h"
#include "Data/EnemyDataAsset.h"
#include "HUD/TargetWidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "portfolio/portfolioCharacter.h"
#include "Component/AbilityComponent.h"
#include "Camera/CameraComponent.h"
#include "Items/KnifeProjectile.h"
#include "HUD/EnemyHPBarWidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/EnemyAnimInstance.h"
#include "MotionWarpingComponent.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

	if (DataAsset)
	{
		EnemyData = DataAsset->EnemyDatas[Name];
	}

	SetRootComponent(GetCapsuleComponent());
	TargetWidgetComponent = CreateDefaultSubobject<UTargetWidgetComponent>(TEXT("TargetImgComponent"));
	if (TargetWidgetComponent)
	{
		TargetWidgetComponent->SetupAttachment(GetCapsuleComponent());
		TargetWidgetComponent->SetVisibility(false);
	}

	HPBarWidgetComponent = CreateDefaultSubobject<UEnemyHPBarWidgetComponent>(TEXT("HPBarComponent"));
	if (HPBarWidgetComponent)
	{
		HPBarWidgetComponent->SetupAttachment(GetCapsuleComponent());
		HPBarWidgetComponent->SetVisibility(true);
	}
	
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	GetMesh()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnBeginOverlapped);
}

float AEnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	if (State != EEnemyState::EES_Dead)
	{
		UEnemyAnimInstance* AnimInstance = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
		if (AnimInstance)
		{
			if (!GetCharacterMovement()->IsFalling())
			{
				AnimInstance->PlayHitReactOnGround();
				const FVector TargetLocation = GetActorLocation() - GetActorForwardVector() * 5.f;
				MotionWarpingComponent->AddOrUpdateWarpTargetFromLocation(FName("HitReactRotation"), DamageCauser->GetActorLocation());
				MotionWarpingComponent->AddOrUpdateWarpTargetFromLocation(FName("HitReactLocation"), GetActorLocation() - GetActorForwardVector() * 100.f);
			}
		}
	}
	return DamageAmount;
}


void AEnemyBase::TargetTimerEnd()
{
	SetTargetImgVisibie(false);
	if (State == EEnemyState::EES_Targeted) State = EEnemyState::EES_Unoccupied;

	AportfolioCharacter* Character = Cast<AportfolioCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (Character) Character->GetAbilityComponent()->SetDashTarget(nullptr);
}

void AEnemyBase::DisplayTargetWidget()
{
	SetTargetImgVisibie(true);
	State = EEnemyState::EES_Targeted;
	GetWorldTimerManager().SetTimer(TargetTimerHandle, this, &AEnemyBase::TargetTimerEnd, TargetDurationTime, false);
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
		DisplayTargetWidget();
		AKnifeProjectile* KnifeProjectile = Cast<AKnifeProjectile>(OtherActor);
		if (KnifeProjectile) KnifeProjectile->OnKnifeEffect(this);
	}
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TargetWidgetComponent && State == EEnemyState::EES_Targeted)
	{
		AportfolioCharacter* Character = Cast<AportfolioCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
		const FRotator Rotation = (Character->GetFollowCamera()->GetComponentLocation() - GetActorLocation()).ToOrientationQuat().Rotator();
		TargetWidgetComponent->SetWorldRotation(Rotation);
	}
}