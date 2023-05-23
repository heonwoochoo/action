// Fill out your copyright notice in the Description page of Project Settings.


#include "Physics/PhysicalMaterialBase.h"
#include "Engine/DataTable.h"

UPhysicalMaterialBase::UPhysicalMaterialBase()
{
	
}

UNiagaraSystem* UPhysicalMaterialBase::GetMovementEmitter(const EMovementType& MovementType) const
{
	const UEnum* SurfaceEnum = FindObject<UEnum>(nullptr, TEXT("/Script/portfolio.ESurfaceType"));
	if (SurfaceType)
	{
		const FName& SurfaceName = FName(SurfaceEnum->GetDisplayNameTextByValue((int64)Surface).ToString());
		if (SurfaceName.IsValid() && MovementEmitterDataTable)
		{
			const FMovementEmitter* MovementEmitter = MovementEmitterDataTable->FindRow<FMovementEmitter>(SurfaceName, "");
			if (MovementEmitter)
			{
				UNiagaraSystem* Selected{};
				switch (MovementType)
				{
				case EMovementType::EMT_Walk:
					Selected = MovementEmitter->Walk;
				case EMovementType::EMT_Run:
					Selected = MovementEmitter->Run;
				case EMovementType::EMT_Sprint:
					Selected = MovementEmitter->Sprint;
				case EMovementType::EMT_Roll:
					Selected = MovementEmitter->Roll;
				case EMovementType::EMT_Rush:
					Selected = MovementEmitter->Rush;
				case EMovementType::EMT_Jump:
					Selected = MovementEmitter->Jump;
				case EMovementType::EMT_Land:
					Selected = MovementEmitter->Land;
				default:
					Selected = MovementEmitter->Walk;
				}
				return Selected;
			}
		}
	}
	return nullptr;
}

USoundCue* UPhysicalMaterialBase::GetMovementSound(const EMovementType& MovementType) const
{
	const UEnum* SurfaceEnum = FindObject<UEnum>(nullptr, TEXT("/Script/portfolio.ESurfaceType"));
	if (SurfaceType)
	{
		const FName& SurfaceName = FName(SurfaceEnum->GetDisplayNameTextByValue((int64)Surface).ToString());
		if (SurfaceName.IsValid() && MovementSoundDataTable)
		{
			const FMovementSound* MovementSound = MovementSoundDataTable->FindRow<FMovementSound>(SurfaceName, "");
			if (MovementSound)
			{
				USoundCue* Selected{};
				switch (MovementType)
				{
				case EMovementType::EMT_Walk:
					Selected = MovementSound->Walk;
				case EMovementType::EMT_Run:
					Selected = MovementSound->Run;
				case EMovementType::EMT_Sprint:
					Selected = MovementSound->Sprint;
				case EMovementType::EMT_Roll:
					Selected = MovementSound->Roll;
				case EMovementType::EMT_Rush:
					Selected = MovementSound->Rush;
				case EMovementType::EMT_Jump:
					Selected = MovementSound->Jump;
				case EMovementType::EMT_Land:
					Selected = MovementSound->Land;
				default:
					Selected = MovementSound->Walk;
				}
				return Selected;
			}
		}
	}
	return nullptr;
}
