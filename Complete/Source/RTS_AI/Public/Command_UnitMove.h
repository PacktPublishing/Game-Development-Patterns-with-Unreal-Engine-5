#pragma once

#include "CoreMinimal.h"
#include "Command.h"
#include "Command_UnitMove.generated.h"

UCLASS()
class RTS_AI_API UCommand_UnitMove : public UCommand
{
	GENERATED_BODY()

public:
	void Init(AActor* unit, FVector moveLocation);
	virtual void Execute() override;

private:
	TObjectPtr<AActor> _unit;
	FVector _moveLocation;
};
