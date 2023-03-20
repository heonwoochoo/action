// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageText.generated.h"

class UDamageWidgetComponent;

UCLASS()
class PORTFOLIO_API ADamageText : public AActor
{
	GENERATED_BODY()
	
public:	
	ADamageText();

	UFUNCTION()
	void Initialize(const float Damage);



protected:
	virtual void BeginPlay() override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDamageWidgetComponent* DamageWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "properties")
	float LifeSpanTime = 1.5f;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	FVector AnchorLocation;

public:
	FORCEINLINE FVector GetAnchorLocation() const { return AnchorLocation; }
};
