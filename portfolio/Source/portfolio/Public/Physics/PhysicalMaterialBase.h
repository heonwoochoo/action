// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Types/SettingTypes.h"
#include "Types/CharacterTypes.h"
#include "PhysicalMaterialBase.generated.h"

class UDataTable;
class UNiagaraSystem;
class USoundCue;

UCLASS()
class PORTFOLIO_API UPhysicalMaterialBase : public UPhysicalMaterial
{
	GENERATED_BODY()
	
public:
	UPhysicalMaterialBase();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data");
	UDataTable* MovementEmitterDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data");
	UDataTable* MovementSoundDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties");
	ESurfaceType Surface = ESurfaceType::ESF_None;
	
public:
	UNiagaraSystem* GetMovementEmitter(const EMovementType& MovementType) const;

	USoundCue* GetMovementSound(const EMovementType& MovementType) const;
};
