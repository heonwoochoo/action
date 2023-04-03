// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Potion.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

APotion::APotion()
{
 	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	if (CollisionComponent)
	{
		RootComponent = CollisionComponent;
		CollisionComponent->SetSphereRadius(100.f);
	}

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	if (StaticMesh)
	{
		StaticMesh->SetupAttachment(GetRootComponent());
	}

}

void APotion::BeginPlay()
{
	Super::BeginPlay();
	
	if (CollisionComponent)
	{
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APotion::BeginOverlap);
	}
}

void APotion::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PotionDataTable && PotionName != EItemName::EIN_None)
	{
		FName RowName;
		switch (PotionName)
		{
		case EItemName::EIN_HealthPotion:
			RowName = "HealthPotion";
			break;
		case EItemName::EIN_StaminaPotion:
			RowName = "StaminaPotion";
			break;
		}

		if (StaticMesh)
		{
			StaticMesh->SetStaticMesh(PotionDataTable->FindRow<FPotionInfo>(RowName, "")->Mesh);
		}	
	}
}

void APotion::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Begin overlap potion"));
}

// Called every frame
void APotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

