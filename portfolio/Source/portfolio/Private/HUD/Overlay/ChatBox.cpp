// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Overlay/ChatBox.h"
#include "Components/ScrollBox.h"
#include "HUD/Overlay/ChatBoxMessage.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GameplayStatics.h"
#include "DefaultCharacter.h"

void UChatBox::NativeConstruct()
{
	Super::NativeConstruct();

	InitMovingBar();

	if (ChatBackground && ChatMovingBar)
	{
		ChatBackground->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.5f));
		ChatMovingBar->SetBackgroundColor(FLinearColor(1.f, 1.f, 1.f, 0.f));
	}
}

void UChatBox::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// MovingBar 드래그 시 위치 조정
	if (bCanMovable && ChatBackground && ChatScrollBox && ChatMovingBar)
	{
		UCanvasPanelSlot* BackgroundSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(ChatBackground);
		UCanvasPanelSlot* ScrollBoxSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(ChatScrollBox);
		UCanvasPanelSlot* MovingBarSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(ChatMovingBar);
		if (BackgroundSlot && ScrollBoxSlot && MovingBarSlot)
		{
			const FVector2D& MouseLocation = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
			const float NewX = MouseLocation.X - OffsetX;
			const float NewY = MouseLocation.Y - OffsetY;
			
			BackgroundSlot->SetPosition(FVector2D(NewX, NewY));
			ScrollBoxSlot->SetPosition(FVector2D(NewX, NewY));
			MovingBarSlot->SetPosition(FVector2D(NewX, NewY));
		}
	}
}

void UChatBox::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (ChatBackground && ChatMovingBar)
	{
		ChatBackground->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
		ChatMovingBar->SetBackgroundColor(FLinearColor(1.f, 1.f, 1.f, 1.f));
	}
}

void UChatBox::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	if (ChatBackground && ChatMovingBar)
	{
		ChatBackground->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.5f));
		ChatMovingBar->SetBackgroundColor(FLinearColor(1.f, 1.f, 1.f, 0.f));
	}
}

void UChatBox::OnPressedMovingBar()
{
	if (ChatMovingBar)
	{
		ChatMovingBar->SetBackgroundColor(FLinearColor(0.3f, 0.3f, 0.3f, 1.f));
	}

	bCanMovable = true;

	// 마우스와 캔버스의 간격 저장
	UCanvasPanelSlot* MovingBarPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(ChatMovingBar);
	if (MovingBarPanelSlot)
	{
		const FVector2D& CanvasLocation = MovingBarPanelSlot->GetPosition();
		const FVector2D& MouseLocation = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
		OffsetX = MouseLocation.X - CanvasLocation.X;
		OffsetY = MouseLocation.Y - CanvasLocation.Y;
	}

}

void UChatBox::OnReleasedMovingBar()
{
	if (ChatMovingBar)
	{
		ChatMovingBar->SetBackgroundColor(FLinearColor(1.f, 1.f, 1.f, 1.f));
	}
	bCanMovable = false;
}

void UChatBox::ShowLevelUpText(const int32& NewLevel)
{
	const FString Message = FString(TEXT("캐릭터가 ")) + FString::FromInt(NewLevel) + FString(TEXT("레벨이 되었습니다."));
	PrintMessageOnChat(FText::FromString(Message), FColor::Yellow);
}

void UChatBox::ShowItemUsed(const FName& ItemCode, const FItemSpec& Spec)
{
	const FString& ItemName = Spec.Name.ToString();
	const FString Message = ItemName + FString(TEXT(" 소모품을 사용하였습니다."));
	PrintMessageOnChat(FText::FromString(Message), FColor::Silver);
}

void UChatBox::ShowItemAdded(const FName& ItemCode, const FItemSpec& Spec)
{
	const FString& ItemName = Spec.Name.ToString();
	const FString Message = ItemName + FString(TEXT(" 아이템을 획득하였습니다."));
	PrintMessageOnChat(FText::FromString(Message), FColor::Yellow);
}

void UChatBox::ShowItemEquipped(const FName& ItemCode, const FItemSpec& Spec)
{
	const FString& ItemName = Spec.Name.ToString();
	const FString Message = ItemName + FString(TEXT(" 장비를 착용하였습니다."));
	PrintMessageOnChat(FText::FromString(Message), FColor::Silver);
}

void UChatBox::InitMovingBar()
{
	ChatMovingBar->OnPressed.AddDynamic(this, &UChatBox::OnPressedMovingBar);
	ChatMovingBar->OnReleased.AddDynamic(this, &UChatBox::OnReleasedMovingBar);
}

void UChatBox::PrintMessageOnChat(const FText& Message, const FColor& Color)
{
	if (ChatBoxMessageClass && ChatScrollBox)
	{
		if (ChatScrollBox->GetChildrenCount() >= MaxLineNumber)
		{
			ChatScrollBox->RemoveChildAt(0);
		}

		UChatBoxMessage* MessageWidget = Cast<UChatBoxMessage>(CreateWidget(this, ChatBoxMessageClass));
		if (MessageWidget)
		{
			MessageWidget->SetMessageText(Message);
			MessageWidget->SetTextColor(Color);
			ChatScrollBox->AddChild(MessageWidget);
		}
	}
}
