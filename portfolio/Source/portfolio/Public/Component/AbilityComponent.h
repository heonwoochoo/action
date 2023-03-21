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

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FCharacterData CharacterData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCharacterSkillAsset* CharacterSkillAsset;

	AportfolioCharacter* Character;


	/** Assassin skill */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AAssassin_SkillOne> SkillOneClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AAssassin_SkillOne* SkillOne;



public:
	UFUNCTION(BlueprintCallable)
	const FCharacterData GetCharacterData();

	FORCEINLINE UCharacterSkillAsset* GetCharacterSkillAsset() const { return CharacterSkillAsset; }

	void HandleSkillOne();
	void HandleSkillTwo();
	void HandleSkillThree();
	void HandleSkillFour();


	UFUNCTION(BlueprintCallable)
	AAssassin_SkillOne* GetSkillOne() const;
};
