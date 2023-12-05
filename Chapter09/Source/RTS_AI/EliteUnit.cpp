#include "EliteUnit.h"

#include "Command_UnitMove.h"
#include "Weapon_Base.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

AEliteUnit::AEliteUnit()
{
	_WeaponAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponAttachPoint"));
	_WeaponAttachPoint->SetupAttachment(RootComponent);
}

void AEliteUnit::Init(UBlackboardComponent* inBlackboard)
{
	_isMoving = false;
	_Blackboard = inBlackboard;

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = this;
	TObjectPtr<AActor> spawnedWeapon = GetWorld()->SpawnActor(_WeaponToSpawn, &_WeaponAttachPoint->GetComponentTransform(), spawnParams);
	spawnedWeapon->AttachToComponent(_WeaponAttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
	_Weapon = Cast<AWeapon_Base>(spawnedWeapon);
}

void AEliteUnit::StopMoving_Implementation()
{
	_isMoving = false;
	_CommandQueue.Empty();
	
	_Blackboard->SetValueAsBool("HasMoveLocation", false);
	_Blackboard->ClearValue("MoveToLocation");
	
}

void AEliteUnit::SetMoveLocation_Implementation(FVector targetLocation)
{
	_isMoving = true;
	
	_Blackboard->SetValueAsBool("HasMoveLocation", true);
	_Blackboard->SetValueAsVector("MoveToLocation", targetLocation);
}

void AEliteUnit::AttackTarget_Implementation(UObject* target)
{
	AActor* targetActor = Cast<AActor>(target);
	if(!targetActor) return;

	FHitResult traceResult(ForceInit);
	if(!UKismetSystemLibrary::LineTraceSingle(GetWorld(), GetActorLocation(), targetActor->GetActorLocation(),
		UEngineTypes::ConvertToTraceType(ECC_Visibility), false,
		{this}, EDrawDebugTrace::ForDuration, traceResult, true,
		FLinearColor::Red, FLinearColor::Green, 5)) return;

	if(traceResult.GetActor() == targetActor)
	{
		_Weapon->Fire();
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No Line of sight"));
	}
}

void AEliteUnit::QueueMoveLocation_Implementation(FVector targetLocation)
{
	if(!_isMoving)
	{
		Execute_SetMoveLocation(this, targetLocation);
		return;
	}
	
	TObjectPtr<UCommand_UnitMove> moveCommand = NewObject<UCommand_UnitMove>(this);
	moveCommand->Init(this, targetLocation);
	_CommandQueue.Enqueue(moveCommand);
}

void AEliteUnit::MoveLocationReached_Implementation()
{
	if(!_CommandQueue.IsEmpty())
	{
		TObjectPtr<UCommand> command;
		_CommandQueue.Dequeue(command);
		command->Execute();
		return;
	}
	
	Execute_StopMoving(this);
}
