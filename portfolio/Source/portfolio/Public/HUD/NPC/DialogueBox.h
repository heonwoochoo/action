// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueBox.generated.h"

class UButton;
class UImage;
class UTextBlock;
class UTexture2D;

UCLASS()
class PORTFOLIO_API UDialogueBox : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* DialogueText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* NPCImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* CloseButtonImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* CloseButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CloseText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* PrevButtonImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* PrevButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PrevText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* NextButtonImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* NextButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* NextText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Textrue")
	UTexture2D* ActivatedButtonImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Textrue")
	UTexture2D* DeactivatedButtonImage;

	UFUNCTION()
	void OnHoveredCloseButton();

	UFUNCTION()
	void OnUnhoveredCloseButton();

	UFUNCTION()
	void OnClickedCloseButton();

	UFUNCTION()
	void OnHoveredPrevButton();

	UFUNCTION()
	void OnUnhoveredPrevButton();

	UFUNCTION()
	void OnClickedPrevButton();

	UFUNCTION()
	void OnHoveredNextButton();

	UFUNCTION()
	void OnUnhoveredNextButton();

	UFUNCTION()
	void OnClickedNextButton();

private:
	void InitCloseButton();
	void InitPrevButton();
	void InitNextButton();

public:
	

};
