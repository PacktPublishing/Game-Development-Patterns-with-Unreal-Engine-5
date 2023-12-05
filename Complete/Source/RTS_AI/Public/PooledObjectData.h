#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "PooledObjectData.generated.h"

USTRUCT(BlueprintType)
struct FPooledObjectData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> _ActorTemplate;
	UPROPERTY(EditAnywhere)
	int _PoolSize;
	UPROPERTY(EditAnywhere)
	bool _CanGrow;
	UPROPERTY(EditAnywhere)
	FString _ActorName;

	FPooledObjectData()
	{
		_ActorTemplate = nullptr;
		_PoolSize = 1;
		_CanGrow = false;
		_ActorName = "default";
	}
};
