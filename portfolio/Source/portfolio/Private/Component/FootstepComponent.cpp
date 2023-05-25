// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/FootstepComponent.h"
#include "DefaultCharacter.h"
#include "Physics/PhysicalMaterialBase.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Sound/SoundCue.h"

UFootstepComponent::UFootstepComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}

void UFootstepComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UFootstepComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UFootstepComponent::HandleFootstep(const EFoot& Foot, const EMovementType& MovementType)
{
	ADefaultCharacter* Character = Cast<ADefaultCharacter>(GetOwner());
	if (Character)
	{
		USkeletalMeshComponent* Mesh = Character->GetMesh();
		if (Mesh)
		{
			FHitResult HitResult;
			FVector SocketLocation{};
			if (MovementType == EMovementType::EMT_Roll)
			{
				SocketLocation = Mesh->GetSocketLocation(RootSocketName);
			}
			else 
			{
				SocketLocation = Mesh->GetSocketLocation(Foot == EFoot::EF_Left ? LeftFootSocketName : RightFootSocketName);
			}
			const FVector& Location = SocketLocation + FVector::UpVector * 20.f;

			FCollisionQueryParams QueryParams;
			QueryParams.bReturnPhysicalMaterial = true;
			QueryParams.AddIgnoredActor(Character);
			
			GetWorld()->LineTraceSingleByChannel(HitResult, Location, Location + FVector::UpVector * -50.f, ECollisionChannel::ECC_WorldStatic, QueryParams);
			if (HitResult.bBlockingHit && HitResult.PhysMaterial.Get())
			{
				UPhysicalMaterialBase* PhysicalMaterial = Cast<UPhysicalMaterialBase>(HitResult.PhysMaterial.Get());
				if (PhysicalMaterial)
				{
					// 소리 재생
					USoundCue* Sound = PhysicalMaterial->GetMovementSound(MovementType);
					if (Sound)
					{
						UGameplayStatics::PlaySoundAtLocation(this, Sound, Location);
					}

					// 파티클 생성
					UNiagaraSystem* Particle = PhysicalMaterial->GetMovementEmitter(MovementType);
					if (Particle)
					{
						const FVector& HitLocation = HitResult.ImpactPoint;
						UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, Particle, HitLocation);
					}
				}
			}
		}
	}
}