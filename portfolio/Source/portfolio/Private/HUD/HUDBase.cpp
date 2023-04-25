// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/HUDBase.h"
#include "GameFramework/Character.h"
#include "HUD/DamageText.h"
#include "HUD/TargetMark.h"
#include "Components/CapsuleComponent.h"
#include "HUD/Overlay/InfoContainer.h"
#include "HUD/ComboCountWidget.h"
#include "HUD/ItemTooltipWidget.h"
#include "HUD/Menu/InGame/InGameMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Controller/CharacterController.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "HUD/Overlay/UserMessage.h"
#include "HUD/Overlay/ChatBox.h"

AHUDBase::AHUDBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHUDBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AHUDBase::BeginPlay()
{
	Super::BeginPlay();
}

void AHUDBase::InitInfoContainer()
{
	if (InfoContainerClass)
	{
		InfoContainer = Cast<UInfoContainer>(CreateWidget(GetOwningPlayerController(), InfoContainerClass));
		if (InfoContainer)
		{
			InfoContainer->AddToViewport();
		}
	}
}

void AHUDBase::InitComboCountWidget()
{
	if (ComboCountClass)
	{
		ComboCountWidget = Cast<UComboCountWidget>(CreateWidget(GetOwningPlayerController(), ComboCountClass));
		if (ComboCountWidget)
		{
			ComboCountWidget->AddToViewport();
			ComboCountWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void AHUDBase::InitUserMessage()
{
	if (UserMessageClass)
	{
		UserMessageWidget = Cast<UUserMessage>(CreateWidget(GetOwningPlayerController(), UserMessageClass));
		if (UserMessageWidget)
		{
			UserMessageWidget->AddToViewport();
		}
	}
}

void AHUDBase::InitChatBox()
{
	if (ChatBoxClass)
	{
		ChatBoxWidget = Cast<UChatBox>(CreateWidget(GetOwningPlayerController(), ChatBoxClass));
		if (ChatBoxWidget)
		{
			ChatBoxWidget->AddToViewport();
		}
	}
}

void AHUDBase::CloseAllInGameChildWidget()
{
	for (const auto& WidgetClass : InGameMenuChildWidgetClasses)
	{
		TArray<UUserWidget*> FoundWidget;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, FoundWidget, WidgetClass);
		if (FoundWidget.Num() >= 1)
		{
			for (auto Widget : FoundWidget)
			{
				Widget->RemoveFromParent();
			}
		}
	}
}

void AHUDBase::ShowDamageOnScreen(ACharacter* Actor, float Damage)
{
	if (DamageTextClass)
	{
		const FVector Location = Actor->GetActorLocation() + Actor->GetActorUpVector() * Actor->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		const FRotator Rotation = Actor->GetActorRotation();
		FActorSpawnParameters SpawnInfo;
		ADamageText* DamageText = GetWorld()->SpawnActor<ADamageText>(DamageTextClass, Location, Rotation, SpawnInfo);
		DamageText->Initialize(Damage);
	}
}

void AHUDBase::ShowTargetMark(ACharacter* Enemy, ACharacter* Caster)
{
	if (TargetMarkClass)
	{
		const FVector Location = Enemy->GetActorLocation() + Enemy->GetActorUpVector() * Enemy->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		const FRotator Rotation = Enemy->GetActorRotation();
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = Enemy;
		SpawnInfo.Instigator = Caster;
		ATargetMark* TargetMark = GetWorld()->SpawnActor<ATargetMark>(TargetMarkClass, Location, Rotation, SpawnInfo);
	}
}

void AHUDBase::ShowItemTooltip(const FName& ItemCode, const FVector2D& Location)
{
	if (ItemTooltipWidgetClass)
	{
		HideItemTooltip();

		if (ItemTooltipWidget)
		{
			ItemTooltipWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			ItemTooltipWidget = Cast<UItemTooltipWidget>(CreateWidget(GetOwningPlayerController(), ItemTooltipWidgetClass));
			ItemTooltipWidget->AddToViewport(-1);
		}
		ItemTooltipWidget->UpdateContents(ItemCode);
		ItemTooltipWidget->SetCanvasPosition(Location);
	}
}

void AHUDBase::HideItemTooltip()
{
	if (ItemTooltipWidget)
	{
		ItemTooltipWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AHUDBase::InitScreenOverlay()
{
	InitInfoContainer();
	InitComboCountWidget();
	InitUserMessage();
	InitChatBox();
}

void AHUDBase::OpenInGameMenu()
{
	if (InGameMenuClass)
	{
		InGameMenuWidget = Cast<UInGameMenu>(CreateWidget(GetWorld(), InGameMenuClass));
		if (InGameMenuWidget)
		{
			InGameMenuWidget->AddToViewport();

			ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
			if (CharacterController)
			{
				CharacterController->SetShowMouseCursor(true);
				CharacterController->SetInputMode(FInputModeGameAndUI());
				CharacterController->SetIgnoreLookInput(true);
				CharacterController->SetIgnoreMoveInput(true);
			}
		}
	}
}

void AHUDBase::CloseInGameMenu()
{
	if (InGameMenuWidget)
	{
		InGameMenuWidget->RemoveOpenedWidget();
		InGameMenuWidget->PlayHideAnimation();
	}

	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController)
	{
		CloseAllInGameChildWidget();
		CharacterController->SetShowMouseCursor(false);
		CharacterController->SetInputMode(FInputModeGameOnly());
		CharacterController->ResetIgnoreLookInput();
		CharacterController->ResetIgnoreMoveInput();
	}
}

void AHUDBase::SetInGameMenuChildWidgetClasses(const TArray<TSubclassOf<UUserWidget>>& Classes)
{
	InGameMenuChildWidgetClasses = Classes;
}

void AHUDBase::NotifyScreenMessage(const FText& Message)
{
	if (UserMessageWidget)
	{
		UserMessageWidget->NotifyMessageToUser(Message);
	}
}

void AHUDBase::HandleMessageOnChat(const FText& Message, const FColor& Color)
{
	if (ChatBoxWidget)
	{
		ChatBoxWidget->PrintMessageOnChat(Message, Color);
	}
}
