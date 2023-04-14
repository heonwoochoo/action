// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/Menu/OptionsWidget.h"
#include "OptionsSound.generated.h"

class UButton;
class UImage;
class UTexture2D;
class UMainMenu;
class UTextBlock;
class UProgressBar;
class USlider;
class USoundClass;
class USoundMix;

UCLASS()
class PORTFOLIO_API UOptionsSound : public UOptionsWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	//=======================
	//       사운드 믹스
	//=======================
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound|Class")
	USoundClass* MasterClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound|Class")
	USoundClass* EffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound|Class")
	USoundClass* MusicClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound|Mix")
	USoundMix* MasterMix;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound|Mix")
	USoundMix* EffectMix;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound|Mix")
	USoundMix* MusicMix;

	// Master
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* MasterOverlayButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* MasterOverlayImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* MasterProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USlider* MasterSlider;

	// Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* EffectOverlayButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* EffectOverlayImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* EffectProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USlider* EffectSlider;

	// Music
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* MusicOverlayButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* MusicOverlayImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* MusicProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USlider* MusicSlider;

	// ==========================
	//		이벤트 바인딩
	// ==========================
	// Master
	UFUNCTION()
	void OnHoveredMaster();

	UFUNCTION()
	void OnUnhoveredMaster();

	UFUNCTION()
	void OnChangedMasterValue(float Value);

	// Effect
	UFUNCTION()
	void OnHoveredEffect();

	UFUNCTION()
	void OnUnhoveredEffect();

	UFUNCTION()
	void OnChangedEffectValue(float Value);

	// Music
	UFUNCTION()
	void OnHoveredMusic();

	UFUNCTION()
	void OnUnhoveredMusic();

	UFUNCTION()
	void OnChangedMusicValue(float Value);

private:
	void InitMaster();
	void InitEffect();
	void InitMusic();

	void SetVolume(USoundMix* SoundMix, USoundClass* SoundClass, float Value);
};
