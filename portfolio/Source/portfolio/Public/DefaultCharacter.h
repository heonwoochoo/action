// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Types/CharacterTypes.h"
#include "Particles/EmitterCameraLensEffectBase.h"
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
class UParticleSystem;
class AHUDBase;
class AItemBase;
class UParticleSystemComponent;
class UHeadUpWidgetComponent;
class UQuestClientComponent;
class ANPCBase;
class UFootstepComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChangedHealthSignature, const float&, CurrentHp, const float&, MaxHp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChangedStaminaSignature, const float&, CurrentSp, const float&, MaxSp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChangedExpSignature, const float&, CurrentExp, const float&, MaxExp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedLevelSignature, const int32&, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedGoldSignature, const int32&, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeadSignature);


UCLASS(config=Game)
class ADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADefaultCharacter();

	virtual void Tick(float DeltaTime) override;
			
	FOnChangedHealthSignature OnChangedHealth;
	FOnChangedStaminaSignature OnChangedStamina;
	FOnChangedExpSignature OnChangedExp;
	FOnChangedLevelSignature OnChangedLevel;
	FOnChangedGoldSignature OnGetGold;
	FOnDeadSignature OnDead;

protected:
	/** 캐릭터의 기본 스탯 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDataTable* StatsDataTable;

	/** 피격시 재생 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect|Sound")
	USoundCue* HitReactSound;

	/** 피격시 카메라 효과 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect|Camera")
	TSubclassOf<UCameraShakeBase> HitCameraShakeClass;

	/** 피격시 카메라 렌즈효과*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect|Camera")
	TSubclassOf<AEmitterCameraLensEffectBase> HitReactCameraLens;

	/** 레벨업시 재생되는 이펙트 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
	UParticleSystem* LevelUpParticle;

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
	void QuickSlotManager_1();
	void QuickSlotManager_2();
	void QuickSlotManager_3();
	void QuickSlotManager_4();
	void QuickSlotManager_5();
	void QuickSlotManager_6();

	/** E 키 (수집, 대화) */
	void OnPressedZKey();
	void PickupItem();
	void TalkWithNPC();


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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera|Shake", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> AttackCameraShakeClass;

	/**  
	* 캐릭터의 발밑에 부착된 컴포넌트
	* ex) 레벨업 시 생기는 파티클, 버프 등
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Particle, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* ParticleComponent;

	/**
	* 캐릭터 머리 위에 생성되는 텍스트
	* ex) 경험치 획득, 골드 회득, 피격 등
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Particle, meta = (AllowPrivateAccess = "true"))
	UHeadUpWidgetComponent* HeadUpWidgetComonent;

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
	UInputAction* ItemSlotOneAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ItemSlotTwoAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ItemSlotThreeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ItemSlotFourAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ItemSlotFiveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ItemSlotSixAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PickupAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InGameMenuAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	UAbilityComponent* AbilityComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	UQuestClientComponent* QuestClientComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	UCharacterMotionWarpingComponent* CharacterMWComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	UFootstepComponent* FootStepComponent;

	UAnimInstanceBase* AnimInstance;
	
	AHUDBase* HUDBase;

	float CameraBoomArmLength = 400.f;

	// true시 카메라 Arm의 길이가 늘어남
	bool bIsIncreaseCameraArmLength = false;

	// 마우스가 화면에 보이는 상태인지?
	// true -> UI 선택모드 / false -> 캐릭터 컨트롤
	bool bIsMouseShowing = false;

	bool bCanAttack = true;

	uint8 AttackCount = 0;

	bool bCanDoubleJump = false;

	float DubleJumpForwardVelocity = 200.f;

	float DefaultMaxWalkSpeed = 400.f;

	float SprintMaxSpeed;

	float CapsuleDefaultHalfHeight = 96.f;

	float InitialRelativeLocationZ;

	// 아이템 픽업 사운드
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect|Sound", meta = (AllowPrivateAccess = "true"))
	USoundCue* ItemPickupSound;

	// 레벨업 사운드
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect|Sound", meta = (AllowPrivateAccess = "true"))
	USoundCue* LevelUpSound;

	// 골드 픽업 사운드
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect|Sound", meta = (AllowPrivateAccess = "true"))
	USoundCue* GoldPickupSound;

	// 공격시 콤보 증가
	int32 ComboCount = 0;

	FTimerHandle ComboTimerHandle;

	// 히트시 경직도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float HitTimeDilation = 0.f;

	// 경직 딜레이
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float HitTimeDilationDelay = 0.05f;

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
	ECharacterActionState ActionState = ECharacterActionState::ECAS_Unoccupied;

	// 캐릭터 무기 착용 상태
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	ECharacterEquipState EquipState = ECharacterEquipState::ECES_Unquipped;

	// 캐릭터에 오버랩 된 아이템
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	AItemBase* OverlappedItem;
	AItemBase* PrevOverlappedItem;

	// 대화를 할 수 있는 NPC
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC", meta = (AllowPrivateAccess = "true"))
	ANPCBase* NPC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Properties")
	FCharacterStats DefaultStats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Properties")
	ECharacterClass DefaultClass;

	void DoubleJump();

	void FinishEvade();

	// 캐릭터의 사망 상태 확인, 이벤트의 실행을 막음
	bool IsPlayerDead();

	// 체력, 스테미너가 Max 이하일 경우 재생
	void RegenerateHealth();
	void RegenerateStamina();
	void TurnOnRegenerateHealth();
	void TurnOnRegenerateStamina();

	// 콤보 카운트 초기화
	void ResetComboCount();

	/**
	* true 반환시 플레이어의 움직임을 제한합니다.
	* ex) 사망, 인게임 메뉴 열기
	*/
	bool IsBlockedMove();

	// 게임 시작 시 저장된 캐릭터의 데이터 불러오기
	void LoadDataFromSaveGame();

	// 경험치가 Max에 도달시 레벨 업
	void LevelUp();

public:
	/** 마우스 토글 */
	void HandleShowMouse();

	void HandleComboCount();

	UFUNCTION(BlueprintCallable)
	UAbilityComponent* GetAbilityComponent() const;

	UInventoryComponent* GetInventoryComponent() const;

	UQuestClientComponent* GetQuestClientComponent() const;

	UFootstepComponent* GetFootstepComponent() const;

	FORCEINLINE USceneComponent* GetEmitterComponent() const { return EmitterComponent; }
	FORCEINLINE UHeadUpWidgetComponent* GetHeadUpWidgetComponent() const { return HeadUpWidgetComonent; }

	UFUNCTION()
	void BeginOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

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
	ECharacterActionState GetActionState() const;
	UFUNCTION(BlueprintCallable)
	void SetActionState(ECharacterActionState NewActionState);

	UFUNCTION(BlueprintCallable)
	ECharacterEquipState GetEquipState() const;
	UFUNCTION(BlueprintCallable)
	void SetEquipState(const ECharacterEquipState& NewState);

	UFUNCTION()
	void OnAnimationEnded(UAnimMontage* AnimClass, bool bInterrupted);

	UCharacterMotionWarpingComponent* GetMotionWarpingComponent() const;
	
	UFUNCTION()
	ECharacterClass GetCharacterClass();

	FORCEINLINE FCharacterStats GetCharacterStats() const { return DefaultStats; }
	
	void DamageToEnemy(AActor* Enemy, float Damage);

	void Die();

	void PlaySoundCue(USoundCue* SoundAsset);

	void PlayCameraShake(TSubclassOf<UCameraShakeBase> CameraShakeClass);

	void PlayCameraLensEffect(TSubclassOf<AEmitterCameraLensEffectBase> CameraLensEffectClass);

	// 캐릭터의 스탯을 업데이트 (체력, 기력, 공격력, ...)
	void UpdateStatManager(EStatTarget Stat, EStatUpdateType UpdateType,float Value);
	
	// 장착된 장비에 따른 스탯 업데이트
	void UpdateEquipmentStat();

	// 장비 스탯 적용
	FCharacterStats GetAppliedEquipmentStats(const FCharacterStats& TargetStats, const FCharacterStats& ItemStats);

	void UpdateHealth(EStatUpdateType UpdateType, float Value);
	void UpdateStamina(EStatUpdateType UpdateType, float Value);
	void UpdateExp(EStatUpdateType UpdateType, float Value);
	void UpdateGold(EStatUpdateType UpdateType, const int32& Value);

	void SetIsMouseShowing(bool bShowing);

	// 아이템을 획득할 수 있는 상태인지 체크
	bool CanPickupItem(AItemBase* Item);

	// 카메라 Arm의 길이를 늘림 (스킬 액션)
	void IncreaseCameraArmLength(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	bool GetIsIncreaseCameraArmLength() const;

	UFUNCTION(BlueprintCallable)
	void SetIsIncreaseCameraArmLength(const bool& IsIncrease);

	// 원래의 길이로 복귀
	void ReturnCameraArmLength(float DeltaTime);

	FORCEINLINE ANPCBase* GetNPC() const { return NPC; }
	FORCEINLINE void SetNPC(ANPCBase* InNPC) { NPC = InNPC; }

	// 경직효과 Time Dilation
	FTimerHandle TimeDilationHandle;

	UFUNCTION()
	void ResetTimeDilation();

	FORCEINLINE float GetHitTimeDilation() const { return HitTimeDilation; }
	FORCEINLINE float GetHitTimeDilationDelay() const { return HitTimeDilationDelay; }
};