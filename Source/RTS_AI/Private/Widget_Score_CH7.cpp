#include "Widget_Score_CH7.h"

#include "Components/TextBlock.h"

void UWidget_Score_CH7::NativeConstruct()
{
	Super::NativeConstruct();

	if(ScoreText)
	{
		ScoreText->SetText(FText::FromString("Points: 0"));
	}
}

void UWidget_Score_CH7::UpdatePoints(int newPoints)
{
	if(ScoreText)
	{
		ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Points: %d"), newPoints)));
	}
}
