// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/AssassinComponent.h"
#include "CharacterTypes.h"
#include "Enemy/EnemyBase.h"
#include "Animation/AnimInstanceBase.h"
#include "portfolio/portfolioCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Component/CharacterMotionWarpingComponent.h"
#include "Items/KnifeProjectile.h"

UAssassinComponent::UAssassinComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAssassinComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

}

void UAssassinComponent::BeginPlay()
{
	Super::BeginPlay();
	PrimaryComponentTick.SetTickFunctionEnable(true);
	PrimaryComponentTick.RegisterTickFunction(GetComponentLevel());

}

void UAssassinComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (bCheckSkillTwoDashOverlap)
	{
		SkillTwoDashOverlap();
	}

}

void UAssassinComponent::SetCheckSkillTwoDashOverlap(bool CanOverlap)
{
	bCheckSkillTwoDashOverlap = CanOverlap;
}

AActor* UAssassinComponent::FindEnemy()
{
	const FVector StartLocation = Character->GetActorLocation() + Character->GetActorForwardVector() * 150.f;
	const FVector EndLocation = StartLocation + Character->GetActorForwardVector() * TraceDistance;
	const TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes{ UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn) };
	const TArray<AActor*> ActorsToIgnore{ Character };
	FHitResult OutHit;
	UKismetSystemLibrary::SphereTraceSingleForObjects(this, StartLocation, EndLocation, AutoDirectionRange, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, OutHit, true);

	if (OutHit.bBlockingHit)
	{
		AEnemyBase* Enemy = Cast<AEnemyBase>(OutHit.GetActor());
		if (Enemy)
		{
			if (Enemy->ActorHasTag(FName("Enemy"))) return OutHit.GetActor();
		}
	}
	return nullptr;
}

void UAssassinComponent::SkillOne_First()
{
	/**
	* 수리검을 던질 때 타겟이 있는지 확인합니다.
	* 타겟이 있다면, 캐릭터의 로테이션(Z Axis)을 해당 타겟으로 워핑합니다.
	* 수리검 방향은 타겟을, 없으면 캐릭터의 Forward를 향합니다.
	*/
	TargetEnemy = FindEnemy();
	if (TargetEnemy)
	{
		RotateToTarget(TargetEnemy);
		DrawDebugSphere(GetWorld(), TargetEnemy->GetActorLocation(), 30.f, 16, FColor::Magenta, false, 5.f, 0U, 2.f);
	}
	else
	{
		Character->GetMotionWarpingComponent()->RemoveWarpTarget(FName("Assassin_SkillOne_First"));
	}
}

void UAssassinComponent::SkillOne_Second()
{
	//MotionWarping
	if (Character && DashTarget->ActorHasTag(FName("Enemy")))
	{
		const FName WarpName = "Assassin_SkillOne_Second";
		const FVector Location = DashTarget->GetActorLocation();
		const FRotator Rotation = (DashTarget->GetActorLocation() - Character->GetActorLocation()).ToOrientationQuat().Rotator();
		Character->GetMotionWarpingComponent()->AddOrUpdateWarpTargetFromLocationAndRotation(WarpName, Location, Rotation);
	}
}

void UAssassinComponent::RotateToTarget(AActor* Target)
{
	//MotionWarping
	if (Character && Target->ActorHasTag(FName("Enemy")))
	{
		const FName WarpName = "Assassin_SkillOne_First";
		const float TargetRotationYaw = (Target->GetActorLocation() - Character->GetActorLocation()).ToOrientationQuat().Rotator().Yaw;
		Character->GetMotionWarpingComponent()->AddOrUpdateWarpTargetFromLocationAndRotation(WarpName, Target->GetActorLocation(), FRotator{ 0.f,TargetRotationYaw,0.f });
	}
}

void UAssassinComponent::SkillTwoDashOverlap()
{
	const TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes{ UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn) };
	const TArray<AActor*> ActorsToIgnore{ Character };
	TArray<AActor*> OutActors;
	UKismetSystemLibrary::SphereOverlapActors(this, Character->GetActorLocation(), 200.f, ObjectTypes, nullptr, ActorsToIgnore, OutActors);
	DrawDebugSphere(GetWorld(), Character->GetActorLocation(), 200.f, 16, FColor::Orange, false, 0.5f);
}

void UAssassinComponent::ThrowKnife()
{
	if (KnifeClass && Character)
	{
		const FTransform Transform = Character->GetActorTransform();
		Knife = GetWorld()->SpawnActor<AKnifeProjectile>(KnifeClass, Transform);
		Knife->Caster = Character;
		if (TargetEnemy)
		{
			const FVector Direction = TargetEnemy->GetActorLocation() - Character->GetActorLocation();
			Knife->SetMovementDirection(Direction.GetSafeNormal());
		}
		else
		{
			const FVector Direction = Character->GetActorForwardVector();
			Knife->SetMovementDirection(Direction);
		}
	}
}

void UAssassinComponent::SetDashTarget(AActor* Target)
{
	DashTarget = Target;
}

void UAssassinComponent::HandleSkillOne()
{
	Super::HandleSkillOne();

	if (AnimInstance && SkillOne.Animation)
	{
		FName SectionName;

		if (DashTarget)
		{
			AEnemyBase* Enemy = Cast<AEnemyBase>(DashTarget);
			if (Enemy)
			{
				Enemy->RemoveMark();
			}
			SkillOne_Second();
			SectionName = SectionName_Second;
			DashTarget = nullptr;
			SetSkillOneTimer();
		}
		else
		{
			if (!bCanSkillOne) return;
			bCanSkillOne = false;
			SkillOne_First();

			SectionName = SectionName_First;
		}
		AnimInstance->Montage_Play(SkillOne.Animation);
		AnimInstance->Montage_JumpToSection(SectionName);
	}
}

void UAssassinComponent::HandleSkillTwo()
{
	Super::HandleSkillTwo();

	if (AnimInstance && SkillTwo.Animation)
	{
		if (!bCanSkillTwo) return;
		bCanSkillTwo = false;
		AnimInstance->Montage_Play(SkillTwo.Animation);

		const FName WarpName = "AssassinSkillTwo";
		const FVector Location = Character->GetActorLocation() + Character->GetActorForwardVector() * SkillTwoDashDistance;
		Character->GetMotionWarpingComponent()->AddOrUpdateWarpTargetFromLocation(WarpName, Location);
	}
}
