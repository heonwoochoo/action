// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/ItemTypes.h"
#include "InventoryComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UDataTable* ItemSpecData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect|Sound", meta = (AllowPrivateAccess = "true"))
	USoundCue* PotionConsumeSound;

	// 저장되어 있는 아이템
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<FName, uint8> ItemList;

	// 입력 이벤트와 매핑될 아이템
	// 1,2,3 : 소모품
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName Item1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName Item2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName Item3;

	// 4,5,6 : 장비
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName Item4;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName Item5;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName Item6;

	// 쿨타임 적용을 위한 타이머 핸들
	FTimerHandle ItemTimerHandle1;
	FTimerHandle ItemTimerHandle2;
	FTimerHandle ItemTimerHandle3;
	FTimerHandle ItemTimerHandle4;
	FTimerHandle ItemTimerHandle5;
	FTimerHandle ItemTimerHandle6;

	bool bEnableItem1 = true;
	bool bEnableItem2 = true;
	bool bEnableItem3 = true;
	bool bEnableItem4 = true;
	bool bEnableItem5 = true;
	bool bEnableItem6 = true;

	void EndTimerHandle1();
	void EndTimerHandle2();
	void EndTimerHandle3();
	void EndTimerHandle4();
	void EndTimerHandle5();
	void EndTimerHandle6();

	// 포션의 데이터 값을 캐릭터에게 적용
	void EffectConsumable(const FName& ItemName, const FItemSpec& Spec);

	// 포션 소모시 캐릭터 주위 파티클 생성
	void SpawnConsumeParticle(UParticleSystem* Particle);

	// 포션 소모시 재생되는 사운드
	void PlayConsumeSound();

public:
	const TMap<FName, uint8>& GetItemList() const;

	uint8 GetItemAmount(const FName& ItemName);

	// 소모품 획득시 아이템 목록 업데이트
	void AddItem(const FName& ItemName);

	// 소모품 사용시 아이템 목록 업데이트
	void UseItem(const FName& ItemName, const FItemSpec& Spec);

	UDataTable* GetItemDataTable() const;

	// UI 이미지와 수량을 업데이트
	void UpdateConsumableUI();

	// 아이템 사용 키보드 입력 이벤트 발생시 호출
	void ItemHandle_1();
	void ItemHandle_2();
	void ItemHandle_3();
	void ItemHandle_4();
	void ItemHandle_5();
	void ItemHandle_6();

	// 소모품 아이템 매핑 초기화
	void ResetItemConsumableMapping();

	// 소모품 아이템 매핑, UI가 업데이트 되면서 호출됨
	void SetItemConsumableMapping(const FName& Name, uint8 Idx);

	FTimerHandle* GetItemTimerHandle(EItemNumber ItemNum);

	bool GetEnableItem(EItemNumber ItemNum);

	bool HasItemInContainer(EItemNumber ItemNum);
};
