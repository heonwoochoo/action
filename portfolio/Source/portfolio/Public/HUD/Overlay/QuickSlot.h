// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuickSlot.generated.h"


class UTextBlock;
class UTexture2D;
class UProgressBar;
class UImage;

UCLASS()
class PORTFOLIO_API UQuickSlot : public UUserWidget
{
	GENERATED_BODY()
	
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CoolDownText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* CoolDownProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* SlotBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* InputKey;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Texture")
	UTexture2D* SlotReadyBorder;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Texture")
	UTexture2D* SlotCoolDownBorder;

public:
	FORCEINLINE UTextBlock* GetCoolDownText() const { return CoolDownText; }
	
};
