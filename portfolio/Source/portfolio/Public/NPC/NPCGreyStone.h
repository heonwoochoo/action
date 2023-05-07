// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC/NPCBase.h"
#include "NPCGreyStone.generated.h"

class AText3DMark;
class UQuestServerComponent;

UCLASS()
class PORTFOLIO_API ANPCGreyStone : public ANPCBase
{
	GENERATED_BODY()
	
public:
	ANPCGreyStone();
	
protected:
	virtual void BeginPlay() override;

	// 퀘스트 제공자
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UQuestServerComponent* QuestServerComponent;

	// 머리 위에 생성할 수 있는 3D 텍스트 (? , ! 아이콘으로 사용됨)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AText3DMark> Text3DMarkClass;

	// 생성된 3D 텍스트의 인스턴스
	AText3DMark* Text3DMark;
};
