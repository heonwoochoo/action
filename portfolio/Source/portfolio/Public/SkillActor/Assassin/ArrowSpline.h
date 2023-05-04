// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArrowSpline.generated.h"

class USplineComponent;
class UStaticMesh;
class ADefaultCharacter;

UCLASS()
class PORTFOLIO_API AArrowSpline : public AActor
{
	GENERATED_BODY()
	
public:	

	AArrowSpline();

protected:
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void Destroyed() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USplineComponent* SplineComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AActor> ArrowClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AActor> TargetCircleClass;

private:
	// 시전자
	ADefaultCharacter* Caster;

	// 목표 타겟
	AActor* Target;

	// 바닥에 그려진 화살표
	TArray<AActor*> Arrows;

	// 생성된 타겟 표식
	AActor* TargetCircle;

public:	
	FORCEINLINE void SetCaster(ADefaultCharacter* InCaster) { Caster = InCaster; }
	FORCEINLINE ADefaultCharacter* GetCaster() const { return Caster; }
	FORCEINLINE void SetTarget(AActor* InTarget) { Target = InTarget; }
	FORCEINLINE AActor* GetTarget() const { return Target; }

	// 캐스터와 타겟을 설정하고 스플라인을 그림
	void Init(ADefaultCharacter* InCaster, AActor* InTarget);

	// 타겟을 향하는 화살표 스플라인을 그림
	void DrawArrows();

	// 타겟에 서클 생성
	void DrawTargetCircle();

	// 화살표의 방향을 업데이트
	void UpdateArrows();

	// 타겟 표식이 바라보는 방향을 업데이트
	void UpdateTargetCircle();
};
