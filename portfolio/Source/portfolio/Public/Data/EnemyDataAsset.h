// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemyTypes.h"
#include "EnemyDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UEnemyDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EEnemyName, FEnemyData> EnemyDatas;
};
