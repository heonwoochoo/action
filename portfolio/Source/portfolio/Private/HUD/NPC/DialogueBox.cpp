// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/NPC/DialogueBox.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/DefaultGameMode.h"
#include "Component/NPCDialogueComponent.h"

void UDialogueBox::NativeConstruct()
{
	Super::NativeConstruct();

	InitCloseButton();
	InitPrevButton();
	InitNextButton();
}

void UDialogueBox::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (DialogueComponent)
	{
		// 현재 페이지
		int32 CurrentPage = DialogueComponent->GetCurrentPage();

		// 마지막 페이지
		int32 LastPage = DialogueComponent->GetLastPage();

		if (CurrentPage == 0)
		{
			DeactivatePrevButton();
		}
		else if (CurrentPage > 0)
		{
			ActivatePrevButton();
		}

		if (CurrentPage == LastPage)
		{
			ChangeNextButtonToAccept();
		}
		else if (CurrentPage < LastPage)
		{
			ChangeAcceptButtonToNext();
		}
	}
}

void UDialogueBox::OnHoveredCloseButton()
{
	if (CloseButtonImage && ActivatedButtonImage)
	{
		CloseButtonImage->SetBrushFromTexture(ActivatedButtonImage);
	}
}

void UDialogueBox::OnUnhoveredCloseButton()
{
	if (CloseButtonImage && DeactivatedButtonImage)
	{
		CloseButtonImage->SetBrushFromTexture(DeactivatedButtonImage);
	}
}

void UDialogueBox::OnClickedCloseButton()
{
	// 효과음
	ADefaultGameMode* DefaultGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this));
	if (DefaultGameMode)
	{
		DefaultGameMode->PlayChangeButtonClickSound();
	}

	// 다이얼로그 닫기
	RemoveFromParent();
}

void UDialogueBox::OnHoveredPrevButton()
{
	if (PrevButtonImage && ActivatedButtonImage)
	{
		PrevButtonImage->SetBrushFromTexture(ActivatedButtonImage);
	}
}

void UDialogueBox::OnUnhoveredPrevButton()
{
	if (PrevButtonImage && DeactivatedButtonImage)
	{
		PrevButtonImage->SetBrushFromTexture(DeactivatedButtonImage);
	}
}

void UDialogueBox::OnClickedPrevButton()
{
	// 이전 페이지 이동
	if (DialogueComponent)
	{
		DialogueComponent->ReadPrevPage();
	}

	// 효과음
	ADefaultGameMode* DefaultGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this));
	if (DefaultGameMode)
	{
		DefaultGameMode->PlayChangeButtonClickSound();
	}
}

void UDialogueBox::OnHoveredNextButton()
{
	if (NextButtonImage && ActivatedButtonImage)
	{
		NextButtonImage->SetBrushFromTexture(ActivatedButtonImage);
	}
}

void UDialogueBox::OnUnhoveredNextButton()
{
	if (NextButtonImage && DeactivatedButtonImage)
	{
		NextButtonImage->SetBrushFromTexture(DeactivatedButtonImage);
	}
}

void UDialogueBox::OnClickedNextButton()
{
	// 다음 페이지 이동
	if (DialogueComponent)
	{
		DialogueComponent->ReadNextPage();
	}

	// 효과음
	ADefaultGameMode* DefaultGameMode = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this));
	if (DefaultGameMode)
	{
		DefaultGameMode->PlayChangeButtonClickSound();
	}
}

void UDialogueBox::InitCloseButton()
{
	if (CloseButton)
	{
		CloseButton->OnHovered.AddDynamic(this, &UDialogueBox::OnHoveredCloseButton);
		CloseButton->OnUnhovered.AddDynamic(this, &UDialogueBox::OnUnhoveredCloseButton);
		CloseButton->OnClicked.AddDynamic(this, &UDialogueBox::OnClickedCloseButton);
	}
	if (CloseButtonImage && DeactivatedButtonImage)
	{
		CloseButtonImage->SetBrushFromTexture(DeactivatedButtonImage);
	}
}

void UDialogueBox::InitPrevButton()
{
	if (PrevButton)
	{
		PrevButton->OnHovered.AddDynamic(this, &UDialogueBox::OnHoveredPrevButton);
		PrevButton->OnUnhovered.AddDynamic(this, &UDialogueBox::OnUnhoveredPrevButton);
		PrevButton->OnClicked.AddDynamic(this, &UDialogueBox::OnClickedPrevButton);
	}
	if (PrevButtonImage && DeactivatedButtonImage)
	{
		PrevButtonImage->SetBrushFromTexture(DeactivatedButtonImage);
	}
}

void UDialogueBox::InitNextButton()
{
	if (NextButton)
	{
		NextButton->OnHovered.AddDynamic(this, &UDialogueBox::OnHoveredNextButton);
		NextButton->OnUnhovered.AddDynamic(this, &UDialogueBox::OnUnhoveredNextButton);
		NextButton->OnClicked.AddDynamic(this, &UDialogueBox::OnClickedNextButton);
	}
	if (NextButtonImage && DeactivatedButtonImage)
	{
		NextButtonImage->SetBrushFromTexture(DeactivatedButtonImage);
	}
}

void UDialogueBox::OnChangedInputMode(const EInputMode& NewMode)
{
	if (NewMode == EInputMode::EIM_Game)
	{
		RemoveFromParent();
	}
}

void UDialogueBox::SetDialogueText(const FText& InText)
{
	if (DialogueText)
	{
		DialogueText->SetText(InText);
	}
}

void UDialogueBox::DeactivatePrevButton()
{
	if (PrevButton)
	{
		PrevButton->SetIsEnabled(false);
	}
	if (PrevButtonImage)
	{
		PrevButtonImage->SetRenderOpacity(0.5f);
	}
}

void UDialogueBox::ActivatePrevButton()
{
	if (PrevButton)
	{
		PrevButton->SetIsEnabled(true);
	}
	if (PrevButtonImage)
	{
		PrevButtonImage->SetRenderOpacity(1.f);
	}
}

void UDialogueBox::ChangeNextButtonToAccept()
{
	if (NextText)
	{
		NextText->SetText(FText::FromString(TEXT("수락")));
	}
}

void UDialogueBox::ChangeAcceptButtonToNext()
{
	if (NextText)
	{
		NextText->SetText(FText::FromString(TEXT("다음")));
	}
}
