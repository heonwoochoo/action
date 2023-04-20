// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types/ItemTypes.h"
#include "ItemBase.generated.h"

class USphereComponent;
class UDataTable;


UCLASS()
class PORTFOLIO_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USphereComponent* CollisionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	UDataTable* ItemSpecData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	FName Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	FItemSpec Spec;

	// ������ ȹ�� �� ������ ��ƼŬ
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties|Particle")
	UParticleSystem* PickupParticle;

	// ȹ�� �� ������ ���� ��ȭ (�ִϸ��̼� ȿ��)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	UCurveFloat* PickupScaleCurve;

public:	
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE FName GetItemName() const { return Name; }
	FORCEINLINE FItemSpec GetItemSpec() const { return Spec; }
};
