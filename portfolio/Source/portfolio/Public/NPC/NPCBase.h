// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Types/QuestTypes.h"
#include "NPCBase.generated.h"

class USphereComponent;
class UDataTable;

UCLASS()
class PORTFOLIO_API ANPCBase : public ACharacter
{
	GENERATED_BODY()

public:
	ANPCBase();    

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// 캐릭터와 대화를 나눌수 있는 공간
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComponent;
	
	// 모든 퀘스트 정보가 들어있는 데이터 파일
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDataTable* QuestData;

	// NPC가 소유하고 있는 퀘스트 목록
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSet<EQuestCode> QuestList;

	// 캐릭터가 가까이 있는지?
	// Sphere 충돌체에 오버랩시 true로 판단
	bool bIsNearPlayer = false;

	UFUNCTION()
	void BeginOverlappedSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlappedSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// 메쉬의 아웃라인을 노란색으로 표시 (플레이어 근접시 호출)
	void ChangeMeshOutline();

	// 아웃라인 제거
	void RemoveMeshOutline();

	// 퀘스트 코드를 참조하여 데이터를 반환
	FQuest* GetQuestData(const EQuestCode& InQuestCode);
};