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
#include "HUD/HUDBase.h"
#include "Controller/CharacterController.h"
#include "HUD/DamageText.h"

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
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	GetMesh()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnBeginOverlapped);
	if (DataAsset)
	{
		EnemyData = DataAsset->EnemyDatas[Name];
	}

	if (TargetWidgetComponent)
	{
		TargetWidgetComponent->SetTargetVisible(false);
	}
}

float AEnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	EnemyData.Hp -= DamageAmount;

	DisplayDamageText(DamageAmount);

	UpdateHPBar();

	UEnemyAnimInstance* AnimInstance = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance && State != EEnemyState::EES_Dead)
	{
		if (!GetCharacterMovement()->IsFalling())
		{
			AnimInstance->PlayHitReactOnGround();
			MotionWarpingComponent->AddOrUpdateWarpTargetFromLocation(FName("HitReactRotation"), DamageCauser->GetActorLocation());
		}
	}
	
	return DamageAmount;
}


void AEnemyBase::TargetTimerEnd()
{
	TargetWidgetComponent->SetTargetVisible(false);
	//SetTargetImgVisibie(false);
	if (State == EEnemyState::EES_Targeted) State = EEnemyState::EES_Unoccupied;

	AportfolioCharacter* Character = Cast<AportfolioCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (Character) Character->GetAbilityComponent()->SetDashTarget(nullptr);
}

void AEnemyBase::DisplayTargetWidget()
{
	TargetWidgetComponent->SetTargetVisible(true);
	//SetTargetImgVisibie(true);
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

void AEnemyBase::HitRotationEnd()
{
	MotionWarpingComponent->AddOrUpdateWarpTargetFromLocation(FName("HitReactLocation"), GetActorLocation() - GetActorForwardVector() * KnockBackDistance);
}

void AEnemyBase::UpdateHPBar()
{
	if (DataAsset && EnemyData.Hp <= 0.f)
	{
		State = EEnemyState::EES_Dead;
		HPBarWidgetComponent->SetVisibility(false);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		SetLifeSpan(3.f);
	}
	else
	{
		const float CurrentHP = GetEnemyData().Hp;
		const float MaxHP = GetEnemyData().MaxHp;
		HPBarWidgetComponent->SetHPBar(CurrentHP / MaxHP);
	}
}

void AEnemyBase::DisplayDamageText(const float Damage)
{
	FVector Location = GetActorLocation();
	FRotator Rotation = GetActorRotation();
	FActorSpawnParameters SpawnInfo;
	ADamageText* DamageText = GetWorld()->SpawnActor<ADamageText>(DamageTextActor,Location, Rotation, SpawnInfo);
	//ADamageText* DamageText = GetWorld()->SpawnActor<ADamageText>(Location, Rotation, SpawnInfo);
	DamageText->Initialize(Damage);
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

void AEnemyBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (DataAsset)
	{
		EnemyData = DataAsset->EnemyDatas[Name];
	}
}
