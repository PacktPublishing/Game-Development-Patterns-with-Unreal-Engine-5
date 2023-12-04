#include "EliteUnit.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

AEliteUnit::AEliteUnit()
{
}

void AEliteUnit::Init(UBlackboardComponent* inBlackboard)
{
	_isMoving = false;
	_Blackboard = inBlackboard;
}

void AEliteUnit::StopMoving_Implementation()
{
	_isMoving = false;
	
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
		UGameplayStatics::ApplyDamage(traceResult.GetActor(), 100.0f, GetController(), this, UDamageType::StaticClass());
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No Line of sight"));
	}
}

void AEliteUnit::QueueMoveLocation_Implementation(FVector targetLocation)
{
	
}

void AEliteUnit::MoveLocationReached_Implementation()
{

	
	Execute_StopMoving(this);
}
