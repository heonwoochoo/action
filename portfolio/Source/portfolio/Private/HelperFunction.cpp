// Fill out your copyright notice in the Description page of Project Settings.


#include "HelperFunction.h"
#include "Kismet/KismetMathLibrary.h"

float UHelperFunction::GetRandomDamage(float Damge)
{
	float RandDamage = UKismetMathLibrary::RandomFloatInRange(Damge * 0.8f, Damge * 1.2f);
	return RandDamage;
}

FName UHelperFunction::GetNameFromEnemyCode(const FName& InEnemyCode)
{
	if (InEnemyCode == FName(TEXT("4000")))
	{
		return FName(TEXT("조폭"));
	}
	else if (InEnemyCode == FName(TEXT("4001")))
	{
		return FName(TEXT("쫄병"));
	}
	else if (InEnemyCode == FName(TEXT("5000")))
	{
		return FName(TEXT("조폭두목"));
	}

	return FName();
}
