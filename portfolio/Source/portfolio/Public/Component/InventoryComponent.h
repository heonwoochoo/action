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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<EItemName, uint8> ItemsAmount;

	// 입력 이벤트와 매핑될 아이템
	// 1,2,3 : 소모품
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EItemName Item1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EItemName Item2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EItemName Item3;

	// 4,5,6 : 장비
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EItemName Item4;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EItemName Item5;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EItemName Item6;

	// 쿨타임 적용을 위한 타이머 핸들
	FTimerHandle ItemTimerHandle1;
	FTimerHandle ItemTimerHandle2;
	FTimerHandle ItemTimerHandle3;
	FTimerHandle ItemTimerHandle4;
	FTimerHandle ItemTimerHandle5;
	FTimerHandle ItemTimerHandle6;

	bool bEnableItem1 = true;
	bool bEnableItem2 = true;
	bool bEnableItem3 = true;
	bool bEnableItem4 = true;
	bool bEnableItem5 = true;
	bool bEnableItem6 = true;

	void EndTimerHandle1();
	void EndTimerHandle2();
	void EndTimerHandle3();
	void EndTimerHandle4();
	void EndTimerHandle5();
	void EndTimerHandle6();

	void EffectPotion(EStatTarget Target, float CoolDown, float AbilityPoint);

	// 포션 데이터 테이블로부터 아이템의 쿨다운 값 반환
	float GetItemPotionCoolDown(EItemName Name);

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

	FTimerHandle* GetItemTimerHandle(EItemNumber ItemNum);

	bool GetEnableItem(EItemNumber ItemNum);

	bool HasItemInContainer(EItemNumber ItemNum);
};
