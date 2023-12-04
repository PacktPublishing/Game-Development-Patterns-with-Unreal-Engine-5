#include "AIUnit_CH7.h"

#include "RTS_AI/HealthComponent.h"

AAIUnit_CH7::AAIUnit_CH7()
{
	_HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

void AAIUnit_CH7::Init()
{
	_HealthComp->onComponentDead.AddUniqueDynamic(this, &AAIUnit_CH7::Handle_HealthDead);
}

void AAIUnit_CH7::Handle_HealthDead(AController* causer)
{
	OnUnitDeath.Broadcast(causer, _PointValue);
	Destroy();
}
