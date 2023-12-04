#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AIUnit_CH7.generated.h"

class UHealthComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAIUnitDeathSignature, AController*, causer, int, points);

UCLASS(Abstract)
class RTS_AI_API AAIUnit_CH7 : public APawn
{
	GENERATED_BODY()

public:
	AAIUnit_CH7();

	UPROPERTY(BlueprintAssignable)
	FAIUnitDeathSignature OnUnitDeath;
	
	void Init();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UHealthComponent> _HealthComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int _PointValue;
	
	UFUNCTION()
	void Handle_HealthDead(AController* causer);
};
