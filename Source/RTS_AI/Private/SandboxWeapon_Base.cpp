#include "SandboxWeapon_Base.h"

#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"

void ASandboxWeapon_Base::Fire()
{
	SandboxFire();
}

void ASandboxWeapon_Base::Reload()
{
	_CurrentAmmo = _MaxAmmo;
	Handle_FireDelay();
}

bool ASandboxWeapon_Base::CheckAmmo()
{
	return _AmmoPerFire <= _CurrentAmmo;
}

void ASandboxWeapon_Base::LinetraceOneShot(FVector direction)
{
	FHitResult hit(ForceInit);
	FVector start = _FirePoint->GetComponentLocation();
	FVector end = start + (direction * _Range);
	if(!UKismetSystemLibrary::LineTraceSingle(GetWorld(),
		start, end,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,
		{this, GetOwner()},
		EDrawDebugTrace::ForDuration,
		hit,
		true,
		FLinearColor::Red, FLinearColor::Green, 5))
			return;
	
	UGameplayStatics::ApplyDamage(hit.GetActor(), _DamagePerHit, GetInstigatorController(), GetOwner(), UDamageType::StaticClass());
}

void ASandboxWeapon_Base::PlaySound(USoundBase* sound)
{
	UGameplayStatics::PlaySoundAtLocation(this, sound, GetActorLocation());
}

void ASandboxWeapon_Base::UpdateAmmo()
{
	_CurrentAmmo -= _AmmoPerFire;
}
