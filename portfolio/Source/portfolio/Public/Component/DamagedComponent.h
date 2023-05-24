// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamagedComponent.generated.h"

class ADamageText;
class UMaterialInstance;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_API UDamagedComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDamagedComponent();

protected:
	virtual void BeginPlay() override;

	// 피격시 적용될 오버레이 머티리얼
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	UMaterialInstance* HitMaterialInstance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Combat", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ADamageText> DamageTextClass;

	// 히트 오버레이 해제 타이머
	FTimerHandle HitOverlayTimerHandle;

	// 피격시 생기는 외형선이 지속되는 시간
	float HitOutlineDurationTime = 5.f;

public:	
	// 피격시 오버레이 머리티얼 적용
	void ApplyHitOverlayMaterial();

	// 히트 오버레이 타이머 경과 -> 메쉬에 적용된 것을 해제
	void OnEndHitOveralyTimer();

	// 피격시 메쉬의 아웃라인을 빨간색으로 표시
	void ChangeMeshOutline();

	// 아웃라인 제거
	// 일정 시간동안 피격 없을 경우 또는 사망시 호출
	void RemoveMeshOutline();

	FTimerHandle MeshOutlineTimerHandle;

	/** 
	* 캐릭터 머리 위에 받은 데미지 텍스트를 출력합니다.
	* @param DamageAmount - 데미지
	* @param IsCritical - 크리티컬을 받았는지?
	*/
	void ShowDamageText(const float& DamageAmount, const bool& IsCritical);

	// 가해자에게 크리티컬 데미지를 받았는지?
	bool IsDamagedCritical(AActor* DamageCauser);

	// 경직 효과 설정
	void SetTimeDilation(const float& DilationRate, const float& Delay);

	// 경직 해제를 위한 타이머 핸들
	FTimerHandle TimeDilationHandle;
	void ResetTimeDilation();
};
