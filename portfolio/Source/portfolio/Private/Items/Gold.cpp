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
	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AGold::OnBeginOverlapped);

	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComponent"));
	ParticleComponent->SetupAttachment(StaticMeshComponent);

	Tags.Add(FName(TEXT("Gold")));
}

// Called when the game starts or when spawned
void AGold::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void AGold::OnBeginOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName(TEXT("Player"))))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player overlapped!"));
	}
}