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

	// 루트로 설정될 충돌체
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMeshComponent;

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

	// 땅에 박힌 후 머티리얼 Threshold의 변화값
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCurveFloat* AlphaCurveFloat;

	// 룬의 투명도 변화값
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCurveFloat* RuneOpacityCurveFloat;

	// 타격 소리
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundCue* HitSound;

	// 날라갈 때 소리
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundCue* ThrowSound;

	// 검이 날라가는 속도
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	float MoveSpeed = 2000.f;

	// 룬이 생성된 후 날라가기까지의 딜레이
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	float MoveDelayRate = 0.5f;

	// 충돌을 검사
	UFUNCTION()
	void OnHitCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// 메쉬와의 오버랩을 검사
	UFUNCTION()
	void OnOverlappedMesh(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	// 객체를 스폰한 소유자
	AActor* Owner;

	// 목표 타겟
	AActor* Target;

	// 날라갈 방향 벡터
	FVector ProjectileDirection;

	// 방향 설정 후 바닥에 생성된 룬
	UParticleSystemComponent* MagicCircle;

	// 룬의 투명도를 변화시킬 머티리얼
	UMaterialInstanceDynamic* CircleMaterialInstance;

	float Damage = 0.f;

	// 생성 후 경과시간
	float ElapsedTime = 0.f;

	// 생성 후 마스크 값이 최대에 도달했는지?
	bool bIsMaskMax = false;

	// 목표 타겟으로 회전이 끝났는지
	bool bIsRotationEnd = false;

	// ThresHold 알파값이 변화해도 되는 조건인지
	bool bCanChangeAlpha = false;

	FTimerHandle MoveTimerHandle;

	FTimerHandle AlphaTimerHandle;

	FTimerHandle RuneOpacityTimerHandle;

	// 투사체에 속도를 부여
	void ActivateProjectile();

	// 알파값의 변화가 끝나고 호출
	void OnEndThresHoldChange();

	// 룬의 투명도 변화가 끝나고 호출
	void OnEndRuneOpacityChange();



public:
	FORCEINLINE void SetTarget(AActor* InTarget) { Target = InTarget; }
	FORCEINLINE void SetDamage(const float& InDamage) { Damage = InDamage; }
	FORCEINLINE void SetOwner(AActor* NewOwner) { Owner = NewOwner; }

	// 투사체의 움직임에 관한 설정
	void MoveToTarget();

	// 타겟의 바닥에 룬 생성
	void SpawnCircleRune(const FVector& Location);

	// 메쉬의 마스크 변화 (최초 생성 직후)
	void ChangeMeshMask();

	// 타겟을 향해 회전
	void RotateMesh(float DeltaTime);

	// 충돌체에 블락된 후 Fade out 효과
	void ChangeMeshThresHold();

	// 룬 생성 직후 투명도 변화
	void ChangeRuneOpacity();

};
