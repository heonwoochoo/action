// Fill out your copyright notice in the Description page of Project Settings.


#include "HelperFunction.h"
#include "Kismet/KismetMathLibrary.h"

float UHelperFunction::GetRandomDamage(float Damge)
{
	float RandDamage = UKismetMathLibrary::RandomFloatInRange(Damge * 0.8f, Damge * 1.2f);
	return RandDamage;
}