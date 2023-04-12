// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDBase.generated.h"

class ADamageText;
class ACharacter;
class ATargetMark;
class UUserWidget;
class UInfoContainer;
class UComboCountWidget;
class UOverlappedItemWidget;

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
	TSubclassOf<ADamageText> DamageTextClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Combat", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ATargetMark> TargetMarkClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Overlay", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> InfoContainerClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Combat", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UComboCountWidget> ComboCountClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Item", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UOverlappedItemWidget> OverlappedItemClass;

	UInfoContainer* InfoContainer;

	UComboCountWidget* ComboCountWidget;

	UOverlappedItemWidget* OverlappedItemWidget;

	void InitInfoContainer();
	void InitComboCountWidget();
	void InitOverlappedItemWidget();

public:
	void ShowDamageOnScreen(ACharacter* Actor, float Damage);
	void ShowTargetMark(ACharacter* Enemy, ACharacter* Caster);

	FORCEINLINE UInfoContainer* GetInfoContainer() { return InfoContainer; }
	FORCEINLINE UComboCountWidget* GetComboCountWidget() { return ComboCountWidget; }
	FORCEINLINE UOverlappedItemWidget* GetOverlappedItemWidget() { return OverlappedItemWidget; }
	
};