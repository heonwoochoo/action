// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types/ItemTypes.h"
#include "ItemBase.generated.h"

class USphereComponent;
class UDataTable;


UCLASS()
class PORTFOLIO_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemBase();

protected:

	virtual void BeginPlay() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	UDataTable* ItemSpecData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	FName Code;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	FItemSpec Spec;

	// 아이템 획득 시 생성될 파티클
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties|Particle")
	UParticleSystem* PickupParticle;

	// 획득 시 스케일 값의 변화 (애니메이션 효과)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	UCurveFloat* PickupScaleCurve;

private:
	FTimerHandle PickupTimerHandle;

	// 아이템 획득시 메쉬의 스케일 변화 시간
	float PickupScaleTime = 1.f;

	// 아이템을 획득한 플레이어
	AActor* Character;

	void EndPickupTimer();

	// 습득한 캐릭터 쪽으로 이동하는 애니메이션 효과
	void MoveToCharacter(float DeltaTime);

public:	
	void HandlePickupItem(AActor* PickupCharacter);

	FORCEINLINE FName GetItemCode() const { return Code; }
	FORCEINLINE FItemSpec GetItemSpec() const { return Spec; }

	// 플레이어가 근접시 아웃라인을 노란색으로 표시
	void ChangeMeshOutline();

	// 아웃라인 제거
	// 아이템 획득 또는 오버랩을 빠져나갈 경우
	void RemoveMeshOutline();

};
