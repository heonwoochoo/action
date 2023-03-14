// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/AbilityComponent.h"
#include "Data/CharacterDataAsset.h"

// Sets default values for this component's properties
UAbilityComponent::UAbilityComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

	
}


// Called when the game starts
void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	if (CharacterDataAssetClass)
	{
		
	}
	
}

void UAbilityComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (CharacterDataAssetClass)
	{
		CharacterData = Cast<UCharacterDataAsset>(CharacterDataAssetClass->GetDefaultObject())->CharacterData;
	}
}


// Called every frame
void UAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

