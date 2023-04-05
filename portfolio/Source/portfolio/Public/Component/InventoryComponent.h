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

	// 입력 이벤트와 매핑될 아이템
	// 1,2,3 : 소모품
	EItemName Item1;
	EItemName Item2;
	EItemName Item3;
	// 4,5,6 : 장비
	EItemName Item4;
	EItemName Item5;
	EItemName Item6;

	void EffectPotion(EItemEffect EffectType, float CoolDown, float AbilityPoint);

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

	// 아이템 사용 키보드 입력 이벤트 발생시 호출
	void ItemHandle_1();
	void ItemHandle_2();
	void ItemHandle_3();
	void ItemHandle_4();
	void ItemHandle_5();
	void ItemHandle_6();

	// 소모품 아이템 매핑 초기화
	void ResetItemPotionMapping();

	// 소모품 아이템 매핑, UI가 업데이트 되면서 호출됨
	void SetItemPotionMapping(EItemName Name, uint8 Idx);
};
