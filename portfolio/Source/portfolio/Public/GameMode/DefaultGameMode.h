// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "DefaultGameMode.generated.h"

class AEnemyBase;
class USoundCue;

UCLASS(minimalapi)
class ADefaultGameMode : public AGameMode
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
	USoundCue* ChangeButtonClickSound;

	// Ȯ�� ��ư �Ҹ�
	UPROPERTY(EditDefaultsOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	USoundCue* CheckButtonClickSound;

	// ������ Ŭ�� �Ҹ�
	UPROPERTY(EditDefaultsOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	USoundCue* ItemClickSound;

public:
	void PlayChangeButtonClickSound();
	void PlayCheckButtonClickSound();
	void PlayItemClickSound();
};



