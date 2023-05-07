// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Text3DActor.h"
#include "Text3DMark.generated.h"

class UMaterial;

enum class ETextMaterialColor : uint8
{
	ETMC_Blue UMETA(DisplayName = "Blue"),
	ETMC_Grey UMETA(DisplayName = "Grey"),
	ETMC_Yellow UMETA(DisplayName = "Yellow"),
	ETMC_None UMETA(DisplayName = "None"),
};

UCLASS()
class PORTFOLIO_API AText3DMark : public AText3DActor
{
	GENERATED_BODY()
	
public:
	AText3DMark();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	UMaterial* BlueColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	UMaterial* GreyColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	UMaterial* YellowColor;


public:
	// 텍스트를 선택된 컬러의 머리티얼로 변경
	void SetTextColor(const ETextMaterialColor& MaterialColor);

	// 오너 액터의 머리 위에 위치 시킴
	void SetLocationOwnerHeadup();

	// 텍스트 컴포넌트의 텍스트를 변경
	void SetText(const FText& InText);
};