// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NPCDialogueComponent.generated.h"

class UDialogueBox;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_API UNPCDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UNPCDialogueComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 대화창 위젯 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UDialogueBox> DialogueBoxClass;

	// 생성된 대화창 위젯
	UDialogueBox* DialogueBox;

public:	
	void OpenDialogueBox(const TArray<FText>& InDialogueText);
		
};
