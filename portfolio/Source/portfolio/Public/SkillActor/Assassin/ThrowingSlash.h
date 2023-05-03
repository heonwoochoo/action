// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThrowingSlash.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;
class UParticleSystem;
class AEnemyBase;

UENUM()
enum class ESlashType : uint8
{
	EST_Single UMETA(DisplayName = "Single"),
	EST_Multi UMETA(DisplayName = "Multi"),
	EST_None UMETA(DisplayName = "None"),
};

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

	// ���󰡴� �ӵ�
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties");
	float SlashSpeed = 3000.f;
	

private:
	// ��ų ������
	AActor* Owner;

	float Damage;

	// Ÿ�ݽ� ������ ����Ʈ
	UParticleSystem* HitImpactEmitter;

	// Single -> �� Ÿ�ٴ� 1ȸ�� ����
	// Multi -> 3ȸ ����
	// �������� �ߺ��� �˻��ϱ� ���� �����̳�
	TMap<AEnemyBase*, uint8> DamagedActors;
	
	// ������ Ÿ��
	ESlashType SlashType = ESlashType::EST_None;

public:	
	FORCEINLINE AActor* GetOwner() const { return Owner; }
	FORCEINLINE void SetOwner(AActor* NewOwner) { Owner = NewOwner; }

	FORCEINLINE float GetDamage() const { return Damage; }
	FORCEINLINE void SetDamage(const float& NewDamage) { Damage = NewDamage; }

	UFUNCTION()
	void OnOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FORCEINLINE void SetHitImpactEmitter(UParticleSystem* NewHitImpactEmitter) { HitImpactEmitter = NewHitImpactEmitter; }

	FORCEINLINE ESlashType GetSlashType() const { return SlashType; }
	void SetSlashType(const ESlashType& NewType);
};
