// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DarkSword.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UParticleSystem;
class USoundCue;
class UCurveFloat;


UCLASS()
class PORTFOLIO_API ADarkSword : public AActor
{
	GENERATED_BODY()
	
public:	
	ADarkSword();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// 물체에 막히는 충돌체
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereCollision;

	// 오버랩되어 데미지가 들어갈 메쉬
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMeshComponent;

	// 투사체의 속성을 설정
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* ParticleComponent;

	// 타겟을 맞힐 경우 생성될 파티클
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UParticleSystem* HitImpactParticle;

	// 벽에 막혔을 때 생성될 파티클
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UParticleSystem* NoHitParticle;

	// 투사체 꼬리의 트레일
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UParticleSystem* TrailParticle;

	// 날라가기 전 타겟 근처의 바닥에 생성될 원형 룬
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UParticleSystem* CircleRuneParticle;

	// 오브젝트 생성 직후 적용될 머티리얼의 마스크값
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCurveFloat* MaskCurveFloat;

	// 타겟을 향해 회전시 참조되는 Lerp()의 알파값
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCurveFloat* AlphaCurveFloat;

	// 타격 소리
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundCue* HitSound;

	// 날라갈 때 소리
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundCue* ThrowSound;

private:
	// 객체를 스폰한 소유자
	AActor* Owner;

	// 목표 타겟
	AActor* Target;

	// 목표 위치
	FVector ProjectileTargetLocation;

	float Damage = 0.f;

	// 생성 후 경과시간
	float ElapsedTime = 0.f;

	// 생성 후 마스크 값이 최대에 도달했는지?
	bool bIsMaskMax = false;

	// 목표 타겟으로 회전이 끝났는지
	bool bIsRotationEnd = false;

public:
	FORCEINLINE void SetTarget(AActor* InTarget) { Target = InTarget; }
	FORCEINLINE void SetDamage(const float& InDamage) { Damage = InDamage; }
	FORCEINLINE void SetOwner(AActor* NewOwner) { Owner = NewOwner; }

};
