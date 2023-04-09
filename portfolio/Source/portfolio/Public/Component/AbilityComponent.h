#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterTypes.h"
#include "AbilityComponent.generated.h"

class UCharacterDataAsset;
class ADefaultCharacter;
class UAnimMontage;
class UCharacterSkillAsset;
class UAnimInstanceBase;
class AKnifeProjectile;
class AAssassin_SkillOne;
class AEnemyBase;
class USoundCue;
class UDataTable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAbilityComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


protected:
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

	ADefaultCharacter* Character;

	UAnimInstanceBase* AnimInstance;

	/** One */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	FCharacterSkill SkillOne;
	FTimerHandle SkillOneHandle;
	void EndSkillOneTimer();
	void SetSkillOneTimer();
	bool bCanSkillOne = true;

	/** Two */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	FCharacterSkill SkillTwo;
	FTimerHandle SkillTwoHandle;
	void EndSkillTwoTimer();
	void SetSkillTwoTimer();
	bool bCanSkillTwo = true;

	/** Three */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	FCharacterSkill SkillThree;
	FTimerHandle SkillThreeHandle;
	void EndSkillThreeTimer();
	void SetSkillThreeTimer();
	bool bCanSkillThree = true;

	/** Four */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	FCharacterSkill SkillFour;
	FTimerHandle SkillFourHandle;
	void EndSkillFourTimer();
	void SetSkillFourTimer();
	bool bCanSkillFour = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties|Data")
	UDataTable* DefaultEffectDataTable;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties|Data")
	UDataTable* SkillDataTable;

	/** One */
	UFUNCTION(BlueprintCallable)
	virtual void HandleSkillOne();
	FORCEINLINE FCharacterSkill& GetSkillOne() { return SkillOne; }
	FORCEINLINE bool GetCanSkillOne() const { return bCanSkillOne; }
	FORCEINLINE FTimerHandle* GetSkillOneHandle() { return &SkillOneHandle; }

	/** Two */
	UFUNCTION(BlueprintCallable)
	virtual void HandleSkillTwo();
	FORCEINLINE FCharacterSkill& GetSkillTwo() { return SkillTwo; }
	FORCEINLINE bool GetCanSkillTwo() const { return bCanSkillTwo; }
	FORCEINLINE FTimerHandle* GetSkillTwoHandle() { return &SkillTwoHandle; }

	/** Three */
	UFUNCTION(BlueprintCallable)
	virtual void HandleSkillThree();
	FORCEINLINE FCharacterSkill& GetSkillThree() { return SkillThree; }
	FORCEINLINE bool GetCanSkillThree() const { return bCanSkillThree; }
	FORCEINLINE FTimerHandle* GetSkillThreeHandle() { return &SkillThreeHandle; }

	/** Four */
	UFUNCTION(BlueprintCallable)
	virtual void HandleSkillFour();
	FORCEINLINE FCharacterSkill& GetSkillFour() { return SkillFour; }
	FORCEINLINE bool GetCanSkillFour() const { return bCanSkillFour; }
	FORCEINLINE FTimerHandle* GetSkillFourHandle() { return &SkillFourHandle; }

	// 기본 파티클 생성
	void SpawnParticleEffect(UParticleSystem* Particle);

	// 적중 타입에 따른 파티클 생성
	void SpawnHitParticle(EHitType HitType, const FVector& Location, const FRotator& Rotation);
	
	// 적중 타입에 따라 다른 효과음 재생
	void PlayHitSound(EHitType HitType, const FVector& Location);

	// 캐릭터의 직업에 따른 RowName을 얻음
	FName GetRowClassName();
};
