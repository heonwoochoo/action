// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/Text3DMark.h"
#include "Materials/Material.h"
#include "Text3DComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

AText3DMark::AText3DMark()
{
	 
}

void AText3DMark::SetTextColor(const ETextMaterialColor& MaterialColor)
{
	if (!BlueColor || !GreyColor || !YellowColor) return;
	
	UMaterial* Selected{};

	switch (MaterialColor)
	{
	case ETextMaterialColor::ETMC_Blue:
		Selected = BlueColor;
		break;
	case ETextMaterialColor::ETMC_Grey:
		Selected = GreyColor;
		break;
	case ETextMaterialColor::ETMC_Yellow:
		Selected = YellowColor;
		break;
	default:
		return;
	}

	if (Selected)
	{
		UText3DComponent* Text3DComponenet = GetText3DComponent();
		if (Text3DComponenet)
		{
			Text3DComponenet->SetFrontMaterial(Selected);
			Text3DComponenet->SetBevelMaterial(Selected);
			Text3DComponenet->SetExtrudeMaterial(Selected);
			Text3DComponenet->SetBackMaterial(Selected);
		}
	}
}

void AText3DMark::SetLocationOwnerHeadup()
{
	 ACharacter* Character = Cast<ACharacter>(GetOwner());
	 if (Character)
	 {
		 UCapsuleComponent* CapsuleComponenet = Character->GetCapsuleComponent();
		 if (CapsuleComponenet)
		 {
			const float& HalfHeight = CapsuleComponenet->GetScaledCapsuleHalfHeight();
			
			FVector Location = CapsuleComponenet->GetComponentLocation();
			Location.Z += HalfHeight + 50.f;

			SetActorLocation(Location);
		 }
	 }
}

void AText3DMark::SetText(const FText& InText)
{
	UText3DComponent* Text3DComponenet = GetText3DComponent();
	if (Text3DComponenet)
	{
		Text3DComponenet->SetText(InText);
	}
}