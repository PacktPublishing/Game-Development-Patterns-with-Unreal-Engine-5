#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Score_CH7.generated.h"

class UTextBlock;
UCLASS(Abstract)
class RTS_AI_API UWidget_Score_CH7 : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void UpdatePoints(int newPoints);

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> ScoreText;
	
};
