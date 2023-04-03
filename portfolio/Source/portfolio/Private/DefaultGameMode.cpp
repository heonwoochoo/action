// Copyright Epic Games, Inc. All Rights Reserved.

#include "DefaultGameMode.h"
#include "DefaultCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy/EnemyBase.h"

ADefaultGameMode::ADefaultGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
	PrimaryActorTick.bCanEverTick = true;
}

int32 ADefaultGameMode::CheckEnemyNumber()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithTag(this, FName("Enemy"), Actors);

	return Actors.Num();
}

void ADefaultGameMode::RespawnEnemy()
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

void ADefaultGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsWithTag(this, FName("Respawn"), RespawnPoints);
	RespawnEnemy();
}

void ADefaultGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CheckEnemyNumber() < EnemyMaxNumber && bRespawnFlag)
	{
		bRespawnFlag = false;
		GetWorld()->GetTimerManager().SetTimer(EnemyRespawnTimerHandle, this, &ADefaultGameMode::RespawnEnemy, 3.f, false);
	}
}