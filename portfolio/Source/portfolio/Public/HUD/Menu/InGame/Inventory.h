// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/Menu/InGame/MovableWidget.h"
#include "Types/ItemTypes.h"
#include "Inventory.generated.h"

class UButton;
class UImage;
class UOverlay;
class UItemBox;
class UHorizontalBox;
class UTextBlock;
class UInGameMenu;

UCLASS()
class PORTFOLIO_API UInventory : public UMovableWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativeDestruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UOverlay* EquipmentTabOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* EquipmentTabButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UOverlay* ConsumableTabOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ConsumableTabButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UHorizontalBox* ItemRow1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UHorizontalBox* ItemRow2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UHorizontalBox* ItemRow3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* GoldText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TSubclassOf<UItemBox> ItemBoxClass;

	UInGameMenu* InGameMenu;

	virtual void OnReleasedTitleDragButton() override;

	UFUNCTION()
	void OnHoveredEquipmentTabButton();

	UFUNCTION()
	void OnUnhoveredEquipmentTabButton();

	UFUNCTION()
	void OnClickedEquipmentTabButton();

	UFUNCTION()
	void OnHoveredConsumableTabButton();

	UFUNCTION()
	void OnUnhoveredConsumableTabButton();

	UFUNCTION()
	void OnClickedConsumableTabButton();

	virtual void InitCanvasLocation() override;

public:
	void SetInGameMenu(UInGameMenu* InInGameMenu);

	FORCEINLINE FVector2D GetTooltipLocation() const { return TooltipLocation; };

private:
	void InitEquipmentTabButton();
	void InitConsumableTabButton();

	// 캐릭터가 가지고 있는 아이템 리스트를 보여줍니다
	void ShowItemList(EItemType ItemType);

	// 툴팁이 뜨는 위치
	FVector2D TooltipLocation;
};
