#include "AIController_CH7.h"

#include "AIUnit_CH7.h"

void AAIController_CH7::Init()
{
	if(APawn* pawn = GetPawn())
	{
		if(_Unit = Cast<AAIUnit_CH7>(pawn))
		{

			_Unit->Init();
			_Unit->OnUnitDeath.AddUniqueDynamic(this, &AAIController_CH7::Handle_UnitDeath);
		}
	}
}

void AAIController_CH7::Handle_UnitDeath(AController* causer, int points)
{
	OnControllerDeath.Broadcast(causer, points);
}
