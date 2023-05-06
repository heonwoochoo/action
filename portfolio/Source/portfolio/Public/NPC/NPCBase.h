// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPCBase.generated.h"

class USphereComponent;


UCLASS()
class PORTFOLIO_API ANPCBase : public ACharacter
{
	GENERATED_BODY()

public:
	ANPCBase();

protected:
	virtual void BeginPlay() override;

	// 캐릭터와 대화를 나눌수 있는 공간
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComponent;
	
	// 캐릭터가 가까이 있는지?
	// Sphere 충돌체에 오버랩시 true로 판단
	bool bIsNearPlayer = false;

	UFUNCTION()
	void BeginOverlappedSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlappedSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	virtual void Tick(float DeltaTime) override;

	// 피격시 메쉬의 아웃라인을 노란색으로 표시
	void ChangeMeshOutline();

	// 아웃라인 제거
	// 일정 시간동안 피격 없을 경우 또는 사망시 호출
	void RemoveMeshOutline();

};
