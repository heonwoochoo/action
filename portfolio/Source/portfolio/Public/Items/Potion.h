// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "Types/ItemTypes.h"
#include "Potion.generated.h"

class USphereComponent;
class UDataTable;
class UParticleSystem;
class UCurveFloat;
class UTexture2D;

UCLASS()
class PORTFOLIO_API APotion : public AItemBase
{
	GENERATED_BODY()
	
public:
	APotion();


protected:
	virtual void BeginPlay() override;


public:	
	virtual void Tick(float DeltaTime) override;

	void HandlePickupPotion(AActor* PickupCharacter);


private:
	FTimerHandle PickupTimerHandle;

	// 아이템 획득시 메쉬의 스케일 변화 시간
	float PickupScaleTime = 1.f;

	// 아이템을 획득한 플레이어
	AActor* Character;

	void EndPickupTimer();

	// 습득한 캐릭터 쪽으로 이동하는 애니메이션 효과
	void MoveToCharacter(float DeltaTime);
};
