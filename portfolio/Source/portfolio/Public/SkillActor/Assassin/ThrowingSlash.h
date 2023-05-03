// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThrowingSlash.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;
class UParticleSystem;

UCLASS()
class PORTFOLIO_API AThrowingSlash : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AThrowingSlash();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	UBoxComponent* BoxCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	UProjectileMovementComponent* ProjectileMovementComponent;

	// 날라가는 속도
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties");
	float SlashSpeed = 3000.f;
	

private:
	// 스킬 시전자
	AActor* Owner;

	float Damage;

	// 타격시 생성될 이펙트
	UParticleSystem* HitImpactEmitter;

	// 한 타겟당 1회만 공격
	// 데미지의 중복을 검사하기 위한 컨테이너
	TSet<AActor*> DamagedActors;
	
public:	
	FORCEINLINE AActor* GetOwner() const { return Owner; }
	FORCEINLINE void SetOwner(AActor* NewOwner) { Owner = NewOwner; }

	FORCEINLINE float GetDamage() const { return Damage; }
	FORCEINLINE void SetDamage(const float& NewDamage) { Damage = NewDamage; }

	UFUNCTION()
	void OnOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FORCEINLINE void SetHitImpactEmitter(UParticleSystem* NewHitImpactEmitter) { HitImpactEmitter = NewHitImpactEmitter; }

};
