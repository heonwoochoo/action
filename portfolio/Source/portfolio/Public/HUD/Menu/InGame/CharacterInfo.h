﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/Menu/InGame/MovableWidget.h"
#include "Types/SettingTypes.h"
#include "CharacterInfo.generated.h"

class UCanvasPanel;
class UButton;
class UImage;
class UTextBlock;
class UTexture2D;
class UEquipmentSlot;
class UProgressBar;

UCLASS()
class PORTFOLIO_API UCharacterInfo : public UMovableWidget
{
	GENERATED_BODY()
	

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativeDestruct() override;

	virtual void OnReleasedTitleDragButton() override;

	virtual void InitCanvasLocation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEquipmentSlot* HelmetSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEquipmentSlot* ArmourSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEquipmentSlot* WeaponSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEquipmentSlot* SubWeaponSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEquipmentSlot* ShieldSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEquipmentSlot* AccessorySlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEquipmentSlot* ShoesSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* UserNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* LevelText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ClassText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* HpCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* HpMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* HPProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* StaminaCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* StaminaMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* StaminaProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ExpCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ExpMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* ExpProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ADText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ADDefenseText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* AttackSpeedText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CriticalText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* APText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* APDefenseText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CoolDownText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MovementSpeedText;

	UFUNCTION()
	void UpdateHealth(const float& CurrentHp, const float& MaxHp);

	UFUNCTION()
	void UpdateStamina(const float& CurrentSp, const float& MaxSp);

private:
	TArray<UEquipmentSlot*> EquipmentSlots;

	FVector2D TooltipLocation;

	void InitEquipmentSlot();
	void UpdateStats();


public:
	FORCEINLINE FVector2D GetTooltipLocation() const { return TooltipLocation; };

	void OnHoveredSlot(const FName& ItemCode);
	void OnUnhoveredSlot();

	UFUNCTION()
	void ChangedInputMode(const EInputMode& Mode);
};
