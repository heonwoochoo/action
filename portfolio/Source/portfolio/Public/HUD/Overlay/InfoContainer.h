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

USTRUCT(BlueprintType)
struct FPotionUI
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	UImage* Image;

	UPROPERTY()
	UTextBlock* Amount;
};

UCLASS()
class PORTFOLIO_API UInfoContainer : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	ADefaultCharacter* Character;

	UAbilityComponent* AbilityComponent;

	UInventoryComponent* InventoryComponent;

	//=======================
	// 플레이어 스탯 정보
	//=======================

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
	UProgressBar* ExpProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* LevelText;

	//================
	// 스킬
	//================
	/** One */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* SkillOneCoolDownText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* SkillOneImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* SkillOneCoolDownProgressBar;

	/** Two */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* SkillTwoCoolDownText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* SkillTwoImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* SkillTwoCoolDownProgressBar;

	/** Three */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* SkillThreeCoolDownText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* SkillThreeImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* SkillThreeCoolDownProgressBar;

	/** Four */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* SkillFourCoolDownText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* SkillFourImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* SkillFourCoolDownProgressBar;

	//===========================
	//          아이템
	//      1,2,3 : 소모품
	//      4,5,6 : 장비
	//===========================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemSlotOne_Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemImageOne;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* ItemCoolDownProgressBarOne;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemCoolDownTextOne;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemSlotTwo_Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemImageTwo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* ItemCoolDownProgressBarTwo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemCoolDownTextTwo;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemSlotThree_Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemImageThree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* ItemCoolDownProgressBarThree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemCoolDownTextThree;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemSlotFour_Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemImageFour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* ItemCoolDownProgressBarFour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemCoolDownTextFour;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemSlotFive_Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemImageFive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* ItemCoolDownProgressBarFive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemCoolDownTextFive;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemSlotSix_Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemImageSix;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* ItemCoolDownProgressBarSix;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemCoolDownTextSix;


	UFUNCTION()
	void UpdateHealth(const float& CurrentHp, const float& MaxHp);

	UFUNCTION()
	void UpdateStamina(const float& CurrentSp, const float& MaxSp);

	UFUNCTION()
	void UpdateExp(const float& CurrentExp, const float& MaxExp);

	UFUNCTION()
	void UpdateLevel(const int32& NewLevel);

	void UpdateSkillOne();
	void UpdateSkillOneImage();

	void UpdateSkillTwo();
	void UpdateSkillTwoImage();

	void UpdateSkillThree();
	void UpdateSkillThreeImage();

	void UpdateSkillFour();
	void UpdateSkillFourImage();

	void UpdateConsumableQuickSlot();
	void UpdateConsumableAmount(const FName& Name, UTexture2D* Image, uint8 Amount);
	
	UFUNCTION()
	void OnChangedQuickSlot(const FName& ItemCode, const FItemSpec& Spec);

	void InitItemPotions();

	UFUNCTION()
	void UpdateCoolDownSlotOne(const float& Remaining, const float& Rate);
	UFUNCTION()
	void ResetCoolDownSlotOne();

	UFUNCTION()
	void UpdateCoolDownSlotTwo(const float& Remaining, const float& Rate);
	UFUNCTION()
	void ResetCoolDownSlotTwo();

	UFUNCTION()
	void UpdateCoolDownSlotThree(const float& Remaining, const float& Rate);
	UFUNCTION()
	void ResetCoolDownSlotThree();

	UFUNCTION()
	void UpdateCoolDownSlotFour(const float& Remaining, const float& Rate);
	UFUNCTION()
	void ResetCoolDownSlotFour();

	UFUNCTION()
	void UpdateCoolDownSlotFive(const float& Remaining, const float& Rate);
	UFUNCTION()
	void ResetCoolDownSlotFive();

	UFUNCTION()
	void UpdateCoolDownSlotSix(const float& Remaining, const float& Rate);
	UFUNCTION()
	void ResetCoolDownSlotSix();

	void UpdateCoolDownUI(FTimerHandle* TimerHandle, UTextBlock* Text, UProgressBar* ProgressBar, bool IsEnable);

private:
	void Init();

	// 아이템의 첫 번째 칸부터 순차적으로 이미지를 적용하기 위한 Index
	uint8 PotionIdx = 0;

	// 업데이트가 필요한 소모품들의 포인터를 담는 배열
	TArray<FPotionUI> ItemPotions;

	// 소모품 UI 초기화
	void RemoveConsumableUI();

	// 인벤토리 컴포넌트의 현재 인벤토리가 가지고 있는 포션 개수를 확인하여 업데이트 수행
	void CheckItemPotionInInventory();
};
