// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DefaultSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API UDefaultSaveGame : public USaveGame
{
	GENERATED_BODY()

private:
	// 슬롯에 저장할 유저의 고유 이름
	FName UserName;

	// 저장된 포지션
	FVector Location;

public:
	FVector GetLocation() const;
	void SetLocation(const FVector& Pos);
};
