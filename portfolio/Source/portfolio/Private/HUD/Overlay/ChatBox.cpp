// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Overlay/ChatBox.h"
#include "Components/ScrollBox.h"
#include "HUD/Overlay/ChatBoxMessage.h"
#include "Components/Image.h"
#include "Components/Button.h"

void UChatBox::NativeConstruct()
{
	InitMovingBar();

	if (ChatBackground && ChatMovingBar)
	{
		ChatBackground->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.5f));
		ChatMovingBar->SetBackgroundColor(FLinearColor(1.f, 1.f, 1.f, 0.f));
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
}

void UChatBox::OnReleasedMovingBar()
{
	if (ChatMovingBar)
	{
		ChatMovingBar->SetBackgroundColor(FLinearColor(1.f, 1.f, 1.f, 1.f));
	}
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
