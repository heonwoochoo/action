// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "PhysicalMaterialBase.generated.h"

class UDataTable;

UCLASS()
class PORTFOLIO_API UPhysicalMaterialBase : public UPhysicalMaterial
{
	GENERATED_BODY()
	
public:
	UPhysicalMaterialBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data");
	UDataTable* MovementEmitterDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data");
	UDataTable* MovementSoundDataTable;
};
