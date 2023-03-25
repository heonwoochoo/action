// Copyright Epic Games, Inc. All Rights Reserved.

#include "portfolioCharacter.h"
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

// AportfolioCharacter

AportfolioCharacter::AportfolioCharacter()
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

	

	InitialRelativeLocationZ = 0.f;

	DefaultClass = ECharacterClass::ECC_Assassin;
}

void AportfolioCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AportfolioCharacter::BeginPlay()
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
		AnimInstance->OnMontageEnded.AddDynamic(this, &AportfolioCharacter::OnAnimationEnded);
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

void AportfolioCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AportfolioCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		
		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AportfolioCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AportfolioCharacter::MoveEnd);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AportfolioCharacter::Look);

		// DefaultAttack
		EnhancedInputComponent->BindAction(DefaultAttackAction, ETriggerEvent::Triggered, this, &AportfolioCharacter::DefaultAttack);
	
		// Sprint
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AportfolioCharacter::OnSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AportfolioCharacter::OffSprint);
		
		// Evade
		EnhancedInputComponent->BindAction(EvadeAction, ETriggerEvent::Triggered, this, &AportfolioCharacter::OnEvade);
		
		// Skill
		EnhancedInputComponent->BindAction(Skill1Action, ETriggerEvent::Triggered, this, &AportfolioCharacter::SkillManagerOne);
		EnhancedInputComponent->BindAction(Skill2Action, ETriggerEvent::Triggered, this, &AportfolioCharacter::SkillManagerTwo);
		EnhancedInputComponent->BindAction(Skill3Action, ETriggerEvent::Triggered, this, &AportfolioCharacter::SkillManagerThree);
		EnhancedInputComponent->BindAction(Skill4Action, ETriggerEvent::Triggered, this, &AportfolioCharacter::SkillManagerFour);
	}
}

void AportfolioCharacter::Move(const FInputActionValue& Value)
{
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

void AportfolioCharacter::MoveEnd()
{
	CharacterActionState = ECharacterActionState::ECAS_Unoccupied;
}

void AportfolioCharacter::Look(const FInputActionValue& Value)
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

void AportfolioCharacter::Jump()
{
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

void AportfolioCharacter::DefaultAttack(const FInputActionValue& Value)
{
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

void AportfolioCharacter::OnSprint()
{
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

void AportfolioCharacter::OffSprint()
{
	if (CharacterActionState != ECharacterActionState::ECAS_Jump)
	{
		CharacterActionState = ECharacterActionState::ECAS_Unoccupied;
	}
	GetCharacterMovement()->MaxWalkSpeed = DefaultMaxWalkSpeed;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

void AportfolioCharacter::OnEvade()
{
	
	if (AnimInstance && GetVelocity().Size() 
		&& !GetCharacterMovement()->IsFalling()
		&& CharacterActionState != ECharacterActionState::ECAS_Evade
		&& CharacterActionState != ECharacterActionState::ECAS_Sprint)
	{
		
		UAnimMontage* DefaultEvadeMontage = AnimInstance->GetDefaultDefaultEvadeMontage();
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

void AportfolioCharacter::SkillManagerOne()
{
	if (AbilityComponent && CharacterActionState != ECharacterActionState::ECAS_SkillCasting)
	{
		AbilityComponent->HandleSkillOne();
	}
}

void AportfolioCharacter::SkillManagerTwo()
{

}

void AportfolioCharacter::SkillManagerThree()
{

}

void AportfolioCharacter::SkillManagerFour()
{

}

FVector AportfolioCharacter::GetMeleeAttackLocation()
{
	return GetActorLocation() + GetActorForwardVector() * MeleeAttackDistance;
}

void AportfolioCharacter::UpdateWarpForwardLocation(const FName WarpName, const float Distance)
{
	if (CharacterMWComponent)
	{
		CharacterMWComponent->AddOrUpdateWarpTargetFromLocation(WarpName, GetActorLocation() + GetActorForwardVector() * Distance);
	}
}

void AportfolioCharacter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (StatsDataTable)
	{
		DefaultStats = *StatsDataTable->FindRow<FCharacterStats>(FName("Default"), "");
	}
}

void AportfolioCharacter::DoubleJump()
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

void AportfolioCharacter::FinishEvade()
{
	CharacterActionState = ECharacterActionState::ECAS_Unoccupied;
}

void AportfolioCharacter::PlaySound(USoundCue* Sound)
{
	if (Sound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sound, GetActorLocation());
	}
}

UAbilityComponent* AportfolioCharacter::GetAbilityComponent() const
{
	return AbilityComponent;
}

void AportfolioCharacter::AttackChainStart()
{
	CharacterActionState = ECharacterActionState::ECAS_AttackCombo;
	AttackCount++;
}

void AportfolioCharacter::AttackChainEnd()
{
	CharacterActionState = ECharacterActionState::ECAS_Unoccupied;
	AttackCount = 0;
}

void AportfolioCharacter::CheckEnemyInRange(const FVector Location, const float Radius, float Damage, USoundCue* HitSound)
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
			TSubclassOf<UDamageType> DamageType;
			ACharacterController* CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0));
			UGameplayStatics::ApplyDamage(Enemy, UHelperFunction::GetRandomDamage(Damage, DefaultStats.GetCritical()), CharacterController, this, DamageType);
			PlaySound(HitSound);
		}
	}
}

void AportfolioCharacter::EnableDoubleJump()
{
	bCanDoubleJump = true;
}

void AportfolioCharacter::DisableDoubleJump()
{
	bCanDoubleJump = false;
}

ECharacterActionState AportfolioCharacter::GetCharacterActionState() const
{
	return CharacterActionState;
}

void AportfolioCharacter::SetCharacterActionState(ECharacterActionState ActionState)
{
	CharacterActionState = ActionState;
}

void AportfolioCharacter::OnAnimationEnded(UAnimMontage* AnimClass, bool bInterrupted)
{
	if (AnimInstance)
	{
		if (AnimClass == AnimInstance->GetDefaultDefaultEvadeMontage())
		{
			FinishEvade();
		}
	}
}
UCharacterMotionWarpingComponent* AportfolioCharacter::GetMotionWarpingComponent() const
{
	return CharacterMWComponent;
}

ECharacterClass AportfolioCharacter::GetCharacterClass()
{
	return DefaultClass;
}
void AportfolioCharacter::DownSizeCapsule(float DeltaTime)
{
	if (GetCapsuleComponent() && GetMesh())
	{
		GetCapsuleComponent()->SetCapsuleHalfHeight(FMath::FInterpTo(GetCapsuleComponent()->GetScaledCapsuleHalfHeight(), CapsuleDefaultHalfHeight / 2.f, DeltaTime, 30.f));

	}
}

void AportfolioCharacter::UpSizeCapsule(float DeltaTime)
{
	if (GetCapsuleComponent() && GetMesh())
	{
		GetCapsuleComponent()->SetCapsuleHalfHeight(FMath::FInterpTo(GetCapsuleComponent()->GetScaledCapsuleHalfHeight(), CapsuleDefaultHalfHeight, DeltaTime, 30.f));
		UE_LOG(LogTemp, Warning, TEXT("Hello"));
	}
}
