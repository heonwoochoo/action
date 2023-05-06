// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC/NPCBase.h"
#include "NPCGreyStone.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO_API ANPCGreyStone : public ANPCBase
{
	GENERATED_BODY()
	
public:
	ANPCGreyStone();
	
protected:
	virtual void BeginPlay() override;


};
