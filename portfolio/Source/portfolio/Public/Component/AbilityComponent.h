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
	void HandleAssassinSkillOneFirst();
	void HandleAssassinSkillOneSecond();

	// 트레이스로 enemy를 찾아 수리검을 날릴 방향 설정
	AActor* FindEnemy();
	AActor* TargetEnemy = nullptr;
	// 수리검에 맞은 적을 연계 스킬 타겟으로 설정 (enemy에 표식이 종료되면 함께 해제됨)
	AActor* DashTarget = nullptr;

	float TraceDistance = 2000.f;
	void RotateCharacterBodyToTarget(AActor* Target);

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

	UAnimMontage* GetSkillOneAnimation() const;

	/** Assassin skill */
	UFUNCTION(BlueprintCallable)
	void ThrowKnife();
	UFUNCTION(BlueprintCallable)
	void ResetTarget();
	void SetDashTarget(AActor* Target);
};
