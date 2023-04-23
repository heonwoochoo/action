// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/ItemTypes.h"
#include "EquipmentSlot.generated.h"

class UImage;
class UButton;
class UTexture2D;


UCLASS()
class PORTFOLIO_API UEquipmentSlot : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* EquipmentSlotImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* EquipmentButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* EquipmentImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture|Icon")
	UTexture2D* HelmetIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture|Icon")
	UTexture2D* ArmourIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture|Icon")
	UTexture2D* WeaponIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture|Icon")
	UTexture2D* SubWeaponIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture|Icon")
	UTexture2D* ShieldIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture|Icon")
	UTexture2D* AccessoryIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture|Icon")
	UTexture2D* ShoesIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* EquippedSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* UnequippedSlot;


private:
	EEquipmentType EquipmentType;

	FName ItemName;

public:
	FORCEINLINE EEquipmentType GetEquipmentType() const { return EquipmentType; }
	FORCEINLINE void SetEquipmentType(const EEquipmentType& Type) { EquipmentType = Type; }
	
	FORCEINLINE FName GetItemName() const { return ItemName; }
	FORCEINLINE void SetItemName(const FName& InName) { ItemName = InName; }

	void InitByType(EEquipmentType Type);
};
