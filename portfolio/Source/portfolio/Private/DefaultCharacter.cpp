// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Component/AbilityComponent.h"
#include "Animation/AnimInstanceBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Component/CharacterMotionWarpingComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Controller/CharacterController.h"
#include "Enemy/EnemyBase.h"
#include "HelperFunction.h"
#include "Sound/SoundCue.h"
#include "HUD/HUDBase.h"
#include "HUD/Overlay/InfoContainer.h"
#include "Component/InventoryComponent.h"
#include "HUD/ComboCountWidget.h"
#include "HUD/ItemTooltipWidget.h"
#include "GameInstance/DefaultGameInstance.h"
#include "SaveGame/UserSaveGame.h"
#include "Items/ItemBase.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Particles/ParticleSystemComponent.h"

ADefaultCharacter::ADefaultCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, CapsuleDefaultHalfHeight);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// 카메라 붐 생성
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 800.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// 카메라 생성
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// 어빌리티 컴포넌트 생성
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent>(TEXT("AbilityComponent"));

	// 모션 매핑 컴포넌트 생성
	CharacterMWComponent = CreateDefaultSubobject<UCharacterMotionWarpingComponent>(TEXT("MotionWarpingComponent"));

	// 인벤토리 컴포넌트 생성
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	EmitterComponent = CreateDefaultSubobject<USceneComponent>(TEXT("EmitterComponent"));
	EmitterComponent->SetupAttachment(GetRootComponent());

	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	ParticleComponent->SetupAttachment(GetRootComponent());

	InitialRelativeLocationZ = 0.f;

	DefaultClass = ECharacterClass::ECC_Assassin;
}

void ADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RegenerateHealth();
	RegenerateStamina();
}

void ADefaultCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	AnimInstance = Cast<UAnimInstanceBase>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &ADefaultCharacter::OnAnimationEnded);
	}

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = DefaultStats.MovementSpeed;
		SprintMaxSpeed = DefaultStats.MovementSpeed * 2.f;
	}

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ADefaultCharacter::BeginOverlapped);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ADefaultCharacter::EndOverlapped);

	ACharacterController* CharacterController = Cast<ACharacterController>(GetController());
	if (CharacterController)
	{
		HUDBase = Cast<AHUDBase>(CharacterController->GetHUD());
	}

	Tags.Add(FName("Player"));

	LoadDataFromSaveGame();
}

//////////////////////////////////////////////////////////////////////////
// Input

void ADefaultCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent) 
	{
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ADefaultCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		
		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADefaultCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ADefaultCharacter::MoveEnd);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADefaultCharacter::Look);

		// DefaultAttack
		EnhancedInputComponent->BindAction(DefaultAttackAction, ETriggerEvent::Triggered, this, &ADefaultCharacter::DefaultAttack);
	
		// Sprint
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ADefaultCharacter::OnSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ADefaultCharacter::OffSprint);
		
		// Evade
		EnhancedInputComponent->BindAction(EvadeAction, ETriggerEvent::Triggered, this, &ADefaultCharacter::OnEvade);
		
		// Skill
		EnhancedInputComponent->BindAction(Skill1Action, ETriggerEvent::Triggered, this, &ADefaultCharacter::SkillManagerOne);
		EnhancedInputComponent->BindAction(Skill2Action, ETriggerEvent::Triggered, this, &ADefaultCharacter::SkillManagerTwo);
		EnhancedInputComponent->BindAction(Skill3Action, ETriggerEvent::Triggered, this, &ADefaultCharacter::SkillManagerThree);
		EnhancedInputComponent->BindAction(Skill4Action, ETriggerEvent::Triggered, this, &ADefaultCharacter::SkillManagerFour);
		
		// Item
		EnhancedInputComponent->BindAction(Item1Action, ETriggerEvent::Triggered, this, &ADefaultCharacter::QuickSlotManager_1);
		EnhancedInputComponent->BindAction(Item2Action, ETriggerEvent::Triggered, this, &ADefaultCharacter::QuickSlotManager_2);
		EnhancedInputComponent->BindAction(Item3Action, ETriggerEvent::Triggered, this, &ADefaultCharacter::QuickSlotManager_3);
		EnhancedInputComponent->BindAction(Item4Action, ETriggerEvent::Triggered, this, &ADefaultCharacter::QuickSlotManager_4);
		EnhancedInputComponent->BindAction(Item5Action, ETriggerEvent::Triggered, this, &ADefaultCharacter::QuickSlotManager_5);
		EnhancedInputComponent->BindAction(Item6Action, ETriggerEvent::Triggered, this, &ADefaultCharacter::QuickSlotManager_6);
		EnhancedInputComponent->BindAction(PickupAction, ETriggerEvent::Triggered, this, &ADefaultCharacter::PickupItem);
		
		// Open widget
		EnhancedInputComponent->BindAction(InGameMenuAction, ETriggerEvent::Triggered, this, &ADefaultCharacter::HandleShowMouse);
	}
}

void ADefaultCharacter::Move(const FInputActionValue& Value)
{
	if (ShouldInputActivated()) return;
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);

		if (GetVelocity().Size() > 0.f
			&& CharacterActionState != ECharacterActionState::ECAS_Evade
			&& CharacterActionState != ECharacterActionState::ECAS_Jump
			&& CharacterActionState != ECharacterActionState::ECAS_Attack
			&& CharacterActionState != ECharacterActionState::ECAS_AttackCombo
			&& CharacterActionState != ECharacterActionState::ECAS_Sprint)
		{
			if (MovementVector.Y)
			{
				CharacterActionState = MovementVector.Y > 0 ? ECharacterActionState::ECAS_MoveForward : ECharacterActionState::ECAS_MoveBack;
			}
			else
			{
				CharacterActionState = MovementVector.X > 0 ? ECharacterActionState::ECAS_MoveRight : ECharacterActionState::ECAS_MoveLeft;
			}
		}
	}
}

void ADefaultCharacter::MoveEnd()
{
	if (ShouldInputActivated()) return;
	CharacterActionState = ECharacterActionState::ECAS_Unoccupied;
}

void ADefaultCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ADefaultCharacter::Jump()
{
	if (ShouldInputActivated()) return;
	CharacterActionState = ECharacterActionState::ECAS_Jump;
	if (!bCanDoubleJump)
	{
		Super::Jump();
	}
	else
	{
		DoubleJump();
	}
}

void ADefaultCharacter::DefaultAttack(const FInputActionValue& Value)
{
	if (ShouldInputActivated()) return;
	if (CharacterActionState == ECharacterActionState::ECAS_Unoccupied
		|| CharacterActionState == ECharacterActionState::ECAS_AttackCombo
		|| CharacterActionState == ECharacterActionState::ECAS_MoveForward
		|| CharacterActionState == ECharacterActionState::ECAS_MoveBack
		|| CharacterActionState == ECharacterActionState::ECAS_MoveLeft
		|| CharacterActionState == ECharacterActionState::ECAS_MoveRight)
	{
		CharacterActionState = ECharacterActionState::ECAS_Attack;
		
		if (AnimInstance)
		{
			UAnimMontage* AttackMontage = AnimInstance->GetDefaultAttackMontage();
			if (AttackMontage && CharacterMWComponent)
			{
				UpdateWarpForwardLocation("MoveForward", AttackForwardDistance);
				AnimInstance->Montage_Play(AttackMontage);

				FName SectionName;
				switch (AttackCount)
				{
				case 0:
					SectionName = "Attack1";
					break;
				case 1:
					SectionName = "Attack2";
					break;
				case 2:
					SectionName = "Attack3";
					break;
				case 3:
					SectionName = "Attack4";
					AttackCount = 0;
					break;
				}
				AnimInstance->Montage_JumpToSection(SectionName);
			}
		}
	}
}

void ADefaultCharacter::OnSprint()
{
	if (ShouldInputActivated()) return;
	if (GetVelocity().Size() > 0.f)
	{
		if (CharacterActionState != ECharacterActionState::ECAS_Jump)
		{
			CharacterActionState = ECharacterActionState::ECAS_Sprint;
		}
		float CurrentSpeed = GetCharacterMovement()->MaxWalkSpeed;
		GetCharacterMovement()->MaxWalkSpeed = UKismetMathLibrary::FInterpTo(CurrentSpeed, SprintMaxSpeed, GetWorld()->GetDeltaSeconds(), 30.f);
		GetCharacterMovement()->bOrientRotationToMovement = true;
		bUseControllerRotationYaw = false;
	}
}

void ADefaultCharacter::OffSprint()
{
	if (ShouldInputActivated()) return;
	if (CharacterActionState != ECharacterActionState::ECAS_Jump)
	{
		CharacterActionState = ECharacterActionState::ECAS_Unoccupied;
	}
	GetCharacterMovement()->MaxWalkSpeed = DefaultMaxWalkSpeed;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

void ADefaultCharacter::OnEvade()
{
	if (ShouldInputActivated()) return;
	if (AnimInstance && GetVelocity().Size() 
		&& !GetCharacterMovement()->IsFalling()
		&& CharacterActionState != ECharacterActionState::ECAS_Evade
		&& CharacterActionState != ECharacterActionState::ECAS_Sprint)
	{
		
		UAnimMontage* DefaultEvadeMontage = AnimInstance->GetDefaultEvadeMontage();
		if (DefaultEvadeMontage)
		{
			AnimInstance->Montage_Play(DefaultEvadeMontage);

			FName SectionName;
			switch (CharacterActionState)
			{
				case ECharacterActionState::ECAS_MoveForward:
					SectionName = "Forward";
					break;
				case ECharacterActionState::ECAS_MoveBack:
					SectionName = "Forward";
					break;
				case ECharacterActionState::ECAS_MoveRight:
					SectionName = "Forward";
					break;
				case ECharacterActionState::ECAS_MoveLeft:
					SectionName = "Forward";
					break;
			}
			AnimInstance->Montage_JumpToSection(SectionName);
			CharacterActionState = ECharacterActionState::ECAS_Evade;
		}
	}
}

void ADefaultCharacter::SkillManagerOne()
{
	if (ShouldInputActivated()) return;
	if (AbilityComponent && CharacterActionState != ECharacterActionState::ECAS_SkillCasting)
	{
		
		AbilityComponent->HandleSkillOne();
	}
}

void ADefaultCharacter::SkillManagerTwo()
{
	if (ShouldInputActivated()) return;
	if (AbilityComponent && CharacterActionState != ECharacterActionState::ECAS_SkillCasting)
	{
		AbilityComponent->HandleSkillTwo();
	}
}

void ADefaultCharacter::SkillManagerThree()
{
	if (ShouldInputActivated()) return;
	if (AbilityComponent && CharacterActionState != ECharacterActionState::ECAS_SkillCasting)
	{
		AbilityComponent->HandleSkillThree();
	}
}

void ADefaultCharacter::SkillManagerFour()
{
	if (ShouldInputActivated()) return;
	if (AbilityComponent && CharacterActionState != ECharacterActionState::ECAS_SkillCasting)
	{
		AbilityComponent->HandleSkillFour();
	}
}

void ADefaultCharacter::QuickSlotManager_1()
{
	if (ShouldInputActivated()) return;
	if (InventoryComponent)
	{
		InventoryComponent->SlotHandle_1();
	}
}

void ADefaultCharacter::QuickSlotManager_2()
{
	if (ShouldInputActivated()) return;
	if (InventoryComponent)
	{
		InventoryComponent->SlotHandle_2();
	}
}

void ADefaultCharacter::QuickSlotManager_3()
{
	if (ShouldInputActivated()) return;
	if (InventoryComponent)
	{
		InventoryComponent->SlotHandle_3();
	}
}

void ADefaultCharacter::QuickSlotManager_4()
{
	if (ShouldInputActivated()) return;
	if (InventoryComponent)
	{
		InventoryComponent->SlotHandle_4();
	}
}

void ADefaultCharacter::QuickSlotManager_5()
{
	if (ShouldInputActivated()) return;
	if (InventoryComponent)
	{
		InventoryComponent->SlotHandle_5();
	}
}

void ADefaultCharacter::QuickSlotManager_6()
{
	if (ShouldInputActivated()) return;
	if (InventoryComponent)
	{
		InventoryComponent->SlotHandle_6();
	}
}

void ADefaultCharacter::PickupItem()
{
	if (ShouldInputActivated()) return;
	if (OverlappedItem)
	{
		AItemBase* Item = Cast<AItemBase>(OverlappedItem);
		if (Item && CanPickupItem(Item))
		{
			Item->HandlePickupItem(this);
			PlaySoundCue(PickupSound);
		}
		else
		{
			if (HUDBase)
			{
				const FText Message = FText::FromString(TEXT("아이템을 획득할 수 없습니다."));
				HUDBase->NotifyMessageToUser(Message);
			}
		}
	}
}

void ADefaultCharacter::HandleShowMouse()
{
	if (HUDBase)
	{
		if (!bIsMouseShowing)
		{
			// UI 선택 모드로 전환
			bIsMouseShowing = true;

			ACharacterController* CharacterController = Cast<ACharacterController>(GetController());
			if (CharacterController)
			{
				CharacterController->SetInputModeToUI();
			}
		}
		else
		{
			// 캐릭터 컨트롤 모드로 전환
			bIsMouseShowing = false;
			HUDBase->CloseInGameMenu();
		}
	}
}

FVector ADefaultCharacter::GetMeleeAttackLocation()
{
	return GetActorLocation() + GetActorForwardVector() * MeleeAttackDistance;
}

void ADefaultCharacter::UpdateWarpForwardLocation(const FName WarpName, const float Distance)
{
	if (CharacterMWComponent)
	{
		CharacterMWComponent->AddOrUpdateWarpTargetFromLocation(WarpName, GetActorLocation() + GetActorForwardVector() * Distance);
	}
}

void ADefaultCharacter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (StatsDataTable)
	{
		DefaultStats = *StatsDataTable->FindRow<FCharacterStats>(FName("Default"), "");
	}
}

float ADefaultCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// 체력 업데이트
	UpdateStatManager(EStatTarget::EST_Health, EStatUpdateType::ESUT_Minus, DamageAmount);
	
	// 피격 효과음 재생
	PlaySoundCue(HitReactSound);

	// 카메라 쉐이크 효과
	PlayCameraShake(HitCameraShakeClass);

	// 카메라 렌즈 효과
	PlayCameraLensEffect(HitReactCameraLens);

	return 0.0f;
}

void ADefaultCharacter::TurnOnRegenerateHealth()
{
	EnableRegenerateHealth = true;
}

void ADefaultCharacter::TurnOnRegenerateStamina()
{
	EnableRegenerateStamina = true;
}

void ADefaultCharacter::ResetComboCount()
{
	// 콤보 초기화
	ComboCount = 0;

	// UI 업데이트
	if (HUDBase)
	{
		UComboCountWidget* ComboCountWidget = HUDBase->GetComboCountWidget();
		if (ComboCountWidget)
		{
			ComboCountWidget->PlayHideAnimation();
		}
	}
}

void ADefaultCharacter::DoubleJump()
{
	bCanDoubleJump = false;

	const FVector ForwardDir = GetActorForwardVector();
	
	const FVector AddForce = ForwardDir * DubleJumpForwardVelocity + FVector(0, 0, 1) * GetCharacterMovement()->JumpZVelocity;
	LaunchCharacter(AddForce, false, true);
	if (GetCharacterMovement()->IsFalling())
	{
		if (AnimInstance)
		{
			UAnimMontage* DoubleJumpMontage = AnimInstance->GetDefaultDoubleJumpMontage();
			if (DoubleJumpMontage)
			{
				AnimInstance->Montage_Play(DoubleJumpMontage);
			}
		}
	}
}

void ADefaultCharacter::FinishEvade()
{
	CharacterActionState = ECharacterActionState::ECAS_Unoccupied;
}

bool ADefaultCharacter::IsPlayerDead()
{
	return CharacterActionState == ECharacterActionState::ECAS_Dead;
}

void ADefaultCharacter::RegenerateHealth()
{
	if (DefaultStats.HP < DefaultStats.HPMax && EnableRegenerateHealth && !IsPlayerDead())
	{
		UpdateStatManager(EStatTarget::EST_Health, EStatUpdateType::ESUT_Plus, RegenerateHealthRate);
		EnableRegenerateHealth = false;
		GetWorld()->GetTimerManager().SetTimer(RegenerateHealthTimerHandle, this, &ADefaultCharacter::TurnOnRegenerateHealth, 1.f, false);
	}
}

void ADefaultCharacter::RegenerateStamina()
{
	if (DefaultStats.Stamina < DefaultStats.StaminaMax && EnableRegenerateStamina && !IsPlayerDead())
	{
		UpdateStatManager(EStatTarget::EST_Stamina, EStatUpdateType::ESUT_Plus, RegenerateStaminaRate);
		EnableRegenerateStamina = false;
		GetWorld()->GetTimerManager().SetTimer(RegenerateStaminaTimerHandle, this, &ADefaultCharacter::TurnOnRegenerateStamina, 1.f, false);
	}
}

bool ADefaultCharacter::ShouldInputActivated()
{
	return IsPlayerDead() || bIsMouseShowing;
}

void ADefaultCharacter::LoadDataFromSaveGame()
{
	UDefaultGameInstance* DefaultGameInstance = Cast<UDefaultGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (DefaultGameInstance)
	{
		const FString UserName = DefaultGameInstance->GetUserName();
		bool IsExist = UGameplayStatics::DoesSaveGameExist(UserName, 0);
		if (IsExist)
		{
			UUserSaveGame* UserSaveGame = Cast<UUserSaveGame>(UGameplayStatics::LoadGameFromSlot(UserName, 0));
			if (UserSaveGame)
			{
				const FUserInGameInfo& InGameInfo = UserSaveGame->InGameInfo;

				// 위치 설정
				const FTransform& SavedTransform = InGameInfo.Transform;
				if (SavedTransform.IsValid())
				{
					if (HUDBase)
					{
						const FText Message = FText::FromString(TEXT("저장된 데이터를 불러왔습니다."));
						HUDBase->NotifyMessageToUser(Message);
					}
					SetActorTransform(SavedTransform);
				}
			}
		}
	}
}

void ADefaultCharacter::LevelUp()
{
	// 스탯 변화
	DefaultStats.Level++;
	DefaultStats.Exp = 0.f;
	
	// 이펙트 생성
	if (ParticleComponent)
	{
		UGameplayStatics::SpawnEmitterAttached(LevelUpParticle, ParticleComponent);
	}

	// 메세지 표시
	if (HUDBase)
	{
		const FString Message =  FString(TEXT("캐릭터가 ")) + FString::FromInt(DefaultStats.Level) + FString(TEXT("레벨이 되었습니다."));
		HUDBase->HandleMessageOnChat(FText::FromString(Message), FColor::Yellow);
	}
}

void ADefaultCharacter::HandleComboCount()
{
	// 카운트 증가
	ComboCount++;

	// UI 업데이트
	if (HUDBase)
	{
		UComboCountWidget* ComboCountWidget = HUDBase->GetComboCountWidget();
		if (ComboCountWidget)
		{	
			ComboCountWidget->SetComboCount(ComboCount);
			ComboCountWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}

	// 리셋 타이머
	float ResetTime = 5.0f;
	GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &ADefaultCharacter::ResetComboCount, ResetTime, false);
}

UAbilityComponent* ADefaultCharacter::GetAbilityComponent() const
{
	return AbilityComponent;
}

UInventoryComponent* ADefaultCharacter::GetInventoryComponent() const
{
	return InventoryComponent;
}

void ADefaultCharacter::BeginOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName("Item")))
	{
		PrevOverlappedItem = OverlappedItem;
		OverlappedItem = Cast<AItemBase>(OtherActor);

		if (HUDBase)
		{
			// 위치 설정
			const FVector2D& ViewSize = UWidgetLayoutLibrary::GetViewportSize(this);
			const float ViewScale = UWidgetLayoutLibrary::GetViewportScale(this);
			const float X = (ViewSize.X * 0.8f)/ViewScale;
			const float Y = (ViewSize.Y * 0.8f)/ViewScale;

			HUDBase->ShowItemTooltip(OverlappedItem->GetItemCode(), FVector2D(X, Y));
		}
	}
}

void ADefaultCharacter::EndOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag(FName("Item")))
	{
		if (OtherActor == OverlappedItem)
		{
			OverlappedItem = nullptr;
		}
		else if (OtherActor == PrevOverlappedItem)
		{
			PrevOverlappedItem = nullptr;
		}

		if (HUDBase)
		{
			HUDBase->HideItemTooltip();
		}
	}
}

void ADefaultCharacter::AttackChainStart()
{
	CharacterActionState = ECharacterActionState::ECAS_AttackCombo;
	AttackCount++;
}

void ADefaultCharacter::AttackChainEnd()
{
	CharacterActionState = ECharacterActionState::ECAS_Unoccupied;
	AttackCount = 0;
}

void ADefaultCharacter::CheckEnemyInRange(const FVector Location, const float Radius, float Damage, EHitType HitType)
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes = { UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn)};
	TArray<AActor*> ActorsToIgnore = { this };
	TArray<AActor*> OutActors;

	UKismetSystemLibrary::SphereOverlapActors(this, Location, Radius, ObjectTypes, nullptr, ActorsToIgnore, OutActors);
	DrawDebugSphere(GetWorld(), Location, Radius, 16, FColor::Red, false, 1.f);

	for (AActor* Actor : OutActors)
	{
		AEnemyBase* Enemy = Cast<AEnemyBase>(Actor);
		if (Enemy && Enemy->ActorHasTag(FName("Enemy")) && Enemy->GetState() != EEnemyState::EES_Dead)
		{
			DamageToEnemy(Enemy, Damage);
			
			if (AbilityComponent)
			{
				const FVector& EnemyLocation = Enemy->GetActorLocation();
				const FRotator& EnemyRotation = Enemy->GetActorRotation();
				AbilityComponent->PlayHitSound(HitType, EnemyLocation);
				AbilityComponent->SpawnHitParticle(HitType, EnemyLocation, EnemyRotation);
			}
		}
	}
}

void ADefaultCharacter::EnableDoubleJump()
{
	bCanDoubleJump = true;
}

void ADefaultCharacter::DisableDoubleJump()
{
	bCanDoubleJump = false;
}

ECharacterActionState ADefaultCharacter::GetCharacterActionState() const
{
	return CharacterActionState;
}

void ADefaultCharacter::SetCharacterActionState(ECharacterActionState ActionState)
{
	CharacterActionState = ActionState;
}

void ADefaultCharacter::OnAnimationEnded(UAnimMontage* AnimClass, bool bInterrupted)
{
	if (AnimInstance)
	{
		if (AnimClass == AnimInstance->GetDefaultEvadeMontage())
		{
			FinishEvade();
		}
	}
}
UCharacterMotionWarpingComponent* ADefaultCharacter::GetMotionWarpingComponent() const
{
	return CharacterMWComponent;
}

void ADefaultCharacter::DamageToEnemy(AEnemyBase* Enemy, float Damage)
{
	TSubclassOf<UDamageType> DamageType;
	ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	UGameplayStatics::ApplyDamage(Enemy, UHelperFunction::GetRandomDamage(Damage, DefaultStats.Critical), CharacterController, this, DamageType);

	HandleComboCount();
}

void ADefaultCharacter::Die()
{
	DefaultStats.HP = 0;
	CharacterActionState = ECharacterActionState::ECAS_Dead;
	Tags.Add(FName("Dead"));
	UE_LOG(LogTemp, Warning, TEXT("Player dead"));
}

void ADefaultCharacter::PlaySoundCue(USoundCue* SoundAsset)
{
	if (SoundAsset)
	{
		UGameplayStatics::PlaySoundAtLocation(this, SoundAsset, GetActorLocation());
	}
}

void ADefaultCharacter::PlayCameraShake(TSubclassOf<UCameraShakeBase> CameraShakeClass)
{
	if (CameraShakeClass)
	{
		UGameplayStatics::PlayWorldCameraShake(this, CameraShakeClass, GetFollowCamera()->GetComponentLocation(), 0.f, 500.f);
	}
}

void ADefaultCharacter::PlayCameraLensEffect(TSubclassOf<AEmitterCameraLensEffectBase> CameraLensEffectClass)
{
	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
	if (CameraManager && CameraLensEffectClass)
	{
		CameraManager->ClearCameraLensEffects();
		CameraManager->AddCameraLensEffect(CameraLensEffectClass);
	}
}

void ADefaultCharacter::UpdateStatManager(EStatTarget Stat, EStatUpdateType UpdateType, float Value)
{
	switch (Stat)
	{
	case EStatTarget::EST_Health:
		UpdateHealth(UpdateType, Value);
		break;
	case EStatTarget::EST_Stamina:
		UpdateStamina(UpdateType, Value);
		break;
	case EStatTarget::EST_Exp:
		UpdateExp(UpdateType, Value);
		break;
	}
}

void ADefaultCharacter::UpdateEquipmentStat()
{
	const TMap<EEquipmentType, FEquippedItem>& EquippedItemList = InventoryComponent->GetEquippedItemList();
	UDataTable* ItemSpecData = InventoryComponent->GetItemDataTable();
	if (ItemSpecData)
	{
		FCharacterStats NewCharacterStats = *StatsDataTable->FindRow<FCharacterStats>(FName("Default"), "");
		for (const auto& EquippedItem : EquippedItemList)
		{
			const FEquippedItem& Item = EquippedItem.Value;
			if (Item.State == EEquippedState::EES_Equipped)
			{
				const FName& ItemCode = Item.ItemCode;
				FItemSpec* Spec = ItemSpecData->FindRow<FItemSpec>(ItemCode, "");
				const FCharacterStats& ItemStats = Spec->Stats;

				NewCharacterStats = GetAppliedEquipmentStats(NewCharacterStats, ItemStats);
			}
		}
		DefaultStats = NewCharacterStats;
	}
}

FCharacterStats ADefaultCharacter::GetAppliedEquipmentStats(const FCharacterStats& TargetStats, const FCharacterStats& ItemStats)
{
	FCharacterStats ResultStats = DefaultStats;

	ResultStats.AbilityPower = FMath::Max(0,TargetStats.AbilityPower + ItemStats.AbilityPower);
	ResultStats.AbilityPowerDefense = FMath::Max(0, TargetStats.AbilityPowerDefense + ItemStats.AbilityPowerDefense);
	ResultStats.AttackDamage = FMath::Max(0, TargetStats.AttackDamage + ItemStats.AttackDamage);
	ResultStats.AttackDamageDefense = FMath::Max(0, TargetStats.AttackDamageDefense + ItemStats.AttackDamageDefense);
	ResultStats.AttackSpeed = FMath::Max(0, TargetStats.AttackSpeed + ItemStats.AttackSpeed);
	ResultStats.CoolDown = FMath::Clamp(TargetStats.CoolDown + ItemStats.CoolDown, 0, 100);
	ResultStats.Critical = FMath::Clamp(TargetStats.Critical + ItemStats.Critical, 0 ,100);
	ResultStats.MovementSpeed = FMath::Max(0, TargetStats.MovementSpeed + ItemStats.MovementSpeed);
	ResultStats.HPMax = FMath::Max(0, TargetStats.HPMax + ItemStats.HPMax);
	ResultStats.Stamina = FMath::Max(0, TargetStats.StaminaMax + ItemStats.StaminaMax);

	return ResultStats;
}

void ADefaultCharacter::UpdateHealth(EStatUpdateType UpdateType, float Value)
{
	float NewHP = 0.f;

	// 증감 연산
	switch (UpdateType)
	{
	case EStatUpdateType::ESUT_Plus:
		NewHP = DefaultStats.HP + Value;
		break;
	case EStatUpdateType::ESUT_Minus:
		NewHP = DefaultStats.HP - Value;
		break;
	}

	DefaultStats.HP = FMath::Clamp(NewHP, 0.f, DefaultStats.HPMax);

	// 사망 확인
	if (DefaultStats.HP == 0.f)
	{
		Die();
	}

	// UI 업데이트
	if (HUDBase)
	{
		HUDBase->GetInfoContainer()->UpdateHP();
	}
}

void ADefaultCharacter::UpdateStamina(EStatUpdateType UpdateType, float Value)
{
	float NewStamina = 0.f;

	switch (UpdateType)
	{
	case EStatUpdateType::ESUT_Plus:
		NewStamina = DefaultStats.Stamina + Value;
		break;
	case EStatUpdateType::ESUT_Minus:
		NewStamina = DefaultStats.Stamina - Value;
		break;
	}

	DefaultStats.Stamina = FMath::Clamp(NewStamina, 0.f, DefaultStats.StaminaMax);

	// UI 업데이트
	if (HUDBase)
	{
		HUDBase->GetInfoContainer()->UpdateStamina();
	}
}

void ADefaultCharacter::UpdateExp(EStatUpdateType UpdateType, float Value)
{
	const float CurrentExp = DefaultStats.Exp;
	const float MaxExp = DefaultStats.ExpMax;

	if (CurrentExp + Value >= MaxExp)
	{
		// 레벨업
		LevelUp();
	}
	else
	{
		DefaultStats.Exp = CurrentExp + Value;
	}
	// UI 업데이트
	if (HUDBase)
	{
		HUDBase->GetInfoContainer()->UpdateExp();
	}
}

void ADefaultCharacter::SetIsMouseShowing(bool bShowing)
{
	bIsMouseShowing = bShowing;
}

bool ADefaultCharacter::CanPickupItem(AItemBase* Item)
{
	const FName& ItemCode = Item->GetItemCode();

	UDataTable* ItemSpecData = InventoryComponent->GetItemDataTable();
	const TMap<FName, uint8>& ItemList = InventoryComponent->GetItemList();

	if (ItemSpecData)
	{
		FItemSpec* Spec = ItemSpecData->FindRow<FItemSpec>(ItemCode, "");
		if (Spec)
		{
			EItemType Type = Spec->Type;
			const int32 SlotNumber = InventoryComponent->GetInventorySlotNumber(Type);
			int32 RemainingSlotNumber = SlotNumber;

			for (const auto& OwnedItem : ItemList)
			{
				const FName& OwnedItemName = OwnedItem.Key;
				FItemSpec* OwnedItemSpec = ItemSpecData->FindRow<FItemSpec>(OwnedItemName, "");
				if (OwnedItemSpec)
				{
					// 순회하는 아이템 타입과 획득하려는 아이템 타입이 같을 경우 빈 슬롯있는지 체크
					if (OwnedItemSpec->Type == Type)
					{
						
						int32 EntireAmount = OwnedItem.Value;
						int32 MaxAmountPerSlot = OwnedItemSpec->AmountMax;

						// 해당 아이템이 인벤토리에서 차지하는 슬롯의 개수
						int32 RequiredSlotNumber =
							EntireAmount % MaxAmountPerSlot ? (EntireAmount / MaxAmountPerSlot) + 1 : (EntireAmount / MaxAmountPerSlot);

						RemainingSlotNumber -= RequiredSlotNumber;
					}
				}
			}
			if (RemainingSlotNumber >= 1)
			{
				return true;
			}
		}
	}

	return false;
}

ECharacterClass ADefaultCharacter::GetCharacterClass()
{
	return DefaultClass;
}
void ADefaultCharacter::DownSizeCapsule(float DeltaTime)
{
	if (GetCapsuleComponent() && GetMesh())
	{
		GetCapsuleComponent()->SetCapsuleHalfHeight(FMath::FInterpTo(GetCapsuleComponent()->GetScaledCapsuleHalfHeight(), CapsuleDefaultHalfHeight / 2.f, DeltaTime, 30.f));
	}
}

void ADefaultCharacter::UpSizeCapsule(float DeltaTime)
{
	if (GetCapsuleComponent() && GetMesh())
	{
		GetCapsuleComponent()->SetCapsuleHalfHeight(FMath::FInterpTo(GetCapsuleComponent()->GetScaledCapsuleHalfHeight(), CapsuleDefaultHalfHeight, DeltaTime, 30.f));
	}
}
