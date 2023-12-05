#include "GuardTower_CH5_1.h"

#include "Components/ArrowComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

AGuardTower_CH5_1::AGuardTower_CH5_1()
{
	PrimaryActorTick.bCanEverTick = true;
	_RotateForward = true;
	_EnemySpotted = false;
	_DetectionRange = 4000.f;
	_DetectionRadius = 250.f;

	_TowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerMesh"));
	RootComponent = _TowerMesh;
	
	_LightPivot = CreateDefaultSubobject<USceneComponent>(TEXT("LightPivot"));
	_LightPivot->SetupAttachment(_TowerMesh);
	
	_LightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightMesh"));
	_LightMesh->SetupAttachment(_LightPivot);
	
	_SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	_SpotLight->SetupAttachment(_LightMesh);
	
	_Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	_Arrow->SetupAttachment(_LightMesh);
}

void AGuardTower_CH5_1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector startLocation = _Arrow->GetComponentLocation();
	FVector endLocation = _Arrow->GetComponentLocation() + (_Arrow->GetForwardVector() * _DetectionRange);
	FHitResult hit;
	TArray<AActor*> ActorsToIgnore;
	UKismetSystemLibrary::SphereTraceSingle(GetWorld(), startLocation, endLocation, _DetectionRadius,
		UEngineTypes::ConvertToTraceType(ECC_Visibility), false,
		ActorsToIgnore, EDrawDebugTrace::ForOneFrame, hit, true);

	ACharacter* otherCasted = Cast<ACharacter>(hit.GetActor());
	_EnemySpotted = (otherCasted != nullptr);

	if(!_EnemySpotted)
	{
		if(_RotateForward)
		{
			_LightPivot->AddLocalRotation(FRotator(0.0, 0.2, 0.0));
			if(FMath::IsNearlyEqual(_LightPivot->GetRelativeRotation().Yaw, 40.f))
			{
				_RotateForward = false;
			}
		}
		else
		{
			_LightPivot->AddLocalRotation(FRotator(0.0, -0.2, 0.0));
			if(FMath::IsNearlyEqual(_LightPivot->GetRelativeRotation().Yaw, -40.f))
			{
				_RotateForward = true;
			}
		}
	}
}

