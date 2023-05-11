// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/Menu/InGame/MovableWidget.h"
#include "Types/ItemTypes.h"
#include "Types/SettingTypes.h"
#include "Inventory.generated.h"

class UButton;
class UImage;
class UOverlay;
class UItemBox;
class UHorizontalBox;
class UTextBlock;
class UInGameMenu;
class UTexture2D;

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
	UImage* EquipmentTabBackground;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* EquipmentTabText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* EquipmentTabButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* EquipmentTabUnderline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UOverlay* ConsumableTabOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ConsumableTabBackground;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ConsumableTabText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ConsumableTabButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ConsumableTabUnderline;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Texture")
	UTexture2D* ActivatedTab;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Texture")
	UTexture2D* DeactivatedTab;

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

	void UpdateItemList(EItemType ItemType);

private:
	void InitEquipmentTabButton();
	void InitConsumableTabButton();

	// 캐릭터가 가지고 있는 아이템 리스트를 보여줍니다
	void ShowItemList(EItemType ItemType);

	// 인벤토리에 아이템을 나타내기전 기존에 있던 아이템 박스 초기화
	void ClearAllItemBox();

	// 툴팁이 뜨는 위치
	FVector2D TooltipLocation;

	// 선택된 탭
	EItemType SelectedTap;

	// 탭 변경시 적용되는 이미지
	void UpdateTabImage(bool IsActive, UImage* TabBackground, UTextBlock* TabText, UImage* TabUnderline);

	// 탭 이미지를 비활성화 상태로 만듦
	void UncheckTabImage(EItemType TargetTab);

	// 탭 변경시 소리 재생
	void PlayChangeButtonSound();

	// 가지고 있는 골드를 보여줌
	void UpdateGold();

	UFUNCTION()
	void OnChangedInputMode(const EInputMode& Mode);
};
