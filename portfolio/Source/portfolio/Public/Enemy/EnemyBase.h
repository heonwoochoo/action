// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyTypes.h"
#include "EnemyBase.generated.h"

class UEnemyDataAsset;
class UTargetWidgetComponent;
class UEnemyHPBarWidgetComponent;


UCLASS()
class PORTFOLIO_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTargetWidgetComponent* TargetWidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UEnemyHPBarWidgetComponent* HPBarWidgetComponent;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EEnemyState State = EEnemyState::EES_Unoccupied;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UEnemyDataAsset* DataAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EEnemyName Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FEnemyData EnemyData;

	float TargetDurationTime = 5.0f;
	FTimerHandle TargetTimerHandle;
	void TargetTimerEnd();

	void DisplayTargetWidget();

	

public:

	EEnemyState GetState() const;
	void SetState(EEnemyState NewState);

	void SetTargetImgVisibie(bool NewState);

	UFUNCTION()
	void OnBeginOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FORCEINLINE EEnemyName GetName() const { return Name; }
};
