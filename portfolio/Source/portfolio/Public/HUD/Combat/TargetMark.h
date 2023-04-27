// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetMark.generated.h"

class UTargetWidgetComponent;

UCLASS()
class PORTFOLIO_API ATargetMark : public AActor
{
	GENERATED_BODY()
	
public:	

	ATargetMark();

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UTargetWidgetComponent* TargetWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Duration = 5.0f;

public:
	virtual void Tick(float DeltaTime) override;

	void SetDurtation(float Time);
};
