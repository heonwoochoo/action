// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/ItemTypes.h"
#include "InventoryComponent.generated.h"

class AWeapon;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FItemSignature, const FName&, ItemCode, const FItemSpec&, Spec);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnProgressCoolDownSignature, const float&, Remaining, const float&, Rate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndCoolDownSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	FItemSignature OnUsed;
	FItemSignature OnAdded;
	FItemSignature OnEquipped;
	FItemSignature OnUnEquipped;

	FOnProgressCoolDownSignature OnProgressCoolDownSlotOne;
	FOnEndCoolDownSignature OnEndCoolDownSlotOne;

	FOnProgressCoolDownSignature OnProgressCoolDownSlotTwo;
	FOnEndCoolDownSignature OnEndCoolDownSlotTwo;

	FOnProgressCoolDownSignature OnProgressCoolDownSlotThree;
	FOnEndCoolDownSignature OnEndCoolDownSlotThree;

	FOnProgressCoolDownSignature OnProgressCoolDownSlotFour;
	FOnEndCoolDownSignature OnEndCoolDownSlotFour;

	FOnProgressCoolDownSignature OnProgressCoolDownSlotFive;
	FOnEndCoolDownSignature OnEndCoolDownSlotFive;

	FOnProgressCoolDownSignature OnProgressCoolDownSlotSix;
	FOnEndCoolDownSignature OnEndCoolDownSlotSix;

	void NotifyCoolDown(const FTimerHandle& TimerHandle, const FOnProgressCoolDownSignature& Delegate);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UDataTable* ItemSpecData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect|Sound", meta = (AllowPrivateAccess = "true"))
	USoundCue* PotionConsumeSound;

	// 장착한 아이템 상태
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<EEquipmentType, FEquippedItem> EquippedItemList;

	// 장착중인 무기 오브젝트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AWeapon* EquippedWeapon;
	
	// 저장되어 있는 아이템
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<FName, uint8> ItemList;

	// 장착 예정인 무기, Anim Notify 호출시 EquipItem 함수에 파라미터 전달용
	FName EquippedItemCode;

	// 인벤토리 슬롯 개수
	int32 InventoryEquipmentSlotNumber = 12;
	int32 InventoryConsumableSlotNumber = 12;

	// 퀵슬롯에 등록된 아이템
	// 1,2,3 : 소모품
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName SlotOne;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName SlotTwo;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName SlotThree;

	// 4,5,6 : 장비
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName SlotFour;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName SlotFive;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName SlotSix;

	// 쿨타임 적용을 위한 타이머 핸들
	FTimerHandle ItemSlotOneTimerHandle;
	FTimerHandle ItemSlotTwoTimerHandle;
	FTimerHandle ItemSlotThreeTimerHandle;
	FTimerHandle ItemSlotFourTimerHandle;
	FTimerHandle ItemSlotFiveTimerHandle;
	FTimerHandle ItemSlotSixTimerHandle;

	bool bEnableItemSlotOne = true;
	bool bEnableItemSlotTwo = true;
	bool bEnableItemSlotThree = true;
	bool bEnableItemSlotFour = true;
	bool bEnableItemSlotFive = true;
	bool bEnableItemSlotSix = true;

	void EndSlotOneTimerHandle();
	void EndSlotTwoTimerHandle();
	void EndSlotThreeTimerHandle();
	void EndSlotFourTimerHandle();
	void EndSlotFiveTimerHandle();
	void EndSlotSixTimerHandle();

	// 포션의 데이터 값을 캐릭터에게 적용
	void EffectConsumable(const FName& ItemCode);

	// 포션 소모시 캐릭터 주위 파티클 생성
	void SpawnConsumeParticle(UParticleSystem* Particle);

	// 포션 소모시 재생되는 사운드
	void PlayConsumeSound();

	void InitEquippedItemList();

	// 아이템 사용시 슬롯의 쿨다운을 알림
	void HandleItemSlotCoolDown();

public:

	TMap<EEquipmentType, FEquippedItem> GetEquippedItemList() const;

	// 장비 장착
	UFUNCTION(BlueprintCallable)
	void EquipItem(const FName& ItemCode);

	TMap<FName, uint8> GetItemList() const;

	uint8 GetItemAmount(const FName& ItemCode);

	// 소모품 획득시 아이템 목록 업데이트
	void AddItem(const FName& ItemCode);

	// 소모품 사용
	void UseItem(const FName& ItemCode);

	UDataTable* GetItemDataTable() const;

	// 인벤토리 슬롯의 개수를 반환
	int32 GetInventorySlotNumber(const EItemType& Type);

	// 퀵슬롯 관련 호출 함수
	void HandleSlotOne();
	void HandleSlotTwo();
	void HandleSlotThree();
	void HandleSlotFour();
	void HandleSlotFive();
	void HandleSlotSix();

	const TArray<FName> GetItemSlots() const;

	// 해당 아이템 코드를 가지고있는 슬롯을 찾아 초기화
	void RemoveItemSlot(const FName& ItemCode);

	// 소모품 아이템 매핑, UI가 업데이트 되면서 호출됨
	void SetItemSlotMapping(const FName& ItemCode, uint8 Idx);

	FTimerHandle* GetItemTimerHandle(EItemNumber ItemNum);

	bool GetEnableItem(EItemNumber ItemNum);

	bool HasItemInContainer(EItemNumber ItemNum);

	// 해당 아이템이 장착되었는지?
	bool IsEquippedItem(FName ItemCode);

	void SetEquippedItemCode(const FName& ItemCode);

	UFUNCTION(BlueprintCallable)
	FName GetEquippedItemCode() const;
};
