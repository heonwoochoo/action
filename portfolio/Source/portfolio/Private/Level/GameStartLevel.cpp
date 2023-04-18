// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/GameStartLevel.h"
#include "HUD/Menu/MainMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void AGameStartLevel::BeginPlay()
{
	Super::BeginPlay();
	
	ShowMainMenu();
	PlayGameStartMusic();
}

void AGameStartLevel::ShowMainMenu()
{
	if (MainMenuClass)
	{
		UMainMenu* MainMenu = Cast<UMainMenu>(CreateWidget(GetWorld(), MainMenuClass));
		if (MainMenu)
		{
			MainMenu->AddToViewport();

			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
			if (PlayerController)
			{
				PlayerController->SetInputMode(FInputModeUIOnly());
				PlayerController->SetShowMouseCursor(true);
			}
		}
	}
}

void AGameStartLevel::PlayGameStartMusic()
{
	if (GameStartMusic)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), GameStartMusic);
	}
}
