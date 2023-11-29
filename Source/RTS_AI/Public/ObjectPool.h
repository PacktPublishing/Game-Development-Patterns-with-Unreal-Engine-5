#pragma once

#include "CoreMinimal.h"
#include "PooledObjectData.h"
#include "GameFramework/Actor.h"
#include "ObjectPool.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPoolerCleanupSignature);

class UPooledObject;

USTRUCT(BlueprintType)
struct FSingleObjectPool
{
	GENERATED_BODY()

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	TArray<TObjectPtr<UPooledObject>> _PooledObjects;
};

UCLASS()
class RTS_AI_API AObjectPool : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FPoolerCleanupSignature OnPoolerCleanup;

	UFUNCTION(BlueprintCallable)
	void Broadcast_PoolerCleanup();

	UFUNCTION(BlueprintCallable)
	AActor* GetPooledActor(FString name);
	
	UFUNCTION(BlueprintCallable)
	void RecyclePooledObject(UPooledObject* poolCompRef);

	UFUNCTION(BlueprintCallable)
	void RecycleActor(AActor* pooledActor);
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPooledObjectData> _PooledObjectData;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	TArray<FSingleObjectPool> _Pools;

private:
	void RegenItem(int poolIndex, int positionIndex);
};
