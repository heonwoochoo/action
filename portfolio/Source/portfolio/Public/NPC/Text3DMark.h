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

/**
* NPC 머리 위에 퀘스트 상태를 표시해주는 마크
* 표시 우선 순위는
* 1. 완료한 퀘스트가 존재 -> 느낌표 노란색
* 2. 진행 할 수 있는 퀘스트가 존재 -> 물음표 파란색
* 3. 진행중인 퀘스트만 존재 -> 물음표 회색
*/

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

	// 퀘스트 상태를 확인하여 그에 맞는 텍스트 마크로 바꿉니다.
	void Update();
};