
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

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 800.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create AbilityComponent
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent>(TEXT("AbilityComponent"));

	// Create MotionWarpingComponent;
	CharacterMWComponent = CreateDefaultSubobject<UCharacterMotionWarpingComponent>(TEXT("MotionWarpingComponent"));

	// Create InventoryComponent
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	InitialRelativeLocationZ = 0.f;

	DefaultClass = ECharacterClass::ECC_Assassin;
}

void ADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
		GetCharacterMovement()->MaxWalkSpeed = DefaultStats.GetMovementSpeed();
		SprintMaxSpeed = DefaultStats.GetMovementSpeed() * 2.f;
	}

	Tags.Add(FName("Player"));
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
		EnhancedInputComponent->BindAction(Item1Action, ETriggerEvent::Triggered, this, &ADefaultCharacter::ItemManager_1);
		EnhancedInputComponent->BindAction(Item2Action, ETriggerEvent::Triggered, this, &ADefaultCharacter::ItemManager_2);
		EnhancedInputComponent->BindAction(Item3Action, ETriggerEvent::Triggered, this, &ADefaultCharacter::ItemManager_3);
		EnhancedInputComponent->BindAction(Item4Action, ETriggerEvent::Triggered, this, &ADefaultCharacter::ItemManager_4);
		EnhancedInputComponent->BindAction(Item5Action, ETriggerEvent::Triggered, this, &ADefaultCharacter::ItemManager_5);
		EnhancedInputComponent->BindAction(Item6Action, ETriggerEvent::Triggered, this, &ADefaultCharacter::ItemManager_6);
	}
}

void ADefaultCharacter::Move(const FInputActionValue& Value)
{
	if (IsPlayerDead()) return;
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
	if (IsPlayerDead()) return;
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
	if (IsPlayerDead()) return;
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
	if (IsPlayerDead()) return;
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
	if (IsPlayerDead()) return;
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
	if (IsPlayerDead()) return;
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
	if (IsPlayerDead()) return;
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
	if (IsPlayerDead()) return;
	if (AbilityComponent && CharacterActionState != ECharacterActionState::ECAS_SkillCasting)
	{
		
		AbilityComponent->HandleSkillOne();
	}
}

void ADefaultCharacter::SkillManagerTwo()
{
	if (IsPlayerDead()) return;
	if (AbilityComponent && CharacterActionState != ECharacterActionState::ECAS_SkillCasting)
	{
		AbilityComponent->HandleSkillTwo();
	}
}

void ADefaultCharacter::SkillManagerThree()
{
	if (IsPlayerDead()) return;
	if (AbilityComponent && CharacterActionState != ECharacterActionState::ECAS_SkillCasting)
	{
		AbilityComponent->HandleSkillThree();
	}
}

void ADefaultCharacter::SkillManagerFour()
{
	if (IsPlayerDead()) return;
	if (AbilityComponent && CharacterActionState != ECharacterActionState::ECAS_SkillCasting)
	{
		AbilityComponent->HandleSkillFour();
	}
}

void ADefaultCharacter::ItemManager_1()
{
	if (IsPlayerDead()) return;
	if (InventoryComponent)
	{
		InventoryComponent->ItemHandle_1();
	}
}

void ADefaultCharacter::ItemManager_2()
{
	if (IsPlayerDead()) return;
	if (InventoryComponent)
	{
		InventoryComponent->ItemHandle_2();
	}
}

void ADefaultCharacter::ItemManager_3()
{
	if (IsPlayerDead()) return;
	if (InventoryComponent)
	{
		InventoryComponent->ItemHandle_3();
	}
}

void ADefaultCharacter::ItemManager_4()
{
	if (IsPlayerDead()) return;
	if (InventoryComponent)
	{
		InventoryComponent->ItemHandle_4();
	}
}

void ADefaultCharacter::ItemManager_5()
{
	if (IsPlayerDead()) return;
	if (InventoryComponent)
	{
		InventoryComponent->ItemHandle_5();
	}
}

void ADefaultCharacter::ItemManager_6()
{
	if (IsPlayerDead()) return;
	if (InventoryComponent)
	{
		InventoryComponent->ItemHandle_6();
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

	DefaultStats.HP -= DamageAmount;

	if (DefaultStats.HP <= 0)
	{
		Die();
	}
	ACharacterController* CharacterController = Cast<ACharacterController>(GetController());
	if (CharacterController)
	{
		AHUDBase* HUDBase = Cast<AHUDBase>(CharacterController->GetHUD());
		if (HUDBase)
		{
			HUDBase->GetInfoContainer()->UpdateHP();
		}
	}
	return 0.0f;
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

void ADefaultCharacter::PlaySound(USoundCue* Sound)
{
	if (Sound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sound, GetActorLocation());
	}
}

bool ADefaultCharacter::IsPlayerDead()
{
	return CharacterActionState == ECharacterActionState::ECAS_Dead;
}

UAbilityComponent* ADefaultCharacter::GetAbilityComponent() const
{
	return AbilityComponent;
}

UInventoryComponent* ADefaultCharacter::GetInventoryComponent() const
{
	return InventoryComponent;
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

void ADefaultCharacter::CheckEnemyInRange(const FVector Location, const float Radius, float Damage, USoundCue* HitSound)
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
			PlaySound(HitSound);
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
	UGameplayStatics::ApplyDamage(Enemy, UHelperFunction::GetRandomDamage(Damage, DefaultStats.GetCritical()), CharacterController, this, DamageType);
}

void ADefaultCharacter::Die()
{
	DefaultStats.HP = 0;
	CharacterActionState = ECharacterActionState::ECAS_Dead;
	Tags.Add(FName("Dead"));
	UE_LOG(LogTemp, Warning, TEXT("Player dead"));
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
		UE_LOG(LogTemp, Warning, TEXT("Hello"));
	}
}
