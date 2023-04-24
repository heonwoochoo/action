// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/ItemTypes.h"
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
	UDataTable* ItemSpecData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect|Sound", meta = (AllowPrivateAccess = "true"))
	USoundCue* PotionConsumeSound;

	// 장착한 아이템
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<EEquipmentType, FEquippedItem> EquippedItemList;

	// 저장되어 있는 아이템
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<FName, uint8> ItemList;

	// 퀵슬롯에 등록된 아이템
	// 1,2,3 : 소모품
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName Slot1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName Slot2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName Slot3;

	// 4,5,6 : 장비
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName Slot4;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName Slot5;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName Slot6;

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

	// 포션의 데이터 값을 캐릭터에게 적용
	void EffectConsumable(const FName& ItemCode);

	// 포션 소모시 캐릭터 주위 파티클 생성
	void SpawnConsumeParticle(UParticleSystem* Particle);

	// 포션 소모시 재생되는 사운드
	void PlayConsumeSound();

	void InitEquippedItemList();

public:

	TMap<EEquipmentType, FEquippedItem> GetEquippedItemList() const;

	// 장비 장착
	void EquipItem(const FName& ItemCode);

	TMap<FName, uint8> GetItemList() const;

	uint8 GetItemAmount(const FName& ItemCode);

	// 소모품 획득시 아이템 목록 업데이트
	void AddItem(const FName& ItemCode);

	// 소모품 사용시 아이템 목록 업데이트
	void UseItem(const FName& ItemCode);

	UDataTable* GetItemDataTable() const;

	// UI 이미지와 수량을 업데이트
	void UpdateConsumableUI();

	// 퀵슬롯 관련 호출 함수
	void SlotHandle_1();
	void SlotHandle_2();
	void SlotHandle_3();
	void SlotHandle_4();
	void SlotHandle_5();
	void SlotHandle_6();

	// 소모품 아이템 매핑 초기화
	void ResetItemConsumableMapping();

	// 소모품 아이템 매핑, UI가 업데이트 되면서 호출됨
	void SetItemConsumableMapping(const FName& ItemCode, uint8 Idx);

	FTimerHandle* GetItemTimerHandle(EItemNumber ItemNum);

	bool GetEnableItem(EItemNumber ItemNum);

	bool HasItemInContainer(EItemNumber ItemNum);

	// 해당 아이템이 장착되었는지?
	bool IsEquippedItem(FName ItemCode);
};
