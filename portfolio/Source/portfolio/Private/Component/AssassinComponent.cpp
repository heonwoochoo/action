// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/AssassinComponent.h"
#include "Types/CharacterTypes.h"
#include "Enemy/EnemyBase.h"
#include "Animation/AnimInstanceBase.h"
#include "DefaultCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Component/CharacterMotionWarpingComponent.h"
#include "SkillActor/Assassin/KnifeProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Controller/CharacterController.h"
#include "HelperFunction.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Particles/ParticleSystem.h"
#include "SkillActor/Assassin/ThrowingSlash.h"
#include "Kismet/KismetMathLibrary.h"

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
		const FName& WarpName = "Assassin_SkillOne_Second";
		const FVector& TargetLocation = DashTarget->GetActorLocation();
		const FRotator& TargetRotation = UKismetMathLibrary::FindLookAtRotation(Character->GetActorLocation(), TargetLocation);

		//const FRotator Rotation = (DashTarget->GetActorLocation() - Character->GetActorLocation()).ToOrientationQuat().Rotator();
		Character->GetMotionWarpingComponent()->AddOrUpdateWarpTargetFromLocationAndRotation(WarpName, TargetLocation, TargetRotation);
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



void UAssassinComponent::SkillTwoFirstEffect()
{
	if (SkillTwo.NiagaraEffects.IsValidIndex(0))
	{
		UNiagaraSystem* SlashEmitter = SkillTwo.NiagaraEffects[0];

		const FVector& Location = Character->GetActorLocation();
		const FVector& NewLocation = FVector(Location.X, Location.Y, Location.Z - 100.f);

		const FRotator& Rotation = Character->GetActorRotation();

		// Emitter 생성
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, SlashEmitter, NewLocation, Rotation);

		// 충돌체 생성
		if (SkillTwo.SkillActorClasses.IsValidIndex(0))
		{
			const TSubclassOf<AActor>& SkillClass = SkillTwo.SkillActorClasses[0];

			AThrowingSlash* ThrowingSlash = GetWorld()->SpawnActor<AThrowingSlash>(SkillClass, Location, Rotation);
			if (ThrowingSlash)
			{
				ThrowingSlash->SetOwner(Character);
				ThrowingSlash->SetDamage(SkillTwo.Damage);
				ThrowingSlash->SetSlashType(ESlashType::EST_Single);

				if (SkillTwo.HitImpacts.IsValidIndex(0))
				{
					ThrowingSlash->SetHitImpactEmitter(SkillTwo.HitImpacts[0]);
				}
			}
		}
	}
}

void UAssassinComponent::SkillTwoEndEffect()
{
	if (SkillTwo.NiagaraEffects.IsValidIndex(1))
	{
		UNiagaraSystem* SlashEmitter = SkillTwo.NiagaraEffects[1];

		const FVector& Location = Character->GetActorLocation();
		const FRotator& Rotation = Character->GetActorRotation();

		// Emitter 생성
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, SlashEmitter, Location, Rotation);

		// 충돌체 생성
		if (SkillTwo.SkillActorClasses.IsValidIndex(0))
		{
			const TSubclassOf<AActor>& SkillClass = SkillTwo.SkillActorClasses[0];

			AThrowingSlash* ThrowingSlash = GetWorld()->SpawnActor<AThrowingSlash>(SkillClass, Location, Rotation);
			if (ThrowingSlash)
			{
				ThrowingSlash->SetOwner(Character);
				ThrowingSlash->SetDamage(SkillTwo.Damage);
				ThrowingSlash->SetSlashType(ESlashType::EST_Multi);

				if (SkillTwo.HitImpacts.IsValidIndex(1))
				{
					ThrowingSlash->SetHitImpactEmitter(SkillTwo.HitImpacts[1]);
				}
			}
		}
	}
}

void UAssassinComponent::HandleSkillThree()
{
	if (!bCanSkillThree) return;

	const float StaminaCost = SkillThree.Stamina;
	const float PlayerStamina = Character->GetCharacterStats().Stamina;

	if (StaminaCost <= PlayerStamina)
	{
		Character->UpdateStatManager(EStatTarget::EST_Stamina, EStatUpdateType::ESUT_Minus, SkillThree.Stamina);
		
		Super::HandleSkillThree();

		if (AnimInstance && SkillThree.Animation)
		{
			bCanSkillThree = false;
			AnimInstance->Montage_Play(SkillThree.Animation);
		}
	}
}

void UAssassinComponent::SpawnSkillThreeFirstEffect()
{
	if (SkillThree.NiagaraEffects.IsValidIndex(0))
	{
		UNiagaraSystem* SlashEmitter = SkillThree.NiagaraEffects[0];

		const FVector& Location = Character->GetActorLocation();
		const FRotator& Rotation = Character->GetActorRotation();

		// Emitter 생성
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, SlashEmitter, Location, Rotation);
	}
}

void UAssassinComponent::SpawnSkillThreeFinalEffect()
{
	if (SkillThree.NiagaraEffects.IsValidIndex(1))
	{
		UNiagaraSystem* SlashEmitter = SkillThree.NiagaraEffects[1];

		const FVector& Location = Character->GetActorLocation();
		const FRotator& Rotation = Character->GetActorRotation();
		const FRotator& NewRotation = FRotator(Rotation.Roll, Rotation.Yaw - 90.f, Rotation.Pitch);

		// Emitter 생성
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, SlashEmitter, Location, NewRotation);
	}
}

void UAssassinComponent::AttackAroundCharacter()
{
	if (Character)
	{
		const FVector Location = Character->GetActorLocation();
		Character->CheckEnemyInRange(Location, AttackAroundRadius, SkillThree.Damage, EHitType::EHT_Slash);
	}
}

void UAssassinComponent::AttackForwardCharacter()
{
	if (Character)
	{
		const FVector Location = Character->GetActorLocation() +  Character->GetActorForwardVector() * AttackForwardOffset;
		Character->CheckEnemyInRange(Location, AttackForwardRadius, SkillThree.Damage, EHitType::EHT_Slash);
	}
}

void UAssassinComponent::HandleSkillFour()
{
	if (!bCanSkillFour) return;

	const float StaminaCost = SkillFour.Stamina;
	const float PlayerStamina = Character->GetCharacterStats().Stamina;

	if (StaminaCost <= PlayerStamina)
	{
		Character->UpdateStatManager(EStatTarget::EST_Stamina, EStatUpdateType::ESUT_Minus, SkillFour.Stamina);
		
		Super::HandleSkillFour();

		if (AnimInstance && SkillFour.Animation)
		{
			bCanSkillFour = false;
			AnimInstance->Montage_Play(SkillFour.Animation);
		}
	}
}

void UAssassinComponent::SkillFourEffect()
{
	Character->LaunchCharacter(FVector(0.f, 0.f, 400.f), false, true);
	LaunchEnemy(400.f);
}

void UAssassinComponent::SkillFourEndEffect()
{
	Character->LaunchCharacter(FVector(0.f, 0.f, -5000.f), false, true);

	LaunchEnemy(-5000.f);

	Character->PlayCameraShake(CameraShakeExplosion);
}

void UAssassinComponent::ThrowKnife()
{
	if (KnifeClass && Character)
	{
		const FTransform Transform = Character->GetActorTransform();
		AKnifeProjectile* Knife = GetWorld()->SpawnActor<AKnifeProjectile>(KnifeClass, Transform);
		
		if (Knife)
		{
			Knife->SetOwner(Character);
			Knife->SetDamage(SkillTwo.Damage);
		}
		// 타겟이 있으면 타겟쪽으로, 없으면 캐릭터의 전방
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

void UAssassinComponent::LaunchEnemy(float ZScale)
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes = { UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn) };
	TArray<AActor*> ActorsToIgnore = { Character };
	TArray<AActor*> OutActors;
	const FVector Location = Character->GetActorLocation();
	UKismetSystemLibrary::SphereOverlapActors(this, Location, SkillFourRange, ObjectTypes, nullptr, ActorsToIgnore, OutActors);

	for (AActor* Actor : OutActors)
	{
		AEnemyBase* Enemy = Cast<AEnemyBase>(Actor);
		if (Enemy && Enemy->ActorHasTag(FName("Enemy")) && Enemy->GetState() != EEnemyState::EES_Dead)
		{
			Enemy->LaunchCharacter(FVector(0.f, 0.f, ZScale), false, true);
		}
	}
}

void UAssassinComponent::HandleSkillOne()
{
	const float StaminaCost = SkillOne.Stamina;
	const float PlayerStamina = Character->GetCharacterStats().Stamina;
	if (StaminaCost <= PlayerStamina)
	{
		Super::HandleSkillOne();
		Character->UpdateStatManager(EStatTarget::EST_Stamina, EStatUpdateType::ESUT_Minus, SkillOne.Stamina);
		
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
}

void UAssassinComponent::HandleSkillTwo()
{
	if (!bCanSkillTwo) return;
	const float StaminaCost = SkillTwo.Stamina;
	const float PlayerStamina = Character->GetCharacterStats().Stamina;
	if (StaminaCost <= PlayerStamina)
	{
		Character->UpdateStatManager(EStatTarget::EST_Stamina, EStatUpdateType::ESUT_Minus, SkillTwo.Stamina);
		
		Super::HandleSkillTwo();

		if (AnimInstance && SkillTwo.Animation)
		{
			bCanSkillTwo = false;
			AnimInstance->Montage_Play(SkillTwo.Animation);
		}
	}
}
