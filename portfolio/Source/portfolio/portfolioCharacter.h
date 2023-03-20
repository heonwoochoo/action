// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CharacterTypes.h"
#include "portfolioCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UAbilityComponent;
class UCharacterDataAsset;
class UAnimInstanceBase;
class UCharacterMotionWarpingComponent;

UCLASS(config=Game)
class AportfolioCharacter : public ACharacter
{
	GENERATED_BODY()



public:
	AportfolioCharacter();

	virtual void Tick(float DeltaTime) override;
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	

	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	void MoveEnd();

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Handle double jump */
	virtual void Jump() override;

	/** Left mouse click */
	void DefaultAttack(const FInputActionValue& Value);

	/** Called Sprint Action */
	void OnSprint();
	void OffSprint();

	/** Called Evade Action */
	void OnEvade();

	/** Skill Event Handler */
	void SkillManagerOne();
	void SkillManagerTwo();
	void SkillManagerThree();
	void SkillManagerFour();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackForwardDistance = 50.f;

	float MeleeAttackDistance = 100.f;

	UPROPERTY(VisibleAnywhere, BLueprintReadOnly)
	float MeleeAttackRadius = 75.f;

	UFUNCTION(BlueprintCallable)
	FVector GetMeleeAttackLocation();

	UFUNCTION(BlueprintCallable)
	void UpdateWarpForwardLocation(const FName WarpName, const float Distance);

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }


	

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DefaultAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* EvadeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Skill1Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Skill2Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Skill3Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Skill4Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	UAbilityComponent* AbilityComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	UCharacterMotionWarpingComponent* CharacterMWComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCharacterDataAsset* CharacterDataAsset;

	UAnimInstanceBase* AnimInstance;
	
	bool bCanAttack = true;

	uint8 AttackCount = 0;

	bool bCanDoubleJump = false;

	float DubleJumpForwardVelocity = 200.f;

	float DefaultMaxWalkSpeed = 400.f;

	float SprintMaxSpeed = 800.f;

	float CapsuleDefaultHalfHeight = 96.f;

	float InitialRelativeLocationZ;


	

	// 캐릭터의 동작 상태
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ECharacterActionState CharacterActionState = ECharacterActionState::ECAS_Unoccupied;

	void DoubleJump();

	void FinishEvade();

	void DownSizeCapsule(float DeltaTime);

	void UpSizeCapsule(float DeltaTime);

public:
	UFUNCTION(BlueprintCallable)
	UAbilityComponent* GetAbilityComponent() const;

	UCharacterDataAsset* GetCharacterDataAsset() const;

	UFUNCTION(BlueprintCallable)
	void AttackChainStart();

	UFUNCTION(BlueprintCallable)
	void AttackChainEnd();

	UFUNCTION(BlueprintCallable)
	void CheckEnemyInRange(const FVector Location, const float Radius, const float Damage);

	UFUNCTION(BlueprintCallable)
	void EnableDoubleJump();

	UFUNCTION(BlueprintCallable)
	void DisableDoubleJump();

	UFUNCTION(BlueprintCallable)
	ECharacterActionState GetCharacterActionState() const;

	UFUNCTION(BlueprintCallable)
	void SetCharacterActionState(ECharacterActionState ActionState);

	UFUNCTION()
	void OnAnimationEnded(UAnimMontage* AnimClass, bool bInterrupted);

	UCharacterMotionWarpingComponent* GetMotionWarpingComponent() const;
};

