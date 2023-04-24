// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Potion.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"


APotion::APotion()
{
 	PrimaryActorTick.bCanEverTick = true;


}

void APotion::BeginPlay()
{
	Super::BeginPlay();

	
	Tags.Add(FName("Potion"));
}

void APotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}