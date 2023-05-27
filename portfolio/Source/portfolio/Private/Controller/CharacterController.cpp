// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/CharacterController.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "HUD/HUDBase.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

ACharacterController::ACharacterController()
{
	const FVector2D& ViewportSize = UWidgetLayoutLibrary::GetViewportSize(this);
	const FVector2D& ViewportCenter = FVector2D(ViewportSize.X * 0.5 / ViewportSize.Y * 0.5);

	CharacterInfoInitialLocation = ViewportCenter;
	InventoryInitialLocation = ViewportCenter;
	QuestInitialLocation = ViewportCenter;

	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void ACharacterController::SetInputModeToGame()
{
	SetShowMouseCursor(false);
	SetInputMode(FInputModeGameOnly());
	ResetIgnoreLookInput();
	ResetIgnoreMoveInput();

	// 가이드 메세지 숨김 처리
	AHUDBase* HUDBase = Cast<AHUDBase>(GetHUD());
	if (HUDBase)
	{
		HUDBase->HideGuideMessage();
	}

	OnChangedInputMode.Broadcast(EInputMode::EIM_Game);
}

void ACharacterController::SetInputModeToUI()
{
	SetShowMouseCursor(true);
	SetInputMode(FInputModeGameAndUI());
	SetIgnoreLookInput(true);
	SetIgnoreMoveInput(true);

	OnChangedInputMode.Broadcast(EInputMode::EIM_UI);
}

void ACharacterController::PlayBackgroundMusic(const EBackgroundMusic& Type)
{
	USoundCue* SelectedMusic = nullptr;

	switch (Type)
	{
	case EBackgroundMusic::EBM_OutsideCastle:
		SelectedMusic = OutsideCastleMusic;
		break;
	case EBackgroundMusic::EBM_InsideCastle:
		SelectedMusic = InsideCastleMusic;
		break;
	case EBackgroundMusic::EBM_CombatBoss:
		SelectedMusic = CombatBossMusic;
		break;
	default:
		SelectedMusic = OutsideCastleMusic;
	}

	if (SelectedMusic)
	{
		if (AudioComponent)
		{
			if (AudioComponent->IsPlaying())
			{
				AudioComponent->Stop();
			}
		}
		AudioComponent = UGameplayStatics::SpawnSound2D(this, SelectedMusic);
		NowPlayingMusic = Type;
	}
}