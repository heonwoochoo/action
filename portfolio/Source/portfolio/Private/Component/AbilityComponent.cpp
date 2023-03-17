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

// Sets default values for this component's properties
UAbilityComponent::UAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true; // Tick 사용시 true로 설정
	bWantsInitializeComponent = true;
	UE_LOG(LogTemp, Warning, TEXT("Constructor"));
	Character = Cast<AportfolioCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
}


// Called when the game starts
void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	PrimaryComponentTick.SetTickFunctionEnable(true);	// Tick 사용시 true로 설정
	PrimaryComponentTick.RegisterTickFunction(GetComponentLevel());
	Character = Cast<AportfolioCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("Begine play"));
		CharacterData = Character->GetCharacterDataAsset()->CharacterData;
	}

	// 데이터 에셋을 참조하여 스킬 애니메이션 포인터 초기화
	if (CharacterSkillAsset)
	{
		UE_LOG(LogTemp, Warning, TEXT("SKill asset reference"));
		SkillOneAnimation = CharacterSkillAsset->GetAnimation(CharacterData.Class, ESkillNumber::ESN_One);
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
	UE_LOG(LogTemp, Warning, TEXT("Assassin skill1 called"));
	if (AnimInstance && SkillOneAnimation)
	{
		UE_LOG(LogTemp, Warning, TEXT("Assassin skill1 called inside"));
		AnimInstance->Montage_Play(SkillOneAnimation);
		FName SectionName = "Assassin_Skill1_First";
		AnimInstance->Montage_JumpToSection(SectionName);

		// Target 설정
		TargetEnemy = FindEnemy();
		if (TargetEnemy)
		{
			DrawDebugSphere(GetWorld(), TargetEnemy->GetActorLocation(), 30.f, 16, FColor::Magenta, false, 5.f, 0U, 2.f);
			GEngine->AddOnScreenDebugMessage(4, 3, FColor::Cyan, FString::Printf(TEXT("Target Rotate Yaw: %f"), TargetEnemy->GetActorRotation().Yaw));
			GEngine->AddOnScreenDebugMessage(5, 3, FColor::Cyan, FString::Printf(TEXT("Character Rotate Yaw: %f"), Character->GetActorRotation().Yaw));
			GEngine->AddOnScreenDebugMessage(5, 3, FColor::Cyan, FString::Printf(TEXT("Oriented Rotator Yaw: %f"),(TargetEnemy->GetActorLocation() - Character->GetActorLocation()).ToOrientationRotator().Yaw));
			GEngine->AddOnScreenDebugMessage(5, 3, FColor::Cyan, FString::Printf(TEXT("Oriented quat z: %f"), (TargetEnemy->GetActorLocation() - Character->GetActorLocation()).ToOrientationQuat().Rotator().Yaw));
		}
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
		return OutHit.GetActor();
	}

	return nullptr;
}

void UAbilityComponent::ThrowKnife()
{
	if (KinfeProjectileClass)
	{
		const FTransform Transform = Character->GetActorTransform();
		KinfeProjectile = GetWorld()->SpawnActor<AKnifeProjectile>(KinfeProjectileClass, Transform);
	}
}

void UAbilityComponent::RotateCharacterBodyToTarget(AActor* Target)
{
	//MotionWarping
	if (Character)
	{
		const FName WarpName = "RotateToTarget";
		const FRotator TargetRotation = (Target->GetActorLocation() - Character->GetActorLocation()).ToOrientationQuat().Rotator();
		Character->GetMotionWarpingComponent()->AddOrUpdateWarpTargetFromLocationAndRotation(WarpName, Target->GetActorLocation(), TargetRotation);
		
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
	if (Character && Character->GetMotionWarpingComponent() && TargetEnemy)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tick Ability Comp"));
		RotateCharacterBodyToTarget(TargetEnemy);
	}
}

