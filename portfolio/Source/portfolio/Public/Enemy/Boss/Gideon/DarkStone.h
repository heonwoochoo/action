// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DarkStone.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UParticleSystemComponent;
class UParticleSystem;
class USoundCue;

UCLASS()
class PORTFOLIO_API ADarkStone : public AActor
{
	GENERATED_BODY()
	
public:	
	ADarkStone();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* ParticleComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UParticleSystem* HitImpactParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UParticleSystem* NoHitParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UParticleSystem* TrailParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundCue* HitSound;

private:
	// 객체를 스폰한 소유자
	AActor* Owner;

	// 날라갈 타겟
	AActor* Target;

	float Damage = 0.f;

public:	
	UFUNCTION()
	void OnOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// 타겟으로 날라가는 방향 설정
	void SetTarget(AActor* InTarget);

	FORCEINLINE void SetDamage(const float& InDamage) { Damage = InDamage; }
	FORCEINLINE void SetOwner(AActor* NewOwner) { Owner = NewOwner; }

};
