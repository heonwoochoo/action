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

	// �ѱ� �� ��ư �Ҹ�
	UPROPERTY(EditDefaultsOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	USoundCue* ClickSound1;

	UPROPERTY(EditDefaultsOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	// Ȯ�� ��ư �Ҹ�
	USoundCue* ClickSound2;

public:
	void PlayClickSound1();
	void PlayClickSound2();
};



