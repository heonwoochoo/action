// Copyright Epic Games, Inc. All Rights Reserved.

#include "DefaultGameMode.h"
#include "DefaultCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy/EnemyBase.h"
#include "Sound/SoundCue.h"

ADefaultGameMode::ADefaultGameMode()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADefaultGameMode::PlayClickSound1()
{
	if (ClickSound1)
	{
		UGameplayStatics::PlaySound2D(this, ClickSound1);
	}
}

void ADefaultGameMode::PlayClickSound2()
{
	if (ClickSound2)
	{
		UGameplayStatics::PlaySound2D(this, ClickSound2);
	}
}

void ADefaultGameMode::BeginPlay()
{
	Super::BeginPlay();

}

void ADefaultGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}