// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillActor/Assassin/ArrowSpline.h"
#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DefaultCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Enemy/EnemyBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"

AArrowSpline::AArrowSpline()
{
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	SetRootComponent(SplineComponent);
	SplineComponent->SetSplinePointType(0, ESplinePointType::Linear);
	SplineComponent->SetSplinePointType(1, ESplinePointType::Linear);
}


void AArrowSpline::BeginPlay()
{
	Super::BeginPlay();
	

}

void AArrowSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Caster && Target && SplineComponent)
	{
		SplineComponent->SetWorldLocationAtSplinePoint(0, Caster->GetMesh()->GetComponentLocation());
		
		AEnemyBase* Enemy = Cast<AEnemyBase>(Target);
		if (Enemy)
		{
			SplineComponent->SetWorldLocationAtSplinePoint(1, Enemy->GetMesh()->GetComponentLocation());
		}		

		UpdateArrows();
		UpdateTargetCircle();
	}
}

void AArrowSpline::Destroyed()
{
	for (auto Arrow : Arrows)
	{
		Arrow->Destroy();
	}
	if (TargetCircle)
	{
		TargetCircle->Destroy();
	}
}

void AArrowSpline::Init(ADefaultCharacter* InCaster, AActor* InTarget)
{
	Caster = InCaster;
	Target = InTarget;

	DrawArrows();
	DrawTargetCircle();
}

void AArrowSpline::DrawArrows()
{
	if (Caster && Target && SplineComponent)
	{
		const float& Distance = (Target->GetActorLocation() - Caster->GetActorLocation()).Length();

		int32 ArrowNum = (int32)(Distance / 100.f);

		for (int32 i = 1; i <= ArrowNum; ++i)
		{
			AActor* Arrow = GetWorld()->SpawnActor<AActor>(ArrowClass);
			Arrows.Add(Arrow);
		}
	}
}

void AArrowSpline::DrawTargetCircle()
{
	if (Caster && Target && TargetCircleClass)
	{

		TargetCircle = GetWorld()->SpawnActor<AActor>(TargetCircleClass);
		FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, false);
		TargetCircle->AttachToActor(Target,Rules);
		TargetCircle->SetActorScale3D(FVector(0.7f));
	}
}



void AArrowSpline::UpdateArrows()
{
	const float& Distance = (Target->GetActorLocation() - Caster->GetActorLocation()).Length();

	const float& Offset = Distance / Arrows.Num();
	
	for (int32 i = 0; i < Arrows.Num(); ++i)
	{
		const FVector& Location = SplineComponent->GetLocationAtDistanceAlongSpline(Offset * (i+1), ESplineCoordinateSpace::World);
		const FRotator& Rotation = SplineComponent->GetRotationAtDistanceAlongSpline(Offset * (i+1), ESplineCoordinateSpace::World);
	
		if (Arrows.IsValidIndex(i))
		{
			Arrows[i]->SetActorRotation(Rotation);
			Arrows[i]->SetActorLocation(Location);
		}
	}
}

void AArrowSpline::UpdateTargetCircle()
{
	if (Caster && Target && TargetCircle)
	{
		UCameraComponent* CasterCamera = Caster->GetFollowCamera();
		const FVector& CameraLocation = CasterCamera->GetComponentLocation();

		const FRotator& Rotation = UKismetMathLibrary::FindLookAtRotation(Target->GetActorLocation(), CameraLocation);
		TargetCircle->SetActorRotation(Rotation);
	}
}
