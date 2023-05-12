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

	// ��ȭâ ���� Ŭ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UDialogueBox> DialogueBoxClass;

	// ������ ��ȭâ ����
	UDialogueBox* DialogueBox;

public:	
	void OpenDialogueBox(const TArray<FText>& InDialogueText);
		
};
