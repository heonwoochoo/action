// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemTypes.h"
#include "Potion.generated.h"

class USphereComponent;
class UDataTable;

UCLASS()
class PORTFOLIO_API APotion : public AActor
{
	GENERATED_BODY()
	
public:
	APotion();

	UPROPERTY(VisibleDefaultsOnly)
	USphereComponent* CollisionComponent;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	UDataTable* PotionDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	EItemName PotionName = EItemName::EIN_None;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
