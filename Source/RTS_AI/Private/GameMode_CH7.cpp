#include "GameMode_CH7.h"

#include "AIController_CH7.h"
#include "PlayerController_Ch7.h"
#include "Kismet/GameplayStatics.h"

void AGameMode_CH7::PostLogin(APlayerController* NewPlayer)
{
	if(APlayerController_Ch7* castedPC = Cast<APlayerController_Ch7>(NewPlayer))
	{
		_PlayerController = castedPC;
		_PlayerController->Init();
	}
	
	Super::PostLogin(NewPlayer);
}

void AGameMode_CH7::Logout(AController* Exiting)
{
	if(Exiting == _PlayerController)
	{
		_PlayerController = nullptr;
	}
	
	Super::Logout(Exiting);
}

void AGameMode_CH7::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> outActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIController_CH7::StaticClass(), outActors);
	for(AActor* actor : outActors)
	{
		_AIControllers.Add(Cast<AAIController_CH7>(actor));
	}
	for(AAIController_CH7* ai : _AIControllers)
	{
		ai->Init();
		ai->OnControllerDeath.AddDynamic(this, &AGameMode_CH7::Handle_ControllerDeath);
	}
}

void AGameMode_CH7::Handle_ControllerDeath(AController* casuer, int points)
{
	_PlayerController->AddPoints(points);
}
