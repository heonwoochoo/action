﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CharacterController.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API ACharacterController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ACharacterController();

private:
	// 메뉴 창이 열리는 뷰포트 상의 위치
	// 닫기 전에 값이 저장되어야함
	FVector2D InventoryInitialLocation;
	FVector2D QuestInitialLocation;

public:
	FORCEINLINE const FVector2D& GetInventoryInitialLocation() const {
		return InventoryInitialLocation;
	}

	FORCEINLINE void SetInventoryInitialLocation(const FVector2D& NewLocation)
	{
		InventoryInitialLocation = NewLocation;
	}

	FORCEINLINE const FVector2D& GetQuestInitialLocation() const {
		return QuestInitialLocation;
	}

	FORCEINLINE void SetQuestInitialLocation(const FVector2D& NewLocation)
	{
		QuestInitialLocation = NewLocation;
	}
};
