// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BossAbilityComponent.generated.h"

class ABossGideon;
class ADarkStone;
class ADarkWave;
class ADarkSword;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_API UBossAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBossAbilityComponent();

private:
	// 컴포넌트의 소유자
	ABossGideon* BossGideon;

protected:
	virtual void BeginPlay() override;

	// 기본 공격시 생성될 오브젝트의 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	TSubclassOf<ADarkStone> DarkStoneClass;

	// 스킬 1 사용시 생성될 오브젝트의 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	TSubclassOf<ADarkWave> DarkWaveClass;

	// 스킬 2 사용시 생성될 오브젝트의 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	TSubclassOf<ADarkSword> DarkSwordClass;

	// 스킬 2 DarkSword 오브젝트가 캐릭터 머리 위로 생성될 높이
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	float DarkSwordSpawnHeight = 300.f;

	// DarkSword의 좌우간격
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	float DarkSwordSideOffset = 300.f;

	// 회피 거리
	float StepOffset = 500.f;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// 기본 공격
	void Attack();
	// 회피
	void BackStep();
	// 스킬 1번
	void HandleSkillOne();
	// 스킬 2번
	void HandleSkillTwo();
	// 궁극기
	void HandleSkillThree();
	
	// 기본 공격 : 다크 스톤을 생성하여 날림
	UFUNCTION(BlueprintCallable)
	void SpawnDarkStone();

	// 스킬 1번 : 바닥에서 분출되는 빔을 3갈래로 생성
	UFUNCTION(BlueprintCallable)
	void SpawnDarkWave();

	// 스킬 2번 : 투검 생성
	UFUNCTION(BlueprintCallable)
	void SpawnDarkSword();
};
