// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemBox.generated.h"

class UButton;
class UImage;
class UOverlay;
class UTextBlock;
class UTexture2D;
class UInventory;

UCLASS()
class PORTFOLIO_API UItemBox : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemSlotImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Image")
	UTexture2D* ClickedSlotImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Image")
	UTexture2D* NormalSlotImage;



public:
	void SetItemImage(UTexture2D* Image);

	void SetItemAmount(uint8 Amount);

	FORCEINLINE void SetItemCode(const FName& InItemCode) { ItemCode = InItemCode; }
	FORCEINLINE void SetInventory(UInventory* InInventory) { Inventory = InInventory; }

private:
	FName ItemCode;

	UInventory* Inventory;

	void PlayEquipAnimation();
};
