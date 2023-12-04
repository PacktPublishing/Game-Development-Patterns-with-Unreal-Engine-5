#include "PlayerController_Ch7.h"

#include "Character_CH7.h"
#include "Widget_Score_CH7.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

void APlayerController_Ch7::Init()
{
	_ScoreWidget = CreateWidget<UWidget_Score_CH7, APlayerController_Ch7>(this, _ScoreWidgetClass.Get());
	_ScoreWidget->AddToViewport();
}