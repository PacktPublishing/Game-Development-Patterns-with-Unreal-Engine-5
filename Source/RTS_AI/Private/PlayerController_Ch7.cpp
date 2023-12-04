#include "PlayerController_Ch7.h"

#include "Character_CH7.h"
#include "Widget_Score_CH7.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

void APlayerController_Ch7::Init()
{
	if(GetPawn() != nullptr) {GetPawn()->Destroy();}
	UWorld* const world = GetWorld();
	AActor* tempStart = UGameplayStatics::GetGameMode(world)->FindPlayerStart(this);
	FVector spawnLoc = tempStart != nullptr ? tempStart->GetActorLocation() : FVector::ZeroVector;
	FRotator spawnRot = tempStart != nullptr ? tempStart->GetActorRotation() : FRotator::ZeroRotator;
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	_Character = world->SpawnActor<ACharacter_CH7>(_CharacterClass.Get(), spawnLoc, spawnRot, spawnParams);
	Possess(_Character);
	_Character->Init();

	_ScoreWidget = CreateWidget<UWidget_Score_CH7, APlayerController_Ch7>(this, _ScoreWidgetClass.Get());
	_ScoreWidget->AddToViewport();
}

void APlayerController_Ch7::AddPoints(int points)
{
	UE_LOG(LogTemp, Warning, TEXT("PlayerCotroller handling Add Points"));

	_Points += points;
	_ScoreWidget->UpdatePoints(_Points);
}
