// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemTooltipWidget.generated.h"

class UImage;
class UTextBlock;
class AItemBase;
class UCanvasPanel;

/**
* 아이템 툴팁
* 1.캐릭터가 아이템 오브젝트에 근접시
* 2.인벤토리 내 아이템에 마우스 Hover시
*/
UCLASS()
class PORTFOLIO_API UItemTooltipWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* ItemCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemCoolDown;

public:
	// 오버랩 창에 표시될 UI 업데이트
	void UpdateOverlappedItemInfo(AItemBase* Item);

	// Canvas의 위치를 조정
	void SetCanvasPosition(const FVector2D& Location);

	FVector2D GetCanvasSize() const;
};