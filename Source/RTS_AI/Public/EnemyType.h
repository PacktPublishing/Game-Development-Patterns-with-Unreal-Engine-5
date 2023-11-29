#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemyType.generated.h"

UCLASS(BlueprintType)
class RTS_AI_API UEnemyType : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMaterialInstance> _Material1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMaterialInstance> _Material2;
};
