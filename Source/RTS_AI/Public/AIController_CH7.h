#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_CH7.generated.h"

class AAIUnit_CH7;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAIControllerDeathSignature, AController*, casuer, int, points);

UCLASS(Abstract)
class RTS_AI_API AAIController_CH7 : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FAIControllerDeathSignature OnControllerDeath;
	
	void Init();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AAIUnit_CH7> _Unit;

	UFUNCTION()
	void Handle_UnitDeath(AController* causer, int points);
};
