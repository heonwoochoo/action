// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Boss/Gideon/BossGideon.h"
#include "Animation/BossAnimInstance.h"
#include "Component/BossAbilityComponent.h"
#include "DefaultCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Controller/CharacterController.h"
#include "HUD/HUDBase.h"

ABossGideon::ABossGideon()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilityComponent = CreateDefaultSubobject<UBossAbilityComponent>(TEXT("AbilityComponent"));
}

void ABossGideon::BeginPlay()
{
	Super::BeginPlay();
}

void ABossGideon::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void ABossGideon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (State == EBossState::EBS_Chasing && 
		GetVelocity().Length() == 0.f && 
		State != EBossState::EBS_Dead)
	{
		if (AbilityComponent)
		{
			// 랜덤 패턴으로 공격
			int32 RandNum = FMath::RandRange(0, 2);

			switch (RandNum)
			{
			case 0:
				AbilityComponent->Attack();
				break;
			case 1:
				AbilityComponent->HandleSkillOne();
				break;
			case 2:
				AbilityComponent->HandleSkillTwo();
				break;
			}
		}
	}
}

float ABossGideon::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return 0.0f;
}

void ABossGideon::Die()
{
	Super::Die();

	State = EBossState::EBS_Dead;
	Tags.Add(FName("Dead"));

	UBossAnimInstance* AnimInstance = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->ClearTimerHandle();
		AnimInstance->PlayDeadAnimation();
	}

	if (CombatTarget)
	{
		ADefaultCharacter* DefaultCharacter = Cast<ADefaultCharacter>(CombatTarget);
		if (DefaultCharacter)
		{
			// 유저가 경험치를 획득
			DefaultCharacter->UpdateStatManager(EStatTarget::EST_Exp, EStatUpdateType::ESUT_Plus, Stats.Exp);

			ACharacterController* CharacterController = Cast<ACharacterController>(DefaultCharacter->GetController());
			if (CharacterController)
			{
				AHUDBase* HUDBase = Cast<AHUDBase>(CharacterController->GetHUD());
				if (HUDBase)
				{
					const FText& Message = FText::FromString(TEXT("보스를 처치하였습니다."));
					HUDBase->NotifyMessageToUser(Message);
				}
			}
		}
	}

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
}
