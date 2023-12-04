#include "GameMode_CH7.h"

#include "AIController_CH7.h"
#include "PlayerController_Ch7.h"
#include "Kismet/GameplayStatics.h"

void AGameMode_CH7::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void AGameMode_CH7::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
}

void AGameMode_CH7::BeginPlay()
{
	Super::BeginPlay();
}

void AGameMode_CH7::Handle_ControllerDeath(AController* casuer, int points)
{
}
