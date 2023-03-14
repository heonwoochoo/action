// Copyright Epic Games, Inc. All Rights Reserved.

#include "portfolioGameMode.h"
#include "portfolioCharacter.h"
#include "UObject/ConstructorHelpers.h"

AportfolioGameMode::AportfolioGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
}
