#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterTypes.h"
#include "AbilityComponent.generated.h"

class UCharacterDataAsset;
class AportfolioCharacter;
class UAnimMontage;
class UCharacterSkillAsset;
class UAnimInstanceBase;
class AKnifeProjectile;
class AAssassin_SkillOne;

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

	AportfolioCharacter* Character;

	UAnimInstanceBase* AnimInstance;

	/** One */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	FCharacterSkill SkillOne;

	bool bCanSkillOne = true;

	FTimerHandle SkillOneHandle;
	
	void EndSkillOneTimer();
	
	void SetSkillOneTimer();

	/** Two */
	/** Three */
	/** Four */

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UDataTable* SkillDataTable;

	/** One */
	UFUNCTION(BlueprintCallable)
	virtual void HandleSkillOne();

	FORCEINLINE FCharacterSkill& GetSkillOne() { return SkillOne; }
	FORCEINLINE bool GetCanSkillOne() const { return bCanSkillOne; }
	FORCEINLINE FTimerHandle GetSkillOneHandle() const { return SkillOneHandle; }

	/** Two */
	/** Three */
	/** Four */
};
