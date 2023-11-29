#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Net/Core/Trace/NetTrace.h"
#include "PooledObject.generated.h"

class AObjectPool;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RTS_AI_API UPooledObject : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	bool _IsActive;
	
	void Init(AObjectPool* owner);

	UFUNCTION(BlueprintCallable)
	void RecycleSelf();
private:
	TObjectPtr<AObjectPool> _ObjectPool;
	
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
};
