// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/AbilityComponent.h"
#include "Data/CharacterDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "portfolio/portfolioCharacter.h"

// Sets default values for this component's properties
UAbilityComponent::UAbilityComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

	if (AportfolioCharacter* Character = Cast<AportfolioCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
	{
		CharacterData = Character->GetCharacterDataAsset()->CharacterData;
	}
}


// Called when the game starts
void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();
}

const FCharacterData UAbilityComponent::GetCharacterData()
{
	return CharacterData;
}


// Called every frame
void UAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

