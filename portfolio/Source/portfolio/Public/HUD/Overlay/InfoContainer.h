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
	UTextBlock* Item1_Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemImage1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* ItemCoolDownProgressBar1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemCoolDownText1;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Item2_Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemImage2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* ItemCoolDownProgressBar2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemCoolDownText2;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Item3_Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemImage3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* ItemCoolDownProgressBar3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemCoolDownText3;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Item4_Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemImage4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* ItemCoolDownProgressBar4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemCoolDownText4;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Item5_Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemImage5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* ItemCoolDownProgressBar5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemCoolDownText5;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Item6_Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemImage6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* ItemCoolDownProgressBar6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemCoolDownText6;



	void Init();

	void UpdateHP();
	void UpdateStamina();
	void UpdateExp();

	void UpdateLevel();

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

	void InitItemPotions();

	void UpdateItemCoolDown1();
	void UpdateItemCoolDown2();
	void UpdateItemCoolDown3();
	void UpdateItemCoolDown4();
	void UpdateItemCoolDown5();
	void UpdateItemCoolDown6();

	void UpdateCoolDownUI(FTimerHandle* TimerHandle, UTextBlock* Text, UProgressBar* ProgressBar, bool IsEnable);

private:
	// 아이템의 첫 번째 칸부터 순차적으로 이미지를 적용하기 위한 Index
	uint8 PotionIdx = 0;

	// 업데이트가 필요한 소모품들의 포인터를 담는 배열
	TArray<FPotionUI> ItemPotions;

	// 소모품 UI 초기화
	void RemoveConsumableUI();

	// 인벤토리 컴포넌트의 현재 인벤토리가 가지고 있는 포션 개수를 확인하여 업데이트 수행
	void CheckItemPotionInInventory();
};
