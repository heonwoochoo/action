// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Potion.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DefaultCharacter.h"
#include "Curves/CurveFloat.h"
#include "Component/InventoryComponent.h"

APotion::APotion()
{
 	PrimaryActorTick.bCanEverTick = true;

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
	if (OtherActor->ActorHasTag(FName("Player")))
	{
		CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		if (PickupParticle)
		{
			const FTransform Transform{ GetTransform() };
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PickupParticle, Transform);
		}

		Character = OtherActor;

		GetWorld()->GetTimerManager().SetTimer(PickupTimerHandle, this, &APotion::EndPickupTimer, PickupScaleTime);
	}	
}

void APotion::Destroyed()
{
	UE_LOG(LogTemp, Warning, TEXT("Potion Destroyed!"));
}

void APotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PickupTimerHandle.IsValid())
	{
		if (PickupScaleCurve)
		{
			const float ElapsedTime = GetWorldTimerManager().GetTimerElapsed(PickupTimerHandle);
			const float ScaleValue = PickupScaleCurve->GetFloatValue(ElapsedTime);
			if (StaticMesh)
			{
				StaticMesh->SetWorldScale3D(FVector(ScaleValue));
			}
			if (ElapsedTime > 0.8f)
			{
				MoveToCharacter(DeltaTime);
			}
		}
	}
}

void APotion::EndPickupTimer()
{
	// 아이템이 필드에서 사라지면서 캐릭터가 아이템을 획득
	ADefaultCharacter* PlayerCharacter = Cast<ADefaultCharacter>(Character);
	if (PlayerCharacter)
	{
		UInventoryComponent* InventoryComponent = PlayerCharacter->GetInventoryComponent();
		if (InventoryComponent && PotionName != EItemName::EIN_None)
		{
			InventoryComponent->AddItemPotion(PotionName);
		}
	}
	Destroy();
}

void APotion::MoveToCharacter(float DeltaTime)
{
	const float X = FMath::FInterpTo(GetActorLocation().X, Character->GetActorLocation().X, DeltaTime, 50.f);
	const float Y = FMath::FInterpTo(GetActorLocation().Y, Character->GetActorLocation().Y, DeltaTime, 50.f);
	const float Z = FMath::FInterpTo(GetActorLocation().Z, Character->GetActorLocation().Z, DeltaTime, 50.f);
	const FVector NewLocation{ X, Y, Z };
	SetActorLocation(NewLocation);
}

