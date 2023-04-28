// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/Overlay/QuickSlot.h"
#include "Types/CharacterTypes.h"
#include "SkillSlot.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API USkillSlot : public UQuickSlot
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	ESkillNumber SkillNumber = ESkillNumber::ESN_None;

public:
	FORCEINLINE void SetSkillNumber(const ESkillNumber& Number) { SkillNumber = Number; }

	// 스킬 넘버를 참조하여 UI 속성값 초기화
	void Init();

	// 쿨다운 UI 업데이트
	UFUNCTION()
	void UpdateCoolDown(const float& Remaining, const float& Rate);

	UFUNCTION()
	void ResetCooldDown();
};
