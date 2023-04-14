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

void ADefaultGameMode::PlayChangeButtonClickSound()
{
	if (ChangeButtonClickSound)
	{
		UGameplayStatics::PlaySound2D(this, ChangeButtonClickSound);
	}
}

void ADefaultGameMode::PlayCheckButtonClickSound()
{
	if (CheckButtonClickSound)
	{
		UGameplayStatics::PlaySound2D(this, CheckButtonClickSound);
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