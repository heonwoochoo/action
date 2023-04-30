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

	FTimerHandle OverlapTimerHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	float OverlapRate = 0.8f;


private:
	// 객체를 스폰한 소유자
	AActor* Owner;

	float Damage = 0.f;

	// 충돌체와 오버랩되는 캐릭터가 있다면 데미지 적용 
	void CheckOverlapping();

public:
	
	FORCEINLINE void SetDamage(const float& InDamage) { Damage = InDamage; }
	FORCEINLINE void SetOwner(AActor* NewOwner) { Owner = NewOwner; }

};
