// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types/SettingTypes.h"
#include "CastleMusicSwitch.generated.h"

class UBoxComponent;

UCLASS()
class PORTFOLIO_API ACastleMusicSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	ACastleMusicSwitch();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Where")
	EBackgroundMusic MusicType = EBackgroundMusic::EBM_None;

	bool bIsCombatBossMode = false;

public:	
	UFUNCTION()
	void OnBeginOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
