// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpotNameNotify.generated.h"

class UWidgetAnimation;
class UTextBlock;

/**
* 캐릭터의 장소가 바뀔 때마다 화면에 알려주는 위젯입니다.
*/

UCLASS()
class PORTFOLIO_API USpotNameNotify : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* ShowAndHide;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* SpotText;

public:
	FWidgetAnimationDynamicEvent EndAnimationEvent;

	// 애니메이션 종료시 호출, 위젯을 제거함
	UFUNCTION()
	void OnEndShowAndHideAnimation();

	void SetSpotText(const FText& InName);

	// 나타났다 사라지는 애니메이션 재생
	void PlayShowAndHideAnimation();
};
