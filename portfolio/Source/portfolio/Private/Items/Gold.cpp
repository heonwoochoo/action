// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Gold.h"
#include "Particles/ParticleSystemComponent.h"
#include "DefaultCharacter.h"

// Sets default values
AGold::AGold()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(StaticMeshComponent);
	
	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComponent"));
	ParticleComponent->SetupAttachment(StaticMeshComponent);

	Tags.Add(FName(TEXT("Gold")));
}

// Called when the game starts or when spawned
void AGold::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void AGold::Destroyed()
{
	Super::Destroyed();

	ParticleComponent->DestroyComponent();
}

