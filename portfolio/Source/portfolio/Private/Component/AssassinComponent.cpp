// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/AssassinComponent.h"
#include "Types/CharacterTypes.h"
#include "Enemy/EnemyBase.h"
#include "Animation/AnimInstanceBase.h"
#include "DefaultCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Component/CharacterMotionWarpingComponent.h"
#include "Items/KnifeProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Controller/CharacterController.h"
#include "HelperFunction.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Particles/ParticleSystem.h"
#include "SkillActor/Assassin/ThrowingSlash.h"

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

	InitSkillThreeEffectRotationValues();
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



void UAssassinComponent::SkillTwoFirstEffect()
{
	if (SkillTwo.NiagaraEffects.IsValidIndex(0))
	{
		UNiagaraSystem* SlashEmitter = SkillTwo.NiagaraEffects[0];

		const FVector& Location = Character->GetActorLocation();
		const FVector& NewLocation = FVector(Location.X, Location.Y, Location.Z - 100.f);

		const FRotator& Rotation = Character->GetActorRotation();
		//const FRotator& NewRotation = FRotator(Rotation.Roll, Rotation.Yaw - 90.f, Rotation.Pitch + 180.f);

		// Emitter 생성
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, SlashEmitter, NewLocation, Rotation);

		// 충돌체 생성
		if (SkillTwo.SkillActorClasses.IsValidIndex(0))
		{
			const TSubclassOf<AActor>& SkillClass = SkillTwo.SkillActorClasses[0];

			AThrowingSlash* ThrowingSlash = GetWorld()->SpawnActor<AThrowingSlash>(SkillClass, NewLocation, Rotation);
			if (ThrowingSlash)
			{
				ThrowingSlash->SetOwner(Character);
				ThrowingSlash->SetDamage(SkillTwo.Damage);

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
	if (Character)
	{
		Character->PlayCameraShake(CameraShakeExplosion);
	}

	if (SkillTwo.NiagaraEffects.IsValidIndex(0))
	{
		UNiagaraSystem* Effect = SkillTwo.NiagaraEffects[0];
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, Effect, Character->GetActorLocation(), Character->GetActorRotation());
	}

	const TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes{ UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn) };
	const TArray<AActor*> ActorsToIgnore{ Character };
	TArray<AActor*> OutActors;
	UKismetSystemLibrary::SphereOverlapActors(this, Character->GetActorLocation(), 400.f, ObjectTypes, nullptr, ActorsToIgnore, OutActors);
	DrawDebugSphere(GetWorld(), Character->GetActorLocation(), 400.f, 16, FColor::Blue, false, 1.f);
	for (auto Actor : OutActors)
	{
		if (Actor->ActorHasTag(FName("Enemy")))
		{
			AEnemyBase* Enemy = Cast<AEnemyBase>(Actor);
			if (Enemy)
			{
				// 적중 시 에어본
				Enemy->LaunchCharacter(FVector(0.f, 0.f, 500.f), false, true);
				Character->DamageToEnemy(Enemy, SkillTwo.Damage);
				SpawnHitParticle(EHitType::EHT_Default, Enemy->GetActorLocation(), Enemy->GetActorRotation());
				PlayHitSound(EHitType::EHT_Default, Enemy->GetActorLocation());
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

void UAssassinComponent::SpawnSkillThreeEffect()
{
	if (Character && SkillThree.ParticleEffects.IsValidIndex(0))
	{	
		// 1. 로테이션 조정
		AdjustCompRotationByCombo(SkillThreeCombo);

		// 2. 파티클 생성
		UParticleSystem* Effect = SkillThree.ParticleEffects[0];
		SpawnParticleEffect(Effect);

		// 3. 범위 내 적 타격
		const FVector Location = Character->GetEmitterComponent()->GetComponentLocation();
		Character->CheckEnemyInRange(Location, 200.f, SkillThree.Damage, EHitType::EHT_Slash);

		// 4. 콤보 증가
		SkillThreeCombo++;
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

void UAssassinComponent::InitSkillThreeEffectRotationValues()
{
	SkillThreeEffectRotationValues.Add(90.f);
	SkillThreeEffectRotationValues.Add(-75.f);
	SkillThreeEffectRotationValues.Add(75.f);
	SkillThreeEffectRotationValues.Add(-90.f);
	SkillThreeEffectRotationValues.Add(120.f);
	SkillThreeEffectRotationValues.Add(-90.f);
	SkillThreeEffectRotationValues.Add(90.f);
	SkillThreeEffectRotationValues.Add(-90.f);
}

void UAssassinComponent::InitSkillThreeComboCount()
{
	SkillThreeCombo = 0;
}

void UAssassinComponent::AdjustCompRotationByCombo(uint8 ComboCount)
{
	USceneComponent* EmitterComponent = Character->GetEmitterComponent();
	if (EmitterComponent && SkillThreeEffectRotationValues.IsValidIndex(ComboCount))
	{
		float RollValue = SkillThreeEffectRotationValues[ComboCount];
		EmitterComponent->SetRelativeRotation(FRotator(0.f,0.f, RollValue));
	}
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
