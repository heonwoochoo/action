// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyBase.h"
#include "Data/EnemyDataAsset.h"
#include "HUD/TargetWidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "portfolio/portfolioCharacter.h"
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
}

float AEnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	EnemyData.Hp -= DamageAmount;

	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController)
	{
		AHUDBase* HUDBase = Cast<AHUDBase>(CharacterController->GetHUD());
		if (HUDBase) HUDBase->ShowDamageOnScreen(this, DamageAmount);
	}
	
	EnemyData.Hp <= 0.f ? Die() : UpdateHPBar();

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

void AEnemyBase::Die()
{
	State = EEnemyState::EES_Dead;
	HPBarWidgetComponent->SetVisibility(false);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetLifeSpan(3.f);
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
	const float CurrentHP = GetEnemyData().Hp;
	const float MaxHP = GetEnemyData().MaxHp;
	HPBarWidgetComponent->SetHPBar(CurrentHP / MaxHP);
}

void AEnemyBase::SetHeadUpMark(AActor* NewMark)
{
	UE_LOG(LogTemp, Warning, TEXT("SetHeadUpMark"));
	HeadUpMark = NewMark;
}

void AEnemyBase::RemoveMark()
{
	UE_LOG(LogTemp, Warning, TEXT("Remove mark out"));
	if (HeadUpMark) HeadUpMark->Destroy();
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (DataAsset)
	{
		EnemyData = DataAsset->EnemyDatas[Name];
	}
}
