// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Overlay/ChatBoxMessage.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/TextBlock.h"

void UChatBoxMessage::NativeConstruct()
{
	// 출력시간은 현재 컴퓨터 시간으로 설정
	const FText& FormatText = GetFormatTimeText(UKismetMathLibrary::Now());
	if (TimeText)
	{
		TimeText->SetText(FormatText);
	}

}

FText UChatBoxMessage::GetFormatTimeText(const FDateTime& Time)
{
	const FString Hours =
		Time.GetHour() < 10 ? FString(TEXT("0")) + FString::FromInt(Time.GetHour()) : FString::FromInt(Time.GetHour());
	
	const FString Minutes =
		Time.GetMinute() < 10 ? FString(TEXT("0")) + FString::FromInt(Time.GetMinute()) : FString::FromInt(Time.GetMinute());
	
	const FString Seconds =
		Time.GetSecond() < 10 ? FString(TEXT("0")) + FString::FromInt(Time.GetSecond()) : FString::FromInt(Time.GetSecond());

	const FString CompleteText = FString(TEXT("[")) + Hours + FString(TEXT(":")) + Minutes + FString(TEXT(":")) + Seconds + FString(TEXT("]"));

	return FText::FromString(CompleteText);
}

void UChatBoxMessage::SetMessageText(const FText& Message)
{
	if (MessageText)
	{
		MessageText->SetText(Message);
	}
}

void UChatBoxMessage::SetTextColor(const FColor& Color)
{
	if (TimeText && MessageText)
	{
		TimeText->SetColorAndOpacity(Color);
		MessageText->SetColorAndOpacity(Color);
	}
}
