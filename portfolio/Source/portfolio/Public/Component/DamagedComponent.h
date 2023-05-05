// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamagedComponent.generated.h"

class ADamageText;
class UMaterialInstance;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_API UDamagedComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDamagedComponent();

protected:
	virtual void BeginPlay() override;

	// �ǰݽ� ����� �������� ��Ƽ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	UMaterialInstance* HitMaterialInstance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Combat", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ADamageText> DamageTextClass;

	// ��Ʈ �������� ���� Ÿ�̸�
	FTimerHandle HitOverlayTimerHandle;

	// �ǰݽ� ����� �������� ���ӵǴ� �ð�
	float HitOutlineDurationTime = 5.f;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// �ǰݽ� �������� �Ӹ�Ƽ�� ����
	void ApplyHitOverlayMaterial();

	// ��Ʈ �������� Ÿ�̸� ��� -> �޽��� ����� ���� ����
	void OnEndHitOveralyTimer();

	// �ǰݽ� �޽��� �ƿ������� ���������� ǥ��
	void ChangeMeshOutline();

	// �ƿ����� ����
	// ���� �ð����� �ǰ� ���� ��� �Ǵ� ����� ȣ��
	void RemoveMeshOutline();

	FTimerHandle MeshOutlineTimerHandle;

	/** 
	* ĳ���� �Ӹ� ���� ���� ������ �ؽ�Ʈ�� ����մϴ�.
	* @param DamageAmount - ������
	* @param IsCritical - ũ��Ƽ���� �޾Ҵ���?
	*/
	void ShowDamageText(const float& DamageAmount, const bool& IsCritical);

	// �����ڿ��� ũ��Ƽ�� �������� �޾Ҵ���?
	bool IsDamagedCritical(AActor* DamageCauser);

};
