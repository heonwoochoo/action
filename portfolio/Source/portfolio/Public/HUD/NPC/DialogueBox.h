// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/SettingTypes.h"
#include "DialogueBox.generated.h"

class UButton;
class UImage;
class UTextBlock;
class UTexture2D;
class UNPCDialogueComponent;

UCLASS()
class PORTFOLIO_API UDialogueBox : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	// 다이얼로그를 관리하는 컴포넌트
	UNPCDialogueComponent* DialogueComponent;

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
	UFUNCTION()
	void OnChangedInputMode(const EInputMode& NewMode);

	FORCEINLINE UNPCDialogueComponent* GetNPCDialogueComponent() const { return DialogueComponent; }
	FORCEINLINE void SetNPCDialogueComponent(UNPCDialogueComponent* InDialogueComponent) { DialogueComponent = InDialogueComponent; }

	// 텍스트 내용 변경
	void SetDialogueText(const FText& InText);

	// Prev 버튼 비활성화
	void DeactivatePrevButton();
	// Prev 버튼 활성화
	void ActivatePrevButton();

	// 다음 페이지 버튼의 텍스트를 수락 버튼으로 변경
	void ChangeNextButtonToAccept();

	//  수락 버튼의 텍스트를 다음 페이지 버튼으로 변경
	void ChangeAcceptButtonToNext();
};
