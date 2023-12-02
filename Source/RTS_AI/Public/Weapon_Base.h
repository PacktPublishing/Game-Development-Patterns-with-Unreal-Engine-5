#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon_Base.generated.h"

class UArrowComponent;

UCLASS(Abstract)
class RTS_AI_API AWeapon_Base : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> _Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UArrowComponent> _FirePoint;
	
	AWeapon_Base();
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void Fire();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int _AmmoPerFire;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	int _CurrentAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int _MaxAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _RoF;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _Range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _DamagePerHit;

	UPROPERTY(BlueprintReadWrite)
	bool _CanFire;
	UPROPERTY(BlueprintReadWrite)
	FTimerHandle _TimerFireDelay;
	UFUNCTION()
	void Handle_FireDelay();
	
	
};
