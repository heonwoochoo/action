// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestSelectBox.generated.h"

class UCanvasPanel;
class UVerticalBox;
class UQuestSelectBoxList;
class UQuestServerComponent;

UCLASS()
class PORTFOLIO_API UQuestSelectBox : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* InnerCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UVerticalBox* QuestListBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UQuestSelectBoxList> QuestSelectBoxListClass;

	// 해당 위젯을 생성한 오너 객체
	AActor* Owner;

public:
	// 컴포넌트 정보를 참조하여 리스트를 초기화시킵니다.
	void Init(UQuestServerComponent* QuestServerComponent);

	// 화면 상에 보일 위치를 조정합니다
	void SetLocation(const FVector2D& InVector2D);

	FORCEINLINE AActor* GetOwner() const { return Owner; }
	FORCEINLINE void SetOwner(AActor* InOwner) { Owner = InOwner; }
};