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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties|Particle")
	UParticleSystem* PickupParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	UCurveFloat* PickupScaleCurve;

	virtual void BeginPlay() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void Destroyed() override;

public:	
	virtual void Tick(float DeltaTime) override;

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
