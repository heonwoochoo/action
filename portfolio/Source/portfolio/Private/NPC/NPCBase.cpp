// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/NPCBase.h"
#include "Components/SphereComponent.h"
#include "Engine/DataTable.h"

ANPCBase::ANPCBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(GetRootComponent());
	SphereComponent->SetGenerateOverlapEvents(true);
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
	}
}

void ANPCBase::EndOverlappedSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag(FName(TEXT("Player"))))
	{
		bIsNearPlayer = false;
		RemoveMeshOutline();
	}
}

void ANPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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