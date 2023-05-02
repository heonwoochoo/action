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
	// 넘길 때 버튼 소리
	UPROPERTY(EditDefaultsOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	USoundCue* ChangeButtonClickSound;

	// 확인 버튼 소리
	UPROPERTY(EditDefaultsOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	USoundCue* CheckButtonClickSound;

	// 아이템 클릭 소리
	UPROPERTY(EditDefaultsOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	USoundCue* ItemClickSound;

public:
	void PlayChangeButtonClickSound();
	void PlayCheckButtonClickSound();
	void PlayItemClickSound();
};



