// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/ItemTypes.h"
#include "InfoContainer.generated.h"

class UTextBlock;
class UTexture2D;
class UProgressBar;
class ADefaultCharacter;
class UAbilityComponent;
class UImage;
class UInventoryComponent;
class UProgressBarContainer;
class USkillSlot;
class UItemSlot;
class UHorizontalBox;

UCLASS()
class PORTFOLIO_API UInfoContainer : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	ADefaultCharacter* Character;

	UAbilityComponent* AbilityComponent;

	UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBarContainer* ProgressBarContainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UHorizontalBox* SkillSlotBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* SkillOneSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* SkillTwoSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* SkillThreeSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USkillSlot* SkillFourSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UHorizontalBox* ItemSlotBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UItemSlot* ItemOneSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UItemSlot* ItemTwoSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UItemSlot* ItemThreeSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UItemSlot* ItemFourSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UItemSlot* ItemFiveSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UItemSlot* ItemSixSlot;
	
private:
	// 스킬 슬롯 초기화
	void InitSkillSlot();

	// 아이템 슬롯 초기화
	void InitItemSlot();
};
