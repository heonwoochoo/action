// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/NPCBase.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/DataTable.h"
#include "DefaultCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"

ANPCBase::ANPCBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(GetRootComponent());
	SphereComponent->SetGenerateOverlapEvents(true);

	NameTextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("NameTextComponent"));
	NameTextComponent->SetupAttachment(GetRootComponent());
	NameTextComponent->SetVisibility(false);
}

void ANPCBase::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ANPCBase::BeginOverlappedSphere);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ANPCBase::EndOverlappedSphere);
}

void ANPCBase::BeginOverlappedSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName(TEXT("Player"))))
	{
		bIsNearPlayer = true;
		ChangeMeshOutline();

		if (NameTextComponent)
		{
			NameTextComponent->SetVisibility(true);
			SetName();

			ADefaultCharacter* PlayerCharacter = Cast<ADefaultCharacter>(OtherActor);
			if (PlayerCharacter)
			{
				NearPlayer = PlayerCharacter;
			}
		}
	}
}

void ANPCBase::EndOverlappedSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag(FName(TEXT("Player"))))
	{
		bIsNearPlayer = false;
		RemoveMeshOutline();

		if (NameTextComponent)
		{
			NameTextComponent->SetVisibility(false);
			NearPlayer = nullptr;
		}
	}
}

void ANPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (NearPlayer)
	{
		RotateNameToPlayer(NearPlayer);
	}
}

void ANPCBase::ChangeMeshOutline()
{
	// 월드에 배치된 포스트 프로세싱에 영향을 받음
	USkeletalMeshComponent* MeshComponent = GetMesh();
	if (MeshComponent)
	{
		MeshComponent->SetRenderCustomDepth(true);
		MeshComponent->SetCustomDepthStencilValue(0);
	}
}

void ANPCBase::RemoveMeshOutline()
{
	USkeletalMeshComponent* MeshComponent = GetMesh();
	if (MeshComponent)
	{
		MeshComponent->SetRenderCustomDepth(false);
	}
}

void ANPCBase::SetName()
{
	if (NameTextComponent && !Name.IsEmpty())
	{
		NameTextComponent->SetText(Name);
	}
}

void ANPCBase::RotateNameToPlayer(ADefaultCharacter* InPlayer)
{
	if (NameTextComponent && InPlayer)
	{
		// 위치는 에디터 내에서 조정

		// 방향 설정
		const FVector& Start = NameTextComponent->GetComponentLocation();

		UCameraComponent* PlayerCamera = InPlayer->GetFollowCamera();
		check(PlayerCamera);
		const FVector& Target = PlayerCamera->GetComponentLocation();

		const FRotator& LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start, Target);
		NameTextComponent->SetWorldRotation(LookAtRotation);
	}
}