#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	_maxHealth = 100.f;
}

void UHealthComponent::InitializeNewMaxHealth(float newMax)
{
	_maxHealth = newMax;
	_currentHealth = _maxHealth;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	_currentHealth = _maxHealth; 
}

void UHealthComponent::DamageTaken(AActor* damagedActor, float damage, const UDamageType* damageType, AController* instigator, AActor* causer)
{
	_currentHealth=FMath::Max(_currentHealth - damage, 0.f); 

	onComponentDamaged.Broadcast(instigator, damage, _currentHealth); 

	if(_currentHealth <= 0.f)
	{
		onComponentDead.Broadcast(instigator);
	} 
}

