// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC/NPCBase.h"
#include "Types/SettingTypes.h"
#include "NPCGreyStone.generated.h"

class AText3DMark;
class UQuestServerComponent;
class UMaterialInstance;
class UQuestSelectBox;
class UNPCDialogueComponent;
class ADefaultCharacter;

UCLASS()
class PORTFOLIO_API ANPCGreyStone : public ANPCBase
{
	GENERATED_BODY()
	
public:
	ANPCGreyStone();
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void BeginOverlappedSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void EndOverlappedSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	
	// 퀘스트 제공자
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UQuestServerComponent* QuestServerComponent;

	// 다이얼로그 관리 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UNPCDialogueComponent* DialogueComponent;

	// 머리 위에 생성할 수 있는 3D 텍스트 (? , ! 아이콘으로 사용됨)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget")
	TSubclassOf<AText3DMark> Text3DMarkClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget")
	TSubclassOf<UQuestSelectBox> QuestBoxClass;

	UQuestSelectBox* QuestBox;

	// 생성된 3D 텍스트의 인스턴스
	AText3DMark* Text3DMark;

public:
	FORCEINLINE UQuestServerComponent* GetQuestServerComponent() const { return QuestServerComponent; }
	FORCEINLINE UQuestSelectBox* GetQuestBox() const { return QuestBox; }

	UFUNCTION()
	void OnChangedInputMode(const EInputMode& InMode);

	UFUNCTION()
	void OnSelectedQuest(const EQuestCode& SelectedCode);

	void TalkWithPlayer(ADefaultCharacter* PlayerCharacter);
};