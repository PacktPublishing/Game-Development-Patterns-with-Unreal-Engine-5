// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ControllableUnit.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UControllableUnit : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTS_AI_API IControllableUnit
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetMoveLocation(FVector targetLocation);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void QueueMoveLocation(FVector targetLocation);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StopMoving();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AttackTarget(UObject* target);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void MoveLocationReached();
};
