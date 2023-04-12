// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemTypes.h"
#include "Potion.generated.h"

class USphereComponent;
class UDataTable;
class UParticleSystem;
class UCurveFloat;
class UTexture2D;

UCLASS()
class PORTFOLIO_API APotion : public AActor
{
	GENERATED_BODY()
	
public:
	APotion();


protected:
	UPROPERTY(VisibleDefaultsOnly)
	USphereComponent* CollisionComponent;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	UDataTable* PotionDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	EItemName PotionName = EItemName::EIN_None;

	// 아이템 획득 시 생성될 파티클
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties|Particle")
	UParticleSystem* PickupParticle;

	// 획득 시 스케일 값의 변화 (애니메이션 효과)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	UCurveFloat* PickupScaleCurve;

	virtual void BeginPlay() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;


	virtual void Destroyed() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void HandlePickupPotion(AActor* PickupCharacter);

	FPotionInfo* GetPotionInfo();
	FName GetName();
	FName GetDescription();
	float GetCoolDown();
	UTexture2D* GetImage();

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
