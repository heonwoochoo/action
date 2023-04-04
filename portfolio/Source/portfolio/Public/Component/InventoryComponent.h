// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemTypes.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UDataTable* PotionDataTable;

	// 저장되어 있는 아이템
	TMap<EItemName, uint8> ItemsAmount;

public:
	TMap<EItemName, uint8> GetItemAmountMap() const;

	uint8 GetItemAmount(EItemName ItemName);

	// 소모품 획득시 아이템 목록 업데이트
	void AddItemPotion(EItemName ItemName);

	// 소모품 사용시 아이템 목록 업데이트
	void UseItemPotion(EItemName ItemName);

	UDataTable* GetPotionDataTable() const;

	// UI 이미지와 수량을 업데이트
	void UpdatePotionUI();
};
