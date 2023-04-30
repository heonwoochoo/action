// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DarkWave.generated.h"

class UBoxComponent;
class UParticleSystemComponent;
class UParticleSystem;
class USoundCue;

UCLASS()
class PORTFOLIO_API ADarkWave : public AActor
{
	GENERATED_BODY()
	
public:	
	ADarkWave();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* ParticleComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UParticleSystem* HitImpactParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundCue* HitSound;

	/**
	* 데미지가 적용되는 구간의 오버랩을 타이머로 설정
	*/
	FTimerHandle OverlapActivateTimerHandle;
	FTimerHandle OverlapDeactivateTimerHandle;

	float OverlapStartTime = 0.8f;
	float OverlapEndTime = 0.9f;

	void ActivateOverlap();
	void DeactivateOverlap();



private:
	// 객체를 스폰한 소유자
	AActor* Owner;

	// 타겟
	AActor* Target;

	float Damage = 0.f;

public:
	// 충돌체와의 이벤트
	UFUNCTION()
	void OnOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FORCEINLINE void SetDamage(const float& InDamage) { Damage = InDamage; }
	FORCEINLINE void SetOwner(AActor* NewOwner) { Owner = NewOwner; }

};
