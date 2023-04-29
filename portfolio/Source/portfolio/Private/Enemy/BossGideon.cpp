// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BossGideon.h"

ABossGideon::ABossGideon()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABossGideon::BeginPlay()
{
	Super::BeginPlay();
}

void ABossGideon::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void ABossGideon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
