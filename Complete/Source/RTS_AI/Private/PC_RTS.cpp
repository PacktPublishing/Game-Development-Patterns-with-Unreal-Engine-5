// Fill out your copyright notice in the Description page of Project Settings.


#include "PC_RTS.h"

#include "ControllableUnit.h"
#include "Kismet/KismetSystemLibrary.h"

APC_RTS::APC_RTS()
{
	_SelectedUnit = nullptr;
	_isQueueing = false;
}

void APC_RTS::SetupInputComponent()
{
	
	Super::SetupInputComponent();

	InputComponent->BindAction("Select",IE_Pressed, this, &APC_RTS::Select);
	
	InputComponent->BindAction("Action", IE_Released, this, &APC_RTS::ActionReleased);

	InputComponent->BindAction("Queue", IE_Pressed, this, &APC_RTS::StartQueueing);
	InputComponent->BindAction("Queue", IE_Released, this, &APC_RTS::StopQueueing);

	bShowMouseCursor  = true;
}

void APC_RTS::Select()
{
	FHitResult traceResult;
	if(GetHitResultUnderCursorForObjects({UEngineTypes::ConvertToObjectType(ECC_Pawn)}, true, traceResult))
	{
		if(UKismetSystemLibrary::DoesImplementInterface(traceResult.GetActor(), UControllableUnit::StaticClass()))
		{
			_SelectedUnit = traceResult.GetActor();
		}
	}
}

void APC_RTS::ActionReleased()
{
	if(!_SelectedUnit) return;
	
	FHitResult traceResult;
	if(!GetHitResultUnderCursor(ECC_Visibility, true, traceResult)) return;

	if(!_isQueueing)
	{
		IControllableUnit::Execute_StopMoving(_SelectedUnit);
		IControllableUnit::Execute_SetMoveLocation(_SelectedUnit, traceResult.Location);
	}
	else
	{
		IControllableUnit::Execute_QueueMoveLocation(_SelectedUnit, traceResult.Location);
	}
}

void APC_RTS::StartQueueing()
{
	_isQueueing = true;
}

void APC_RTS::StopQueueing()
{
	_isQueueing = false;
}
