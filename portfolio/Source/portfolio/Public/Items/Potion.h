// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "Potion.generated.h"

UCLASS()
class PORTFOLIO_API APotion : public AItemBase
{
	GENERATED_BODY()
	
public:
	APotion();


protected:
	virtual void BeginPlay() override;


public:	
	virtual void Tick(float DeltaTime) override;
};
