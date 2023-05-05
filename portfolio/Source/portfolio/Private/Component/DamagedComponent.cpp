// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/DamagedComponent.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "HUD/Combat/DamageText.h"
#include "DefaultCharacter.h"
#include "Components/CapsuleComponent.h"

UDamagedComponent::UDamagedComponent()
{

	PrimaryComponentTick.bCanEverTick = true;


}

void UDamagedComponent::BeginPlay()
{
	Super::BeginPlay();


	
}


void UDamagedComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void UDamagedComponent::ApplyHitOverlayMaterial()
{
	ACharacter* Owner = Cast<ACharacter>(GetOwner());
	if (Owner)
	{
		USkeletalMeshComponent* MeshComponent = Owner->GetMesh();
		if (MeshComponent && HitMaterialInstance)
		{
			MeshComponent->SetOverlayMaterial(HitMaterialInstance);
			GetWorld()->GetTimerManager().SetTimer(HitOverlayTimerHandle, this, &UDamagedComponent::OnEndHitOveralyTimer, 0.1f, false);
		}
	}
}

void UDamagedComponent::OnEndHitOveralyTimer()
{
	ACharacter* Owner = Cast<ACharacter>(GetOwner());
	if (Owner)
	{
		USkeletalMeshComponent* MeshComponent = Owner->GetMesh();
		if (MeshComponent)
		{
			MeshComponent->SetOverlayMaterial(nullptr);
		}
	}
}

void UDamagedComponent::ChangeMeshOutline()
{
	// ���忡 ��ġ�� ����Ʈ ���μ��̿� ������ ����
	// �������� �������� ��Ÿ��
	ACharacter* Owner = Cast<ACharacter>(GetOwner());
	if (Owner)
	{
		USkeletalMeshComponent* MeshComponent = Owner->GetMesh();
		if (MeshComponent)
		{
			MeshComponent->SetRenderCustomDepth(true);
			MeshComponent->SetCustomDepthStencilValue(1);

			GetWorld()->GetTimerManager().ClearTimer(MeshOutlineTimerHandle);
			GetWorld()->GetTimerManager().SetTimer(MeshOutlineTimerHandle, this, &UDamagedComponent::RemoveMeshOutline, HitOutlineDurationTime, false);
		}
	}
}

void UDamagedComponent::RemoveMeshOutline()
{
	ACharacter* Owner = Cast<ACharacter>(GetOwner());
	if (Owner)
	{
		USkeletalMeshComponent* MeshComponent = Owner->GetMesh();
		if (MeshComponent)
		{
			MeshComponent->SetRenderCustomDepth(false);
		}
	}
}

void UDamagedComponent::ShowDamageText(const float& DamageAmount, const bool& IsCritical)
{
	if (DamageTextClass)
	{
		ACharacter* Owner = Cast<ACharacter>(GetOwner());
		if (Owner)
		{
			const FVector& Location = Owner->GetActorLocation() + Owner->GetActorUpVector() * Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
			const FRotator& Rotation = Owner->GetActorRotation();
			FActorSpawnParameters SpawnInfo;
			ADamageText* DamageText = GetWorld()->SpawnActor<ADamageText>(DamageTextClass, Location, Rotation, SpawnInfo);
			DamageText->Initialize(DamageAmount, IsCritical);
		}
	}
}

bool UDamagedComponent::IsDamagedCritical(AActor* DamageCauser)
{
	ADefaultCharacter* Causer = Cast<ADefaultCharacter>(DamageCauser);
	if (Causer)
	{
		const FCharacterStats& Stats = Causer->GetCharacterStats();

		const int32& Rand = FMath::FRandRange(1, 100);
		if (Stats.Critical > Rand)
		{
			return true;
		}
	}
	return false;
}

