// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API AWeapon : public AItemBase
{
	GENERATED_BODY()
	
public:
	AWeapon();

	void AttachMeshToSocket(USceneComponent* InParent, const FName& InputSocketName);

protected:
	virtual void BeginPlay() override;
};
