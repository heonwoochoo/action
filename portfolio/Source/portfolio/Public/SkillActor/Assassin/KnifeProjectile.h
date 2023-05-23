// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KnifeProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class USkeletalMeshComponent;
class ADefaultCharacter;
class USoundCue;

UCLASS()
class PORTFOLIO_API AKnifeProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AKnifeProjectile();

protected:
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

protected:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly)
	USphereComponent* CollisionComponent;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

private:
	// 스킬을 시전한 캐릭터
	ADefaultCharacter* Caster;

	float Damage = 0.f;

public:
	FORCEINLINE void SetCaster(ADefaultCharacter* NewCaster) { Caster = NewCaster; }
	FORCEINLINE ADefaultCharacter* GetCaster() const { return Caster; }

	FORCEINLINE void SetDamage(const float& NewDamage) { Damage = NewDamage; }

	UFUNCTION()
	void OnBeginOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetMovementDirection(const FVector& Direction);

	UPROPERTY(EditDefaultsOnly)
	USoundCue* KnifeHitSound;
};
