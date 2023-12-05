#include "Command_UnitMove.h"

#include "ControllableUnit.h"

void UCommand_UnitMove::Init(AActor* unit, FVector moveLocation)
{
	_unit = unit;
	_moveLocation = moveLocation;
}

void UCommand_UnitMove::Execute()
{
	Super::Execute();

	IControllableUnit::Execute_SetMoveLocation(_unit, _moveLocation);
}
