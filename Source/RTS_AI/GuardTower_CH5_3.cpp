#include "GuardTower_CH5_3.h"

#include "Components/ArrowComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

AGuardTower_CH5_3::AGuardTower_CH5_3()
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

	_Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	_Sphere->SetupAttachment(_LightMesh);
	_Sphere->OnComponentBeginOverlap.AddDynamic(this, &AGuardTower_CH5_3::OnSphereOverlapBegin);
	_Sphere->OnComponentEndOverlap.AddDynamic(this, &AGuardTower_CH5_3::OnSphereOverlapEnd);
	
	T_RotateLight = CreateDefaultSubobject<UTimelineComponent>(TEXT("T_RotateLight"));
	onTimeline_Update.BindUFunction(this, FName("Handle_RotateLight_Update"));
	onTimeline_Finished.BindUFunction(this, FName("Handle_RotateLight_Finished"));
}

void AGuardTower_CH5_3::BeginPlay()
{
	Super::BeginPlay();

	if(_Curve == nullptr) { return;}
	T_RotateLight->AddInterpFloat(_Curve, onTimeline_Update, FName("Alpha"));
	T_RotateLight->SetTimelineFinishedFunc(onTimeline_Finished);
	T_RotateLight->SetLooping(false);
	T_RotateLight->SetIgnoreTimeDilation(true);
	StartRotation();
}

void AGuardTower_CH5_3::Handle_RotateLight_Update(float val)
{
	_LightPivot->SetRelativeRotation(
		FRotator(0.f, FMath::Lerp(-40.f, 40.f, val), 0.f));
}

void AGuardTower_CH5_3::Handle_RotateLight_Finished()
{
	_RotateForward = !_RotateForward;
	StartRotation();
}

void AGuardTower_CH5_3::StartRotation()
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

void AGuardTower_CH5_3::StopRotation()
{
	T_RotateLight->Stop();
}

void AGuardTower_CH5_3::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	if(_EnemyUnit != nullptr) {return;}

	_EnemyUnit = Cast<ACharacter>(OtherActor);
	if(_EnemyUnit == nullptr) {return;}
	
	FHitResult hit(ForceInit);
	FVector start = _Arrow->GetComponentLocation();
	FVector end = _EnemyUnit->GetActorLocation();
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(_EnemyUnit);
	if(UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end,
		UEngineTypes::ConvertToTraceType(ECC_Visibility), false,
		ActorsToIgnore, EDrawDebugTrace::ForDuration, hit, true, FLinearColor::Red,
		FLinearColor::Green, 0.5f))
	{
		if(hit.GetActor() != OtherActor) return;
	}
	
	_EnemySpotted = true;
	StopRotation();
}

void AGuardTower_CH5_3::OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(_EnemyUnit != OtherActor) {return;}
	
	_EnemySpotted = false;
	_EnemyUnit = nullptr;
	StartRotation();
}
