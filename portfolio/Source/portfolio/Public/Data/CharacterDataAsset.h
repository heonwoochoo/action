// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterTypes.h"
#include "CharacterDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UCharacterDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCharacterData CharacterData;
};
