// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "PhysicalMaterialBase.generated.h"

class USoundBase;
class UNiagaraSystem;

UCLASS()
class PORTFOLIO_API UPhysicalMaterialBase : public UPhysicalMaterial
{
	GENERATED_BODY()
	
public:
	UPhysicalMaterialBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound");
	USoundBase* FootstepSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound");
	UNiagaraSystem* FootstepParticle;
};
