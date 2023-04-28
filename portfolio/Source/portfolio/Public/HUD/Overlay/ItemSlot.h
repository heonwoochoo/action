// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/Overlay/QuickSlot.h"
#include "Types/ItemTypes.h"
#include "ItemSlot.generated.h"

class UTextBlock;

UCLASS()
class PORTFOLIO_API UItemSlot : public UQuickSlot
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemAmount;

private:
	// 현재 아이템
	FName ItemCode;

	// 이전에 등록되어있던 아이템
	FName PrevItemCode;

	// 솔롯넘버
	EItemNumber SlotNumber = EItemNumber::EIN_NONE;

public:
	FORCEINLINE void SetItemCode(const FName& InItemCode) { ItemCode = InItemCode; }
	FORCEINLINE const FName& GetItemCode() const { return ItemCode; }

	FORCEINLINE void SetSlotNumber(const EItemNumber& Number) { SlotNumber = Number; }
	FORCEINLINE const EItemNumber& GetSlotNumber() const { return SlotNumber; }

	UFUNCTION()
	void OnUsedItem(const FName& UsedItemCode, const FItemSpec& Spec);

	UFUNCTION()
	void OnAddedItem(const FName& AddedItemCode, const FItemSpec& Spec);

	UFUNCTION()
	void UpdateCoolDownSlot(const float& Remaining, const float& Rate);
	
	UFUNCTION()
	void ResetCoolDownSlot();

	// 아무것도 등록 안 된 상태, 검은 배경으로 설정
	void Reset();

	// 등록된 아이템 코드를 참조하여 UI 설정
	void UpdateUI();

	void Init();
};
