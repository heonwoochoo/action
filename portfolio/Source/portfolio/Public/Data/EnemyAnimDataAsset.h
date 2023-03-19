// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemyTypes.h"
#include "EnemyAnimDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UEnemyAnimDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EEnemyName, FEnemyAnimData> EnemyAnimDatas;
};
