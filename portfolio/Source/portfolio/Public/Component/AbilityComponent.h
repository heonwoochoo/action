#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/CharacterTypes.h"
#include "AbilityComponent.generated.h"

class UAnimInstanceBase;
class UDataTable;
class ADefaultCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnProgressSkillCoolDownSignature, const float&, Remaining, const float&, Rate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndSkillCoolDownSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAbilityComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FOnProgressSkillCoolDownSignature OnProgressSkillOne;
	FOnEndSkillCoolDownSignature OnEndSkillOne;

	FOnProgressSkillCoolDownSignature OnProgressSkillTwo;
	FOnEndSkillCoolDownSignature OnEndSkillTwo;

	FOnProgressSkillCoolDownSignature OnProgressSkillThree;
	FOnEndSkillCoolDownSignature OnEndSkillThree;

	FOnProgressSkillCoolDownSignature OnProgressSkillFour;
	FOnEndSkillCoolDownSignature OnEndSkillFour;

protected:
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

	ADefaultCharacter* Character;

	UAnimInstanceBase* AnimInstance;

	/** One */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	FCharacterSkill SkillOne;
	FTimerHandle SkillOneHandle;
	bool bCanSkillOne = true;

	/** Two */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	FCharacterSkill SkillTwo;
	FTimerHandle SkillTwoHandle;
	bool bCanSkillTwo = true;

	/** Three */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	FCharacterSkill SkillThree;
	FTimerHandle SkillThreeHandle;
	bool bCanSkillThree = true;

	/** Four */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	FCharacterSkill SkillFour;
	FTimerHandle SkillFourHandle;
	bool bCanSkillFour = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties|Data")
	UDataTable* DefaultEffectDataTable;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties|Data")
	UDataTable* SkillDataTable;

	/** One */
	UFUNCTION(BlueprintCallable)
	virtual void HandleSkillOne();
	void EndSkillOneTimer();
	void SetSkillOneTimer();
	FORCEINLINE FCharacterSkill& GetSkillOne() { return SkillOne; }
	FORCEINLINE bool GetCanSkillOne() const { return bCanSkillOne; }
	FORCEINLINE void SetCanSkillOne(const bool& IsActive) { bCanSkillOne = IsActive; }
	FORCEINLINE FTimerHandle* GetSkillOneHandle() { return &SkillOneHandle; }

	/** Two */
	UFUNCTION(BlueprintCallable)
	virtual void HandleSkillTwo();
	void EndSkillTwoTimer();
	void SetSkillTwoTimer();
	FORCEINLINE FCharacterSkill& GetSkillTwo() { return SkillTwo; }
	FORCEINLINE bool GetCanSkillTwo() const { return bCanSkillTwo; }
	FORCEINLINE void SetCanSkillTwo(const bool& IsActive) { bCanSkillTwo = IsActive; }
	FORCEINLINE FTimerHandle* GetSkillTwoHandle() { return &SkillTwoHandle; }

	/** Three */
	UFUNCTION(BlueprintCallable)
	virtual void HandleSkillThree();
	void EndSkillThreeTimer();
	void SetSkillThreeTimer();
	FORCEINLINE FCharacterSkill& GetSkillThree() { return SkillThree; }
	FORCEINLINE bool GetCanSkillThree() const { return bCanSkillThree; }
	FORCEINLINE void SetCanSkillThree(const bool& IsActive) { bCanSkillThree = IsActive; }
	FORCEINLINE FTimerHandle* GetSkillThreeHandle() { return &SkillThreeHandle; }

	/** Four */
	UFUNCTION(BlueprintCallable)
	virtual void HandleSkillFour();
	void EndSkillFourTimer();
	void SetSkillFourTimer();
	FORCEINLINE FCharacterSkill& GetSkillFour() { return SkillFour; }
	FORCEINLINE bool GetCanSkillFour() const { return bCanSkillFour; }
	FORCEINLINE void SetCanSkillFour(const bool& IsActive) { bCanSkillFour = IsActive; }
	FORCEINLINE FTimerHandle* GetSkillFourHandle() { return &SkillFourHandle; }

	// 기본 파티클 생성
	void SpawnParticleEffect(UParticleSystem* Particle);

	// 적중 타입에 따른 파티클 생성
	void SpawnHitParticle(EHitType HitType, const FVector& Location, const FRotator& Rotation);
	
	// 적중 타입에 따라 다른 효과음 재생
	void PlayHitSound(EHitType HitType, const FVector& Location);

	// 캐릭터의 직업에 따른 RowName을 얻음
	FName GetRowClassName();

	// 쿨다운일 경우 알림
	void NotifyCoolDown(const FTimerHandle& TimerHandle, const FOnProgressSkillCoolDownSignature& Delegate);
};
