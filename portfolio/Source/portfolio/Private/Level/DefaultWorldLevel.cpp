// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/DefaultWorldLevel.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/HUDBase.h"
#include "Enemy/EnemyBase.h"
#include "Controller/CharacterController.h"
#include "Enemy/Boss/Gideon/BossGideon.h"


ADefaultWorldLevel::ADefaultWorldLevel()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADefaultWorldLevel::BeginPlay()
{
	Super::BeginPlay();

	
    ACharacterController* PlayerController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerController)
	{
		
		AHUDBase* HUDBase = Cast<AHUDBase>(PlayerController->GetHUD());
		if (HUDBase)
		{
			// 스크린에 기본 UI 표시
			HUDBase->InitScreenOverlay();

			// 최초 지점 이름 표시
			const FText& StartSpotName = FText::FromString(TEXT("태초마을"));
			HUDBase->ShowSpotName(StartSpotName);			
		}

		// 배경음 재생
		PlayerController->PlayBackgroundMusic(EBackgroundMusic::EBM_OutsideCastle);
	}

	// 리스폰 지점 배열에 담기
	UGameplayStatics::GetAllActorsWithTag(this, FName("Respawn"), RespawnPoints);
	RespawnEnemy();

	// 보스의 스폰 지점 저장
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsWithTag(this, FName(TEXT("BossSpawnPoint")), OutActors);
	if (OutActors.IsValidIndex(0))
	{
		BossSpawnPoint = OutActors[0];
	}
}

void ADefaultWorldLevel::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// 일정 마리 수 이하가 되면 적 리스폰
	if (CheckEnemyNumber() < EnemyMaxNumber && bRespawnFlag && !bIsBossSpawn)
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

void ADefaultWorldLevel::SpawnBoss()
{
	if (BossSpawnPoint && BossClass)
	{
		const FVector& Location = BossSpawnPoint->GetActorLocation();
		const FRotator& Rotation = BossSpawnPoint->GetActorRotation();

		SpawnedBoss = GetWorld()->SpawnActor<ABossGideon>(BossClass, Location, Rotation);
	}
}

void ADefaultWorldLevel::RemoveAllEnemies()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsWithTag(this, FName(TEXT("Enemy")), OutActors);

	for (int32 i = 0; i < OutActors.Num(); ++i)
	{
		OutActors[i]->Destroy();
		UE_LOG(LogTemp, Warning, TEXT("잔몹이 제거되었습니다."));
	}

	if (EnemyRespawnTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(EnemyRespawnTimerHandle);
	}

	bRespawnFlag = false;
}
