// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HelperFunction.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UHelperFunction : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	static float GetRandomDamage(float Damge);

	UFUNCTION()
	static FName GetNameFromEnemyCode(const FName& InEnemyCode);
};