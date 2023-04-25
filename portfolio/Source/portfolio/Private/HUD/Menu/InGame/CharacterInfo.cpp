// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Menu/InGame/CharacterInfo.h"
#include "HUD/Menu/InGame/EquipmentSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CanvasPanel.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Controller/CharacterController.h"
#include "DefaultCharacter.h"
#include "GameInstance/DefaultGameInstance.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "HUD/HUDBase.h"



void UCharacterInfo::NativeConstruct()
{
	Super::NativeConstruct();

	EquipmentSlots = { HelmetSlot, ArmourSlot, WeaponSlot, SubWeaponSlot, ShieldSlot, AccessorySlot, ShoesSlot };

	InitEquipmentSlot();
	InitCanvasLocation();
	UpdateStats();
}

void UCharacterInfo::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	
	if (DefaultCharacter)
	{
		const FCharacterStats& Stats = DefaultCharacter->GetCharacterStats();
		if (Stats.HP != Stats.HPMax)
		{
			UpdateHP(Stats.HP, Stats.HPMax);
		}
		if (Stats.Stamina != Stats.StaminaMax)
		{
			UpdateStamina(Stats.Stamina, Stats.StaminaMax);
		}
	}
}

void UCharacterInfo::NativeDestruct()
{
	Super::NativeDestruct();
	OnUnhoveredSlot();
}

void UCharacterInfo::OnReleasedTitleDragButton()
{
	Super::OnReleasedTitleDragButton();

	// 위치저장
	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController)
	{
		UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(InnerCanvas);
		if (CanvasPanelSlot)
		{
			const FVector2D& CurrentLocation = CanvasPanelSlot->GetPosition();
			CharacterController->SetCharacterInfoInitialLocation(CurrentLocation);

			float PanelSlotSizeX = CanvasPanelSlot->GetSize().X;
			TooltipLocation = FVector2D(CurrentLocation.X + PanelSlotSizeX + 10.f, CurrentLocation.Y + 30.f);
		}
	}
}

void UCharacterInfo::InitCanvasLocation()
{
	Super::InitCanvasLocation();

	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController && InnerCanvas)
	{
		UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(InnerCanvas);
		if (CanvasPanelSlot)
		{
			const FVector2D& Location = CharacterController->GetCharacterInfoInitialLocation();
			CanvasPanelSlot->SetPosition(Location);

			float PanelSlotSizeX = CanvasPanelSlot->GetSize().X;
			TooltipLocation = FVector2D(Location.X + PanelSlotSizeX + 10.f, Location.Y + 30.f);
		}
	}
}

void UCharacterInfo::InitEquipmentSlot()
{
	if (HelmetSlot && ArmourSlot && WeaponSlot && SubWeaponSlot && ShieldSlot && AccessorySlot && ShoesSlot)
	{
		HelmetSlot->InitByType(EEquipmentType::EET_Helmet);
		ArmourSlot->InitByType(EEquipmentType::EET_Armour);
		WeaponSlot->InitByType(EEquipmentType::EET_Weapon);
		SubWeaponSlot->InitByType(EEquipmentType::EET_SubWeapon);
		ShieldSlot->InitByType(EEquipmentType::EET_Shield);
		AccessorySlot->InitByType(EEquipmentType::EET_Accessory);
		ShoesSlot->InitByType(EEquipmentType::EET_Shoes);

		for (UEquipmentSlot* EquipmentSlot : EquipmentSlots)
		{
			EquipmentSlot->UpdateSlot();
			EquipmentSlot->SetCharacterInfo(this);
		}
	}
}

void UCharacterInfo::UpdateStats()
{
	ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	UDefaultGameInstance* DefaultGameInstance = Cast<UDefaultGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (DefaultCharacter && DefaultGameInstance)
	{
		const FCharacterStats& Stats = DefaultCharacter->GetCharacterStats();


		// 이름
		const FString& UserName = DefaultGameInstance->GetUserName();
		if (UserNameText)
		{
			UserNameText->SetText(FText::FromString(UserName));
		}

		// 레벨
		const int32 Level = Stats.Level;
		if (LevelText)
		{
			LevelText->SetText(FText::FromString(FString::FromInt(Level)));
		}

		// 직업
		const ECharacterClass CharacterClass = DefaultCharacter->GetCharacterClass();
		if (ClassText)
		{
			if (CharacterClass == ECharacterClass::ECC_Assassin)
			{
				ClassText->SetText(FText::FromString(TEXT("어쌔신")));
			}
		}

		// 체력
		const float CharacterHp = Stats.HP;
		const float CharacterHpMax = Stats.HPMax;
		UpdateHP(CharacterHp, CharacterHpMax);

		// 스태미너
		const float CharacterStamina = Stats.Stamina;
		const float CharacterStaminaMax = Stats.StaminaMax;
		UpdateStamina(CharacterStamina, CharacterStaminaMax);

		// 경험치
		const float CharacterExp = Stats.Exp;
		const float CharacterExpMax = Stats.ExpMax;
		if (ExpCurrent && ExpMax && ExpProgressBar)
		{
			ExpCurrent->SetText(FText::FromString(FString::FromInt(CharacterExp)));
			ExpMax->SetText(FText::FromString(FString::FromInt(CharacterExpMax)));

			if (CharacterExp != 0.f)
			{
				ExpProgressBar->SetPercent(CharacterExp / CharacterExpMax);
			}
			else
			{
				ExpProgressBar->SetPercent(0.f);
			}
		}

		// 공격력
		const float AttackDamage = Stats.AttackDamage;
		if (ADText)
		{
			ADText->SetText(FText::FromString(FString::SanitizeFloat(AttackDamage)));
		}

		// 물리방어
		const float ADDefense = Stats.AttackDamageDefense;
		if (ADDefenseText)
		{
			ADDefenseText->SetText(FText::FromString(FString::SanitizeFloat(ADDefense)));
		}

		// 공격속도
		const float AttackSpeed = Stats.AttackSpeed;
		if (AttackSpeedText)
		{
			AttackSpeedText->SetText(FText::FromString(FString::SanitizeFloat(AttackSpeed)));
		}

		// 치명타
		const float Critical = Stats.Critical;
		if (CriticalText)
		{
			CriticalText->SetText(FText::FromString(FString::SanitizeFloat(Critical)));
		}

		// 마법데미지
		const float AbilityPower = Stats.AbilityPower;
		if (APText)
		{
			APText->SetText(FText::FromString(FString::SanitizeFloat(AbilityPower)));
		}

		// 마법저항력
		const float APDefense = Stats.AbilityPowerDefense;
		if (APDefenseText)
		{
			APDefenseText->SetText(FText::FromString(FString::SanitizeFloat(APDefense)));
		}

		// 쿨다운
		const float CoolDown = Stats.CoolDown;
		if (CoolDownText)
		{
			CoolDownText->SetText(FText::FromString(FString::SanitizeFloat(CoolDown)));
		}

		// 이동속도
		const float MovementSpeed = Stats.MovementSpeed;
		if (MovementSpeedText)
		{
			MovementSpeedText->SetText(FText::FromString(FString::SanitizeFloat(MovementSpeed)));
		}
	}
}

void UCharacterInfo::UpdateHP(const float& CurrentHP, const float& MaxHP)
{
	if (HpCurrent && HpMax && HPProgressBar)
	{
		HpCurrent->SetText(FText::FromString(FString::FromInt(CurrentHP)));
		HpMax->SetText(FText::FromString(FString::FromInt(MaxHP)));

		if (CurrentHP != 0.f)
		{
			HPProgressBar->SetPercent(CurrentHP / MaxHP);
		}
		else
		{
			HPProgressBar->SetPercent(0.f);
		}
	}
}

void UCharacterInfo::UpdateStamina(const float& CurrentStamina, const float& MaxStamina)
{
	if (StaminaCurrent && StaminaMax && StaminaProgressBar)
	{
		StaminaCurrent->SetText(FText::FromString(FString::FromInt(CurrentStamina)));
		StaminaMax->SetText(FText::FromString(FString::FromInt(MaxStamina)));

		if (CurrentStamina != 0.f)
		{
			StaminaProgressBar->SetPercent(CurrentStamina / MaxStamina);
		}
		else
		{
			StaminaProgressBar->SetPercent(0.f);
		}
	}
}

void UCharacterInfo::OnHoveredSlot(const FName& ItemCode)
{
	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController)
	{
		AHUDBase* HUDBase = Cast<AHUDBase>(CharacterController->GetHUD());
		if (HUDBase)
		{
			HUDBase->ShowItemTooltip(ItemCode, TooltipLocation);
		}
	}
}

void UCharacterInfo::OnUnhoveredSlot()
{
	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (CharacterController)
	{
		AHUDBase* HUDBase = Cast<AHUDBase>(CharacterController->GetHUD());
		if (HUDBase)
		{
			HUDBase->HideItemTooltip();
		}
	}
}

