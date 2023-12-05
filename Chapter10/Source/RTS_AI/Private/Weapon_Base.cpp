#include "Weapon_Base.h"

#include "Components/ArrowComponent.h"

AWeapon_Base::AWeapon_Base()
{
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = _Root;
	
	_FirePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePoint"));
	_FirePoint->SetupAttachment(RootComponent);

	_AmmoPerFire = 1;
	_CurrentAmmo = 0;
	_MaxAmmo = 12;
	_RoF = 1.f;
	_CanFire = true;
	_Range = 1000.f;
	_DamagePerHit = 100.f;
}

void AWeapon_Base::BeginPlay()
{
	Super::BeginPlay();
	_CurrentAmmo = _MaxAmmo;
}

void AWeapon_Base::Fire()
{
	_CanFire = false;
	GetWorld()->GetTimerManager().SetTimer(_TimerFireDelay, this, &AWeapon_Base::Handle_FireDelay, 1.f/_RoF, false);
	return;
}

void AWeapon_Base::Handle_FireDelay()
{
	GetWorld()->GetTimerManager().ClearTimer(_TimerFireDelay);
	_CanFire = true;
}