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

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FCharacterData CharacterData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCharacterSkillAsset* CharacterSkillAsset;

	AportfolioCharacter* Character;

	UAnimInstanceBase* AnimInstance;

	UAnimMontage* SkillOneAnimation;

	// Assassin project weapon
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AKnifeProjectile> KinfeProjectileClass;

	AKnifeProjectile* KinfeProjectile;

	/** Assassin skill */
	void HandleAssassinSkillOne();
	
	AActor* FindEnemy();
	float TraceDistance = 2000.f;

	void HandleAssassinSkillTwo();
	void HandleAssassinSkillThree();
	void HandleAssassinSkillFour();
	/** ====================================*/
public:
	UFUNCTION(BlueprintCallable)
	const FCharacterData GetCharacterData();

	void HandleSkillOne();
	void HandleSkillTwo();
	void HandleSkillThree();
	void HandleSkillFour();

	/** Assassin skill */
	UFUNCTION(BlueprintCallable)
	void ThrowKnife();
};
