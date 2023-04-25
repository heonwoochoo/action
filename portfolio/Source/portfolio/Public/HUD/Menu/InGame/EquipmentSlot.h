// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/ItemTypes.h"
#include "EquipmentSlot.generated.h"

class UImage;
class UButton;
class UTexture2D;
class UCharacterInfo;

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


	UFUNCTION()
	void OnHoveredEquipmentButton();

	UFUNCTION()
	void OnUnhoveredEquipmentButton();

private:
	// 해당 슬롯이 위치한 캐릭터 인포 창
	UCharacterInfo* CharacterInfo;
	
	EEquipmentType EquipmentType;

	FName ItemCode;

	void InitEquipmentButton();

public:
	FORCEINLINE EEquipmentType GetEquipmentType() const { return EquipmentType; }
	FORCEINLINE void SetEquipmentType(const EEquipmentType& Type) { EquipmentType = Type; }
	
	FORCEINLINE FName GetItemCode() const { return ItemCode; }
	FORCEINLINE void SetItemCode(const FName& InItemCode) { ItemCode = InItemCode; }

	// 슬롯의 장비 타입 설정
	void InitByType(EEquipmentType Type);

	// 캐릭터의 장비 착용 상태를 참조하여 슬롯에 이미지 적용
	void UpdateSlot();

	FORCEINLINE void SetCharacterInfo(UCharacterInfo* InCharacterInfo) { CharacterInfo = InCharacterInfo; }
};
