// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "GameStartLevel.generated.h"

class UMainMenu;


UCLASS()
class PORTFOLIO_API AGameStartLevel : public ALevelScriptActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	// 게임 시작 시 보여질 메인메뉴 창
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserWidget")
	TSubclassOf<UMainMenu> MainMenuClass;
};
