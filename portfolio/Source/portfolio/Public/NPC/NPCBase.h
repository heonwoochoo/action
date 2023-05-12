// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPCBase.generated.h"

class USphereComponent;
class UDataTable;
class UTextRenderComponent;
class ADefaultCharacter;

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

	// 캐릭터의 이름을 나타내는 텍스트 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UTextRenderComponent* NameTextComponent;

	// NPC 이름
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name;

	// 근접한 플레이어 (오버랩 시 저장)
	ADefaultCharacter* NearPlayer;

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

	// 이름 설정
	void SetName();

	// 이름을 플레이어의 카메라 방향으로 보여줍니다.
	void RotateNameToPlayer(ADefaultCharacter* InPlayer);

	FORCEINLINE ADefaultCharacter* GetNearPlayer() const { return NearPlayer; }
	FORCEINLINE void SetNearPlayer(ADefaultCharacter* InNearPlayer) { NearPlayer = InNearPlayer; }
};