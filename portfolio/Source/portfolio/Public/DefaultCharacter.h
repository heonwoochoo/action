// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CharacterTypes.h"
#include "DefaultCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UEnhancedInputComponent;
class UInputMappingContext;
class UInputAction;
class UAbilityComponent;
class UAnimInstanceBase;
class UCharacterMotionWarpingComponent;
class UDataTable;
class USoundCue;
class AEnemyBase;
class UInventoryComponent;

UCLASS(config=Game)
class ADefaultCharacter : public ACharacter
{
	GENERATED_BODY()



public:
	ADefaultCharacter();

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

	/** 아이템 핸들러 */
	void ItemManager_1();
	void ItemManager_2();
	void ItemManager_3();
	void ItemManager_4();
	void ItemManager_5();
	void ItemManager_6();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackForwardDistance = 50.f;

	float MeleeAttackDistance = 100.f;

	UPROPERTY(VisibleAnywhere, BLueprintReadOnly)
	float MeleeAttackRadius = 75.f;

	UFUNCTION(BlueprintCallable)
	FVector GetMeleeAttackLocation();

	UFUNCTION(BlueprintCallable)
	void UpdateWarpForwardLocation(const FName WarpName, const float Distance);

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }


	

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Particle, meta = (AllowPrivateAccess = "true"))
	USceneComponent* EmitterComponent;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UEnhancedInputComponent* EnhancedInputComponent;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Item1Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Item2Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Item3Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Item4Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Item5Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Item6Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	UAbilityComponent* AbilityComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	UCharacterMotionWarpingComponent* CharacterMWComponent;

	UAnimInstanceBase* AnimInstance;
	
	bool bCanAttack = true;

	uint8 AttackCount = 0;

	bool bCanDoubleJump = false;

	float DubleJumpForwardVelocity = 200.f;

	float DefaultMaxWalkSpeed = 400.f;

	float SprintMaxSpeed;

	float CapsuleDefaultHalfHeight = 96.f;

	float InitialRelativeLocationZ;
	
	// 초당 재생량
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float RegenerateHealthRate = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float RegenerateStaminaRate = 1.f;

	FTimerHandle RegenerateHealthTimerHandle;

	FTimerHandle RegenerateStaminaTimerHandle;

	bool EnableRegenerateHealth = true;

	bool EnableRegenerateStamina = true;

	// 캐릭터의 동작 상태
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	ECharacterActionState CharacterActionState = ECharacterActionState::ECAS_Unoccupied;

	void DoubleJump();

	void FinishEvade();

	void DownSizeCapsule(float DeltaTime);

	void UpSizeCapsule(float DeltaTime);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Properties")
	FCharacterStats DefaultStats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Properties")
	ECharacterClass DefaultClass;

	// 캐릭터의 사망 상태 확인, 이벤트의 실행을 막음
	bool IsPlayerDead();

	// 체력, 스테미너가 Max 이하일 경우 재생
	void RegenerateHealth();

	void RegenerateStamina();

	void TurnOnRegenerateHealth();

	void TurnOnRegenerateStamina();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDataTable* StatsDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect|Sound")
	USoundCue* HitReactSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect|Camera")
	TSubclassOf<UCameraShakeBase> HitCameraShakeClass;

	UFUNCTION(BlueprintCallable)
	UAbilityComponent* GetAbilityComponent() const;

	UInventoryComponent* GetInventoryComponent() const;

	FORCEINLINE USceneComponent* GetEmitterComponent() const { return EmitterComponent; }

	UFUNCTION(BlueprintCallable)
	void AttackChainStart();

	UFUNCTION(BlueprintCallable)
	void AttackChainEnd();

	UFUNCTION(BlueprintCallable)
	void CheckEnemyInRange(const FVector Location, const float Radius, float Damage, EHitType HitType);

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
	
	UFUNCTION()
	ECharacterClass GetCharacterClass();

	FORCEINLINE FCharacterStats GetCharacterStats() const { return DefaultStats; }
	
	void DamageToEnemy(AEnemyBase* Enemy, float Damage);

	void Die();

	void PlaySoundCue(USoundCue* SoundAsset);

	void PlayCameraShake(TSubclassOf<UCameraShakeBase> CameraShakeClass);

	// 캐릭터의 스탯을 업데이트 (체력, 기력, 공격력, ...)
	void UpdateStatManager(EStatTarget Stat, EStatUpdateType UpdateType,float AbilityPoint);
	
	void UpdateHealth(EStatUpdateType UpdateType, float AbilityPoint);
	void UpdateStamina(EStatUpdateType UpdateType, float AbilityPoint);

};

