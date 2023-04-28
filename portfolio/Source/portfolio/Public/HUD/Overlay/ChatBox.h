// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/ItemTypes.h"
#include "ChatBox.generated.h"

class UButton;
class UImage;
class UScrollBox;
class UChatBoxMessage;

UCLASS()
class PORTFOLIO_API UChatBox : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ChatBackground;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UScrollBox* ChatScrollBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ChatMovingBar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget Class")
	TSubclassOf<UChatBoxMessage> ChatBoxMessageClass;

	// 버튼 Press,Release 이벤트로 토글
	// true시 인벤토리 창이 마우스 따라 이동
	bool bCanMovable = false;

	// 마우스와 캔버스의 간격
	float OffsetX;
	float OffsetY;

	UFUNCTION()
	void OnPressedMovingBar();

	UFUNCTION()
	void OnReleasedMovingBar();

private:
	// 최대 저장할 라인 수
	int32 MaxLineNumber = 50;

	void InitMovingBar();

public:
	UFUNCTION()
	void ShowLevelUpText(const int32& NewLevel);

	UFUNCTION()
	void ShowItemUsed(const FName& ItemCode, const FItemSpec& Spec);

	UFUNCTION()
	void ShowItemAdded(const FName& ItemCode, const FItemSpec& Spec);

	UFUNCTION()
	void ShowItemEquipped(const FName& ItemCode, const FItemSpec& Spec);

	void PrintMessageOnChat(const FText& Message, const FColor& Color);
};
