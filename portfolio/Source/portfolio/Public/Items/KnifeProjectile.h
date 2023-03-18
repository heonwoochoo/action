// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KnifeProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class USkeletalMeshComponent;
class AportfolioCharacter;
UCLASS()
class PORTFOLIO_API AKnifeProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AKnifeProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly)
	USphereComponent* CollisionComponent;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

	AportfolioCharacter* Caster;

	void SetMovementDirection(const FVector& Direction);

	void OnKnifeEffect(AActor* HitActor);

	UFUNCTION()
	void OnBeginOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
