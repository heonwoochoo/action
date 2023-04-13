// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DefaultGameMode.generated.h"

class AEnemyBase;
class USoundCue;

UCLASS(minimalapi)
class ADefaultGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	ADefaultGameMode();

private:

	// 넘길 때 버튼 소리
	UPROPERTY(EditDefaultsOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	USoundCue* ClickSound1;

	UPROPERTY(EditDefaultsOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	// 확인 버튼 소리
	USoundCue* ClickSound2;

public:
	void PlayClickSound1();
	void PlayClickSound2();
};



