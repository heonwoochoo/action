// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyBase.h"
#include "Data/EnemyDataAsset.h"
#include "HUD/TargetWidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "portfolio/portfolioCharacter.h"
#include "Component/AbilityComponent.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = false;

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

	
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	GetMesh()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnBeginOverlapped);
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
	}
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

