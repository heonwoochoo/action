// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gold.generated.h"

class UParticleSystemComponent;

UCLASS()
class PORTFOLIO_API AGold : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGold();

protected:
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UParticleSystemComponent* ParticleComponent;
private:
	int32 Value = 10;

public:
	FORCEINLINE int32 GetValue() const { return Value; }
	FORCEINLINE void SetValue(const int32 InValue) { Value = InValue; }
};