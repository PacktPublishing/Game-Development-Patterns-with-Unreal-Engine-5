// Fill out your copyright notice in the Description page of Project Settings.


#include "GuardTower_CH5_2.h"

#include "Components/ArrowComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AGuardTower_CH5_2::AGuardTower_CH5_2()
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
	
	T_RotateLight = CreateDefaultSubobject<UTimelineComponent>(TEXT("T_RotateLight"));
	onTimeline_Update.BindUFunction(this, FName("Handle_RotateLight_Update"));
	onTimeline_Finished.BindUFunction(this, FName("Handle_RotateLight_Finished"));
}

// Called when the game starts or when spawned
void AGuardTower_CH5_2::BeginPlay()
{
	Super::BeginPlay();

	if(_Curve == nullptr) { return;}
	T_RotateLight->AddInterpFloat(_Curve, onTimeline_Update, FName("Alpha"));
	T_RotateLight->SetTimelineFinishedFunc(onTimeline_Finished);
	T_RotateLight->SetLooping(false);
	T_RotateLight->SetIgnoreTimeDilation(true);
	StartRotation();
}

void AGuardTower_CH5_2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	FVector startLocation = _Arrow->GetComponentLocation();
	FVector endLocation = startLocation + (_Arrow->GetForwardVector() * _DetectionRange);
	FHitResult hit;
	TArray<AActor*> ActorsToIgnore;
	UKismetSystemLibrary::SphereTraceSingle(GetWorld(), startLocation, endLocation, _DetectionRadius,
		UEngineTypes::ConvertToTraceType(ECC_Visibility), false,
		ActorsToIgnore, EDrawDebugTrace::ForOneFrame, hit, true);

	ACharacter* otherCasted = Cast<ACharacter>(hit.GetActor());
	_EnemySpotted = (otherCasted != nullptr);

	if(_EnemySpotted)
	{
		StopRotation();
	}
}

void AGuardTower_CH5_2::Handle_RotateLight_Update(float val)
{
	_LightPivot->SetRelativeRotation(
		FRotator(0.f, FMath::Lerp(-40.f, 40.f, val), 0.f)
		);
}

void AGuardTower_CH5_2::Handle_RotateLight_Finished()
{
	_RotateForward = !_RotateForward;
	StartRotation();
}

void AGuardTower_CH5_2::StartRotation()
{
	if(_RotateForward)
	{
		T_RotateLight->Play();
	}
	else
	{
		T_RotateLight->Reverse();
	}
}

void AGuardTower_CH5_2::StopRotation()
{
	T_RotateLight->Stop();
}
