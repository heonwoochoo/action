// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyTypes.h"
#include "EnemyBase.generated.h"

class UEnemyDataAsset;
class UTargetWidgetComponent;
class UEnemyHPBarWidgetComponent;
class UMotionWarpingComponent;
class ADamageText;

UCLASS()
class PORTFOLIO_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();
	virtual void Tick(float DeltaTime) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTargetWidgetComponent* TargetWidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UEnemyHPBarWidgetComponent* HPBarWidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMotionWarpingComponent* MotionWarpingComponent;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// Hit react
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float KnockBackDistance = 30.f;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Properties")
	UDataTable* EnemyStatsDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Properties")
	FEnemyStats Stats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EEnemyState State = EEnemyState::EES_Unoccupied;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EEnemyName Name;

	AActor* HeadUpMark;

	void Die();

public:
	FORCEINLINE FEnemyStats GetEnemyStats() const { return Stats; }
	FORCEINLINE UEnemyHPBarWidgetComponent* GetHPBarWidgetComponent() const { return HPBarWidgetComponent;}

	EEnemyState GetState() const;
	void SetState(EEnemyState NewState);

	void SetTargetImgVisibie(bool NewState);

	UFUNCTION()
	void OnBeginOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FORCEINLINE EEnemyName GetName() const { return Name; }

	UFUNCTION(BlueprintCallable)
	void HitRotationEnd();

	void UpdateHPBar();

	void SetHeadUpMark(AActor* NewMark);
	void RemoveMark();
};
