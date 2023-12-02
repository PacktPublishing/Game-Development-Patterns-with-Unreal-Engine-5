#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Command.h"
#include "ControllableUnit.h"
#include "GameFramework/Character.h"
#include "Containers/Queue.h"
#include "EliteUnit.generated.h"

class AWeapon_Base;
UCLASS(Abstract)
class RTS_AI_API AEliteUnit : public ACharacter, public IControllableUnit
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> _WeaponAttachPoint;

	AEliteUnit();
	
	UFUNCTION(BlueprintCallable)
	void Init(UBlackboardComponent* inBlackboard);
	
	virtual void StopMoving_Implementation() override;
	virtual void SetMoveLocation_Implementation(FVector targetLocation) override;
	virtual void QueueMoveLocation_Implementation(FVector targetLocation) override;
	virtual void AttackTarget_Implementation(UObject* target) override;
	virtual void MoveLocationReached_Implementation() override;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AAIController> _AIController;
	UPROPERTY(VisibleInstanceOnly)
	TObjectPtr<UBlackboardComponent> _Blackboard;
	UPROPERTY(VisibleInstanceOnly)
	bool _isMoving;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon_Base> _WeaponToSpawn;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	TObjectPtr<AWeapon_Base> _Weapon;

	TQueue<TObjectPtr<UCommand>> _CommandQueue;
};
