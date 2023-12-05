#pragma once

#include "CoreMinimal.h"
#include "Weapon_Base.h"
#include "TemplateWeapon_Base.generated.h"

UCLASS(Abstract)
class RTS_AI_API ATemplateWeapon_Base : public AWeapon_Base
{
	GENERATED_BODY()

public:
	virtual void Fire() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Reload();
	
protected:

	UFUNCTION(BlueprintNativeEvent)
	bool CheckAmmo();
	UFUNCTION(BlueprintImplementableEvent)
	void ProcessFiring();
	UFUNCTION(BlueprintImplementableEvent)
	void PlayEffects();
	UFUNCTION(BlueprintNativeEvent)
	void UpdateAmmo();

};
