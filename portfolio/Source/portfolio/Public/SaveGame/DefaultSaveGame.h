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
	// ���Կ� ������ ������ ���� �̸�
	FName UserName;

	// ����� ������
	FVector Location;

public:
	FVector GetLocation() const;
	void SetLocation(const FVector& Pos);
};
