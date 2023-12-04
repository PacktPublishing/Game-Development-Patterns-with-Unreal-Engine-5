#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_RTS.generated.h"

UCLASS()
class RTS_AI_API APC_RTS : public APlayerController
{
	GENERATED_BODY()
public:
	APC_RTS();
	
protected:
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(VisibleInstanceOnly)
	TObjectPtr<AActor> _SelectedUnit;
	UPROPERTY(VisibleInstanceOnly)
	bool _isQueueing;
	
	void Select();
	void ActionReleased();
	void StartQueueing();
	void StopQueueing();
};
