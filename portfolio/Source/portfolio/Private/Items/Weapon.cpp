// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapon.h"

AWeapon::AWeapon()
{
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FName("Weapon"));
}

void AWeapon::AttachMeshToSocket(USceneComponent* InParent, const FName& InputSocketName)
{
	const FAttachmentTransformRules TransFormRules(EAttachmentRule::SnapToTarget, true);
	SkeletalMesh->AttachToComponent(InParent, TransFormRules, InputSocketName);
}