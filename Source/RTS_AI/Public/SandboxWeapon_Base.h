#pragma once

#include "CoreMinimal.h"
#include "Weapon_Base.h"
#include "SandboxWeapon_Base.generated.h"

UCLASS(Abstract)
class RTS_AI_API ASandboxWeapon_Base : public AWeapon_Base
{
	GENERATED_BODY()

public:
	virtual void Fire() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void SandboxFire();
	UFUNCTION(BlueprintCallable)
	void Reload();
	
protected:
	
	UFUNCTION(BlueprintCallable)
	bool CheckAmmo();
	UFUNCTION(BlueprintCallable)
	void LinetraceOneShot(FVector direction);
	UFUNCTION(BlueprintCallable)
	void PlaySound(USoundBase* sound);
	UFUNCTION(BlueprintCallable)
	void UpdateAmmo();
};
