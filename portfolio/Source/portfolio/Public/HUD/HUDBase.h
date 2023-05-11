// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDBase.generated.h"

class ADamageText;
class ACharacter;
class UUserWidget;
class UInfoContainer;
class UComboCountWidget;
class UItemTooltipWidget;
class UInGameMenu;
class UUserMessage;
class UChatBox;
class UInGameMenuToggleButton;
class UGuideMessage;
class AHeadUpText;
class UBossHPBar;
class ABossBase;

UCLASS()
class PORTFOLIO_API AHUDBase : public AHUD
{
	GENERATED_BODY()
	
public:
	AHUDBase();

protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Combat", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UComboCountWidget> ComboCountClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Overlay", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> InfoContainerClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Item", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UItemTooltipWidget> ItemTooltipWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Overlay", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UInGameMenu> InGameMenuClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Overlay", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserMessage> UserMessageClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Overlay", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UChatBox> ChatBoxClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Overlay", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UInGameMenuToggleButton> InGameMenuToggleButtonClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Overlay", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGuideMessage> GuideMessageClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Overlay", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UBossHPBar> BossHPBarClass;

	UInfoContainer* InfoContainer;

	UComboCountWidget* ComboCountWidget;

	UItemTooltipWidget* ItemTooltipWidget;

	UInGameMenu* InGameMenuWidget;

	UUserMessage* UserMessageWidget;

	UChatBox* ChatBoxWidget;

	UInGameMenuToggleButton* InGameMenuToggleWidget;

	UGuideMessage* GuideMessageWidget;

	UBossHPBar* BossHpBar;

	TArray<TSubclassOf<UUserWidget>> InGameMenuChildWidgetClasses;

	void InitInfoContainer();
	void InitComboCountWidget();
	void InitUserMessage();
	void InitChatBox();
	void InitGuideMessage();

public:
	void ShowItemTooltip(const FName& ItemCode, const FVector2D& Location);
	void HideItemTooltip();

	// 캐릭터 컨트롤 모드 -> UI모드 전환시에 항상 호출되어야함
	void CreateInGameMenuToggleButton();

	FORCEINLINE UInfoContainer* GetInfoContainer() { return InfoContainer; }
	FORCEINLINE UComboCountWidget* GetComboCountWidget() { return ComboCountWidget; }
	FORCEINLINE UItemTooltipWidget* GetItemTooltip() { return ItemTooltipWidget; }
	
	UFUNCTION(BlueprintCallable)
	void InitScreenOverlay();

	void OpenInGameMenu();
	void CloseInGameMenu();

	//화면 중앙 상단에 유저 알림 메세지 출력
	void NotifyMessageToUser(const FText& Message);

	// 가이드 메세지 토글
	void ShowGuideMessage(const FText& Message);
	void HideGuideMessage();

	// 보스전 HP Bar 생성
	void CreateBossHPBar(ABossBase* BossActor);

};