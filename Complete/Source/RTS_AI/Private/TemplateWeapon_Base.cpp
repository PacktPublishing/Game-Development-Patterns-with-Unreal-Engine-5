#include "TemplateWeapon_Base.h"

void ATemplateWeapon_Base::Fire()
{
	if(!_CanFire) return;
	
	if(CheckAmmo())
	{
		PlayEffects();
		ProcessFiring();
		UpdateAmmo();
		Super::Fire();
		return;
	}
	
	Reload();
}

void ATemplateWeapon_Base::Reload_Implementation()
{
	_CurrentAmmo = _MaxAmmo;
	Handle_FireDelay();
}

bool ATemplateWeapon_Base::CheckAmmo_Implementation()
{
	return _AmmoPerFire <= _CurrentAmmo;
}

void ATemplateWeapon_Base::UpdateAmmo_Implementation()
{
	_CurrentAmmo -= _AmmoPerFire;
}
