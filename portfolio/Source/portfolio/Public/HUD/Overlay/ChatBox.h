// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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

	UFUNCTION()
	void OnPressedMovingBar();

	UFUNCTION()
	void OnReleasedMovingBar();

private:
	// 최대 저장할 라인 수
	int32 MaxLineNumber = 50;

	void InitMovingBar();

public:
	void PrintMessageOnChat(const FText& Message, const FColor& Color);
};
