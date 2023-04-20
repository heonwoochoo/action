// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	if (CollisionComponent)
	{
		RootComponent = CollisionComponent;
	}

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	if (StaticMesh)
	{
		StaticMesh->SetupAttachment(GetRootComponent());
	}
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FName("Item"));
}

void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

