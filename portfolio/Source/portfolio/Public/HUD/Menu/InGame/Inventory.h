// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/ItemTypes.h"
#include "Inventory.generated.h"

class UButton;
class UImage;
class UOverlay;
class UItemBox;
class UHorizontalBox;
class UTextBlock;
class UTexture2D;
class UInGameMenu;
class UCanvasPanel;

UCLASS()
class PORTFOLIO_API UInventory : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativeDestruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* InventoryCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UOverlay* InventoryDragOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* InventoryTextImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* InventoryDragButton;

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
	UButton* ExitButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage*	ExitButtonImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* GoldText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TSubclassOf<UItemBox> ItemBoxClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* ActivatedExitButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* DeactivatedExitButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* ActivatedBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* DeactivatedBox;

	UInGameMenu* InGameMenu;

	UFUNCTION()
	void OnHoveredInventoryDragButton();

	UFUNCTION()
	void OnUnhoveredInventoryDragButton();

	UFUNCTION()
	void OnPressedInventoryDragButton();

	UFUNCTION()
	void OnReleasedInventoryDragButton();

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

	UFUNCTION()
	void OnHoveredExitButton();

	UFUNCTION()
	void OnUnhoveredExitButton();

	UFUNCTION()
	void OnClickedExitButton();

public:
	void SetInGameMenu(UInGameMenu* InInGameMenu);


private:
	void InitInventoryDragButton();
	void InitEquipmentTabButton();
	void InitConsumableTabButton();
	void InitExitButton();

	// 캐릭터가 가지고 있는 아이템 리스트를 보여줍니다
	void ShowItemList(EItemType ItemType);

	void PlayButtonSound();

	// 오픈시 저장된 위치 값 불러오기
	void InitCanvasLocation();

	// 버튼 Press,Release 이벤트로 토글
	// true시 인벤토리 창이 마우스 따라 이동
	bool bCanMovable = false;

	// 마우스와 캔버스의 간격
	float OffsetX;
	float OffsetY;
};
