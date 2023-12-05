#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AIUnit_CH7.generated.h"

class UHealthComponent;


UCLASS(Abstract)
class RTS_AI_API AAIUnit_CH7 : public APawn
{
	GENERATED_BODY()

public:
	AAIUnit_CH7();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int _PointValue;
};