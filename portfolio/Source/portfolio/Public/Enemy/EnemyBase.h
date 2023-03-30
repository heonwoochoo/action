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
class UPawnSensingComponent;
class AAIController;

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

	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;

	/*
	* Navigation
	*/
	UPROPERTY()
	AAIController* EnemyController;

	// Current patrol target
	UPROPERTY(EditInstanceOnly, Category = "AI Navigation");
	AActor* PatrolTarget;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	TArray<AActor*> PatrolTargets;

	UPROPERTY(BlueprintReadOnly, Category = Combat)
	AActor* CombatTarget;

	UFUNCTION()
	void PawnSeen(APawn* SeenPawn);

	void ChaseTarget();

	bool CanAttack();

	UPROPERTY(EditAnywhere, Category = Combat)
	float ChasingWalkSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float PatrolWalkSpeed = 150.f;

	UPROPERTY(EditAnywhere)
	double PatrolRadius = 200.f;

	FTimerHandle PatrolTimer;

	void PatrolTimerFinished();

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMin = 5.f;
	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMax = 10.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	double AcceptanceRadius = 50.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	double CombatRadius = 1000.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	double AttackRadius = 150.f;

	FTimerHandle AttackTimer;

	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMin = 0.5f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMax = 1.f;

	

	void PlayAttackAnim();

	UFUNCTION(BlueprintCallable)
	void AttackCharacter();

	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	void StartAttackTimer();


	void MoveToTarget(AActor* Target);

	void CheckCombatTarget();

	void CheckPatrolTarget();

	bool InTargetRange(AActor* Target, double Radius);

	void ClearAttackTimer();

	void LoseInterest();

	void HideHealthBar();

	void ShowHealthBar();

	void StartPatrolling();

	AActor* ChoosePatrolTarget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTargetWidgetComponent* TargetWidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UEnemyHPBarWidgetComponent* HPBarWidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMotionWarpingComponent* MotionWarpingComponent;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void HandleAttackTarget(AController* EventInstigator);

	void HandleDamage(AActor* DamageCauser, float DamageAmount);

	// Hit react
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float KnockBackDistance = 30.f;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Properties")
	UDataTable* EnemyStatsDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Properties")
	FEnemyStats Stats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EEnemyState State = EEnemyState::EES_NoState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EEnemyName Name;

	AActor* HeadUpMark;

	void Die();

	FTimerHandle TakeDamageHandle;

	AActor* DamageCauserActor;

	void PlayHitAnimNextTick();
	void PlayHitAnim();

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
