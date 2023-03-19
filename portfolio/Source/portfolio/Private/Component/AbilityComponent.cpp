// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/AbilityComponent.h"
#include "Data/CharacterDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "portfolio/portfolioCharacter.h"
#include "Data/CharacterSkillAsset.h"
#include "Animation/AnimInstanceBase.h"
#include "Items/KnifeProjectile.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "Component/CharacterMotionWarpingComponent.h"
#include "Enemy/EnemyBase.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values for this component's properties
UAbilityComponent::UAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = false; // Tick 사용시 true로 설정
	bWantsInitializeComponent = true;
	UE_LOG(LogTemp, Warning, TEXT("Constructor"));
	Character = Cast<AportfolioCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
}


// Called when the game starts
void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	PrimaryComponentTick.SetTickFunctionEnable(false);	// Tick 사용시 true로 설정
	PrimaryComponentTick.RegisterTickFunction(GetComponentLevel());
	Character = Cast<AportfolioCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("Begine play"));
		CharacterData = Character->GetCharacterDataAsset()->CharacterData;
	}

	if (Character && Character->GetMesh())
	{
		UE_LOG(LogTemp, Warning, TEXT("AnimInstance reference"));
		AnimInstance = Cast<UAnimInstanceBase>(Character->GetMesh()->GetAnimInstance());
	}
}

void UAbilityComponent::InitializeComponent()
{
	Super::InitializeComponent();
	UE_LOG(LogTemp, Warning, TEXT("InitializeComponent"));

}

const FCharacterData UAbilityComponent::GetCharacterData()
{
	return CharacterData;
}

void UAbilityComponent::HandleSkillOne()
{
	switch (CharacterData.Class)
	{
	case ECharacterClass::ECC_Assassin:
		HandleAssassinSkillOne();
		break;
	}
}

void UAbilityComponent::HandleSkillTwo()
{
}

void UAbilityComponent::HandleSkillThree()
{
}

void UAbilityComponent::HandleSkillFour()
{
}


void UAbilityComponent::HandleAssassinSkillOne()
{
	if (AnimInstance && AnimInstance->GetSkillOne())
	{
		FName SectionName;

		if (DashTarget)
		{
			HandleAssassinSkillOneSecond();
			SectionName = "Assassin_Skill1_Second";
			DashTarget = nullptr;
		}
		else
		{
			HandleAssassinSkillOneFirst();
			SectionName = "Assassin_Skill1_First";
		}
		AnimInstance->Montage_Play(AnimInstance->GetSkillOne());
		AnimInstance->Montage_JumpToSection(SectionName);
	}
}

void UAbilityComponent::HandleAssassinSkillOneFirst()
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

void UAbilityComponent::HandleAssassinSkillOneSecond()
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



AActor* UAbilityComponent::FindEnemy()
{
	const FVector StartLocation = Character->GetActorLocation() + Character->GetActorForwardVector() * 150.f;
	const FVector EndLocation = StartLocation + Character->GetActorForwardVector() * TraceDistance;
	const TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes{ UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn)};
	const TArray<AActor*> ActorsToIgnore{ Character };
	FHitResult OutHit;
	UKismetSystemLibrary::SphereTraceSingleForObjects(this, StartLocation, EndLocation, 300.f, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, OutHit, true);

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

void UAbilityComponent::ResetTarget()
{
	if (TargetEnemy)
	{
	}
}

void UAbilityComponent::SetDashTarget(AActor* Target)
{
	DashTarget = Target;
}

void UAbilityComponent::ThrowKnife()
{
	if (KinfeProjectileClass && Character)
	{
		const FTransform Transform = Character->GetActorTransform();
		KinfeProjectile = GetWorld()->SpawnActor<AKnifeProjectile>(KinfeProjectileClass, Transform);
		KinfeProjectile->Caster = Character;
		if (TargetEnemy)
		{
			const FVector Direction = TargetEnemy->GetActorLocation() - Character->GetActorLocation();
			KinfeProjectile->SetMovementDirection(Direction.GetSafeNormal());
		}
		else
		{
			const FVector Direction = Character->GetActorForwardVector();
			KinfeProjectile->SetMovementDirection(Direction);
		}
	}
}

void UAbilityComponent::RotateToTarget(AActor* Target)
{
	//MotionWarping
	if (Character && Target->ActorHasTag(FName("Enemy")))
	{
		const FName WarpName = "Assassin_SkillOne_First";
		const float TargetRotationYaw = (Target->GetActorLocation() - Character->GetActorLocation()).ToOrientationQuat().Rotator().Yaw;
		Character->GetMotionWarpingComponent()->AddOrUpdateWarpTargetFromLocationAndRotation(WarpName, Target->GetActorLocation(), FRotator{0.f,TargetRotationYaw,0.f});
	}
}

void UAbilityComponent::HandleAssassinSkillTwo()
{
}

void UAbilityComponent::HandleAssassinSkillThree()
{
}

void UAbilityComponent::HandleAssassinSkillFour()
{
}

// Called every frame
void UAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

