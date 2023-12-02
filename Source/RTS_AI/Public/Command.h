#pragma once

#include "CoreMinimal.h"
#include "Command.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType)
class RTS_AI_API UCommand : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	virtual void Execute();
};
