// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/DefaultWorldLevel.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/HUDBase.h"
#include "Enemy/EnemyBase.h"

ADefaultWorldLevel::ADefaultWorldLevel()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADefaultWorldLevel::BeginPlay()
{
	Super::BeginPlay();

	// ��ũ���� UI ǥ��
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		AHUDBase* HUDBase = Cast<AHUDBase>(PlayerController->GetHUD());
		if (HUDBase)
		{
			HUDBase->InitScreenOverlay();
		}
	}

	// ������ ���� �迭�� ���
	UGameplayStatics::GetAllActorsWithTag(this, FName("Respawn"), RespawnPoints);
	RespawnEnemy();
}

void ADefaultWorldLevel::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// ���� ���� �� ���ϰ� �Ǹ� �� ������
	if (CheckEnemyNumber() < EnemyMaxNumber && bRespawnFlag)
	{
		bRespawnFlag = false;
		GetWorld()->GetTimerManager().SetTimer(EnemyRespawnTimerHandle, this, &ADefaultWorldLevel::RespawnEnemy, 3.f, false);
	}
}

int32 ADefaultWorldLevel::CheckEnemyNumber()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithTag(this, FName("Enemy"), Actors);

	return Actors.Num();
}

void ADefaultWorldLevel::RespawnEnemy()
{
	if (RespawnPoints.Num() > 0 && Enemies.Num() > 0)
	{
		const int32 RandTargetPointNum = FMath::RandRange(0, RespawnPoints.Num() - 1);
		const FVector Location = RespawnPoints[RandTargetPointNum]->GetActorLocation();
		const FRotator Rotation = RespawnPoints[RandTargetPointNum]->GetActorRotation();

		const int32 RandEnemyNum = FMath::RandRange(0, Enemies.Num() - 1);

		GetWorld()->SpawnActor<AEnemyBase>(Enemies[RandEnemyNum], Location, Rotation);
	}
	bRespawnFlag = true;
}
