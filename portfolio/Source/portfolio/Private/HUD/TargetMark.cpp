#include "HUD/TargetMark.h"
#include "HUD/TargetWidgetComponent.h"
#include "portfolio/portfolioCharacter.h"
#include "Camera/CameraComponent.h"
#include "Enemy/EnemyBase.h"

ATargetMark::ATargetMark()
{
 	PrimaryActorTick.bCanEverTick = true;

	TargetWidgetComponent = CreateDefaultSubobject<UTargetWidgetComponent>(TEXT("TargetWidgetComponent"));
	if (TargetWidgetComponent) SetRootComponent(TargetWidgetComponent);
	

}

void ATargetMark::BeginPlay()
{
	Super::BeginPlay();

	AEnemyBase* Enemy = Cast<AEnemyBase>(GetOwner());
	if (Enemy) Enemy->SetHeadUpMark(this);

	SetLifeSpan(Duration);
}


void ATargetMark::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AportfolioCharacter* Character = Cast<AportfolioCharacter>(GetInstigator());
	const FRotator Rotation = (Character->GetFollowCamera()->GetComponentLocation() - GetActorLocation()).ToOrientationQuat().Rotator();
	TargetWidgetComponent->SetWorldRotation(Rotation);
}

void ATargetMark::SetDurtation(float Time)
{
	if (Time > 0.f) Duration = Time;
	else Duration = 0.f;
}

