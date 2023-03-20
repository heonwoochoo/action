

#include "Skill/Assassin_SkillOne.h"
#include "Kismet/GameplayStatics.h"
#include "portfolio/portfolioCharacter.h"
#include "Animation/AnimInstanceBase.h"
#include "Component/CharacterMotionWarpingComponent.h"
#include "Enemy/EnemyBase.h"
#include "Items/KnifeProjectile.h"
#include "Data/CharacterSkillAsset.h"

AAssassin_SkillOne::AAssassin_SkillOne()
{
 	PrimaryActorTick.bCanEverTick = false;

	Character = Cast<AportfolioCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Character)
	{
		AnimInstance = Cast<UAnimInstanceBase>(Character->GetMesh()->GetAnimInstance());
	}

	if (SkillAsset)
	{
		SkillData = SkillAsset->GetCharacterSkills().Find(ECharacterClass::ECC_Assassin)->CharacterSkill[ESkillNumber::ESN_One];
	}


}

void AAssassin_SkillOne::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (SkillAsset)
	{
		SkillData = SkillAsset->GetCharacterSkills().Find(ECharacterClass::ECC_Assassin)->CharacterSkill[ESkillNumber::ESN_One];
	}
}

void AAssassin_SkillOne::ThrowKnife()
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

void AAssassin_SkillOne::PlayAction()
{
	if (AnimInstance && SkillData.Animation)
	{
		FName SectionName;

		if (DashTarget)
		{
			AEnemyBase* Enemy = Cast<AEnemyBase>(DashTarget);
			if (Enemy)
			{
				Enemy->RemoveMark();
				UE_LOG(LogTemp, Warning, TEXT("Enemy Cast OK"));
			}
			SecondAction();
			SectionName = "Assassin_Skill1_Second";
			DashTarget = nullptr;
		}
		else
		{
			FirstAction();
			SectionName = "Assassin_Skill1_First";
		}
		AnimInstance->Montage_Play(SkillData.Animation);
		AnimInstance->Montage_JumpToSection(SectionName);
	}
}

AActor* AAssassin_SkillOne::FindEnemy()
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

void AAssassin_SkillOne::FirstAction()
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

void AAssassin_SkillOne::SecondAction()
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

void AAssassin_SkillOne::RotateToTarget(AActor* Target)
{
	//MotionWarping
	if (Character && Target->ActorHasTag(FName("Enemy")))
	{
		const FName WarpName = "Assassin_SkillOne_First";
		const float TargetRotationYaw = (Target->GetActorLocation() - Character->GetActorLocation()).ToOrientationQuat().Rotator().Yaw;
		Character->GetMotionWarpingComponent()->AddOrUpdateWarpTargetFromLocationAndRotation(WarpName, Target->GetActorLocation(), FRotator{ 0.f,TargetRotationYaw,0.f });
	}
}