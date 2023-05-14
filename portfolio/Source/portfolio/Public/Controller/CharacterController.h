// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Types/SettingTypes.h"
#include "CharacterController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedInputModeSignature, const EInputMode&, Mode);

UCLASS()
class PORTFOLIO_API ACharacterController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ACharacterController();

	FOnChangedInputModeSignature OnChangedInputMode;

private:
	// 메뉴 창이 열리는 뷰포트 상의 위치
	// 닫기 전에 값이 저장되어야함
	FVector2D CharacterInfoInitialLocation;
	FVector2D InventoryInitialLocation;
	FVector2D QuestInitialLocation;

public:

	FORCEINLINE const FVector2D& GetCharacterInfoInitialLocation() const {
		return CharacterInfoInitialLocation;
	}

	FORCEINLINE void SetCharacterInfoInitialLocation(const FVector2D& NewLocation)
	{
		CharacterInfoInitialLocation = NewLocation;
	}

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

	// 인풋모드 상태 전환
	void SetInputModeToGame();
	void SetInputModeToUI();

	// 인게임 메뉴 토글버튼 생성
	void OpenMenuToggle();
};
