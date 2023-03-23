// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/AssassinComponent.h"
#include "CharacterTypes.h"
#include "Enemy/EnemyBase.h"
#include "Animation/AnimInstanceBase.h"
#include "portfolio/portfolioCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Component/CharacterMotionWarpingComponent.h"
#include "Items/KnifeProjectile.h"

void UAssassinComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

}

void UAssassinComponent::BeginPlay()
{
	Super::BeginPlay();

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
	* �������� ���� �� Ÿ���� �ִ��� Ȯ���մϴ�.
	* Ÿ���� �ִٸ�, ĳ������ �����̼�(Z Axis)�� �ش� Ÿ������ �����մϴ�.
	* ������ ������ Ÿ����, ������ ĳ������ Forward�� ���մϴ�.
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
		}
		else
		{
			SkillOne_First();
			SectionName = SectionName_First;
		}
		AnimInstance->Montage_Play(SkillOne.Animation);
		AnimInstance->Montage_JumpToSection(SectionName);
	}
}