// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "DefaultCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Curves/CurveFloat.h"
#include "Component/InventoryComponent.h"

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

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	if (SkeletalMesh)
	{
		SkeletalMesh->SetupAttachment(GetRootComponent());
	}
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	if (CollisionComponent)
	{
		CollisionComponent->SetSphereRadius(100.f);
	}

	Tags.Add(FName("Item"));
}

void AItemBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (Code.IsValid() && ItemSpecData)
	{
		Spec = *ItemSpecData->FindRow<FItemSpec>(Code, "");

		if (StaticMesh && Spec.StaticMesh)
		{
			UStaticMesh* Mesh = Spec.StaticMesh;
			StaticMesh->SetStaticMesh(Mesh);
		}

		if (SkeletalMesh && Spec.SkeletalMesh)
		{
			USkeletalMesh* Mesh = Spec.SkeletalMesh;
			SkeletalMesh->SetSkeletalMesh(Mesh);
		}
	}
}

void AItemBase::Tick(float DeltaTime)
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
			if (SkeletalMesh)
			{
				SkeletalMesh->SetWorldScale3D(FVector(ScaleValue));
			}
			if (ElapsedTime > 0.8f)
			{
				MoveToCharacter(DeltaTime);
			}
		}
	}
}

void AItemBase::EndPickupTimer()
{
	// 아이템이 필드에서 사라지면서 캐릭터가 아이템을 획득
	ADefaultCharacter* PlayerCharacter = Cast<ADefaultCharacter>(Character);
	if (PlayerCharacter)
	{
		UInventoryComponent* InventoryComponent = PlayerCharacter->GetInventoryComponent();
		if (InventoryComponent)
		{
			InventoryComponent->AddItem(Code);
		}
	}

	Destroy();
}

void AItemBase::MoveToCharacter(float DeltaTime)
{
	const float X = FMath::FInterpTo(GetActorLocation().X, Character->GetActorLocation().X, DeltaTime, 50.f);
	const float Y = FMath::FInterpTo(GetActorLocation().Y, Character->GetActorLocation().Y, DeltaTime, 50.f);
	const float Z = FMath::FInterpTo(GetActorLocation().Z, Character->GetActorLocation().Z, DeltaTime, 50.f);
	const FVector NewLocation{ X, Y, Z };
	SetActorLocation(NewLocation);
}



void AItemBase::HandlePickupItem(AActor* PickupCharacter)
{
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (PickupParticle)
	{
		const FTransform Transform{ GetTransform() };
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PickupParticle, Transform);
	}

	Character = PickupCharacter;

	GetWorld()->GetTimerManager().SetTimer(PickupTimerHandle, this, &AItemBase::EndPickupTimer, PickupScaleTime);
}

