// Fill out your copyright notice in the Description page of Project Settings.


#include "HelperFunction.h"
#include "Kismet/KismetMathLibrary.h"

float UHelperFunction::GetRandomDamage(float Damge, float Critical)
{
	float RandDamage = UKismetMathLibrary::RandomFloatInRange(Damge * 0.8f, Damge * 1.2f);

	float RandFloat = UKismetMathLibrary::RandomFloat();

	if (RandFloat < Critical * 0.01f) return RandDamage * 1.5f;
	else return RandDamage;
}
