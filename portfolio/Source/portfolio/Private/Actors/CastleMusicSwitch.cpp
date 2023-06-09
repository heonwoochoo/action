﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CastleMusicSwitch.h"
#include "Components/BoxComponent.h"
#include "DefaultCharacter.h"
#include "Controller/CharacterController.h"
#include "HUD/HUDBase.h"
#include "Component/QuestClientComponent.h"
#include "Level/DefaultWorldLevel.h"

ACastleMusicSwitch::ACastleMusicSwitch()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetGenerateOverlapEvents(true);
}

void ACastleMusicSwitch::BeginPlay()
{
	Super::BeginPlay();
	
	if (BoxComponent)
	{
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACastleMusicSwitch::OnBeginOverlapped);
	}


}

void ACastleMusicSwitch::OnBeginOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName("Player")) && !bIsCombatBossMode)
	{
		ADefaultCharacter* PlayerCharacter = Cast<ADefaultCharacter>(OtherActor);
		if (PlayerCharacter)
		{
			ACharacterController* CharacterController = Cast<ACharacterController>(PlayerCharacter->GetController());
			if (CharacterController)
			{
				if (MusicType != EBackgroundMusic::EBM_None)
				{
					// 현재 재생되고 있는 음악과의 중복을 검사
					const EBackgroundMusic& NowPlaying = CharacterController->GetNowPlayingMusic();
					if (NowPlaying != MusicType)
					{
						CharacterController->PlayBackgroundMusic(MusicType);

						AHUDBase* HUDBase = Cast<AHUDBase>(CharacterController->GetHUD());
						if (HUDBase)
						{
							FText SpotName{};
							if (MusicType == EBackgroundMusic::EBM_InsideCastle)
							{
								SpotName = FText::FromString(TEXT("조폭의 요새"));

								UQuestClientComponent* QuestClientComponent = PlayerCharacter->GetQuestClientComponent();
								if (QuestClientComponent)
								{
									const TArray<FQuestClientData>& QuestList = QuestClientComponent->GetQuestList();
									for (const auto& QuestData : QuestList)
									{
										if (QuestData.QuestCode == EQuestCode::EQC_0002)
										{
											
											ALevelScriptActor* CurrentWorldLevel = GetWorld()->GetLevelScriptActor();
											if (CurrentWorldLevel)
											{
												ADefaultWorldLevel* DefaultWorldLevel = Cast<ADefaultWorldLevel>(CurrentWorldLevel);
												if (DefaultWorldLevel)
												{
													DefaultWorldLevel->RemoveAllEnemies();

													DefaultWorldLevel->SpawnBoss();
																							
													// 보스 음악 재생
													CharacterController->PlayBackgroundMusic(EBackgroundMusic::EBM_CombatBoss);

													bIsCombatBossMode = true;
												}
											}
											// 캐릭터 탈출못하게 투명벽
										}
									}
								}
							}
							else if (MusicType == EBackgroundMusic::EBM_OutsideCastle)
							{
								SpotName = FText::FromString(TEXT("태초마을"));
							}
							HUDBase->ShowSpotName(SpotName);
						}
					}
				}
			}
		}
	}
}