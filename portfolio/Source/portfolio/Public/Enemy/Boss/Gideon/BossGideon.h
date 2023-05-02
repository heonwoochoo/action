// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Boss/BossBase.h"
#include "BossGideon.generated.h"

class ADarkStone;
class ADarkWave;
class ADarkSword;
class UBossAbilityComponent;

/**
 * < 공격 패턴 >
 * 등장 -> 추격 -> (사거리 도달시) 공격 -> 휴식 -> 추격 -> 공격 ...
 */
UCLASS()
class PORTFOLIO_API ABossGideon : public ABossBase
{
	GENERATED_BODY()
	
public:
	ABossGideon();

protected:
	virtual void BeginPlay() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// 스킬이 구현되어있는 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBossAbilityComponent* AbilityComponent;



public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UBossAbilityComponent* GetAbilityComponent() const { return AbilityComponent; };

	virtual void Die() override;
};
