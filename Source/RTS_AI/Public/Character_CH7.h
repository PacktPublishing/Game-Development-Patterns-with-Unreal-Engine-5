#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character_CH7.generated.h"

UCLASS(Abstract)
class RTS_AI_API ACharacter_CH7 : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacter_CH7();

	void Init();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UFUNCTION()
	void Fire();
};
