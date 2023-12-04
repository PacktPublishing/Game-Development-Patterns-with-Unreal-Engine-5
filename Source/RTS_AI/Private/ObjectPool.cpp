#include "ObjectPool.h"

#include "PooledObject.h"

void AObjectPool::Broadcast_PoolerCleanup()
{
	OnPoolerCleanup.Broadcast();
}

AActor* AObjectPool::GetPooledActor(FString name)
{
	int poolCount = _Pools.Num();
	int currentPool = -1;
	for(int i = 0; i < poolCount; i++)
	{
		if(_PooledObjectData[i]._ActorName == name)
		{
			currentPool = i;
			break;
		}
	}

	if(currentPool == -1) { return nullptr; }

	int pooledObjectCount = _Pools[currentPool]._PooledObjects.Num();
	int firstAvailable = -1;
	for(int i = 0; i < pooledObjectCount; i++)
	{
		if(_Pools[currentPool]._PooledObjects[i] != nullptr)
		{
			if(!_Pools[currentPool]._PooledObjects[i]->_IsActive)
			{
				firstAvailable = i;
				break;
			}
		}
		else
		{
			RegenItem(currentPool, i);
			firstAvailable = i;
			break;
		}
	}

	if(firstAvailable >= 0)
	{
		UPooledObject* toReturn = _Pools[currentPool]._PooledObjects[firstAvailable];
		toReturn->_IsActive = true;
		OnPoolerCleanup.AddUniqueDynamic(toReturn, &UPooledObject::RecycleSelf);
		AActor* toReturnActor = toReturn->GetOwner();
		toReturnActor->SetActorHiddenInGame(false);
		toReturnActor->SetActorEnableCollision(true);
		toReturnActor->SetActorTickEnabled(true);
		toReturnActor->AttachToActor(nullptr, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		return toReturnActor;
	}

	if(!_PooledObjectData[currentPool]._CanGrow) { return nullptr; }

	
	FActorSpawnParameters spawnParams;
	spawnParams.Name = FName(FString::Printf(TEXT("%s"), *_PooledObjectData[currentPool]._ActorName));
	spawnParams.NameMode = FActorSpawnParameters::ESpawnActorNameMode::Requested;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* spawnedActor = GetWorld()->SpawnActor(_PooledObjectData[currentPool]._ActorTemplate,
				&FVector::ZeroVector, &FRotator::ZeroRotator, spawnParams);
	spawnedActor->SetActorLabel(spawnedActor->GetName());
	UPooledObject* poolComp = NewObject<UPooledObject>(spawnedActor);
	poolComp->RegisterComponent();
	spawnedActor->AddInstanceComponent(poolComp);
	poolComp->Init(this);
	_Pools[currentPool]._PooledObjects.Add(poolComp);
	poolComp->_IsActive = true;
	OnPoolerCleanup.AddUniqueDynamic(poolComp, &UPooledObject::RecycleSelf);
	return spawnedActor;
}

void AObjectPool::RecyclePooledObject(UPooledObject* poolCompRef)
{
	OnPoolerCleanup.RemoveDynamic(poolCompRef, &UPooledObject::RecycleSelf);
	poolCompRef->_IsActive = false;
	AActor* returningActor = poolCompRef->GetOwner();
	returningActor->SetActorHiddenInGame(true);
	returningActor->SetActorEnableCollision(false);
	returningActor->SetActorTickEnabled(false);
	returningActor->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void AObjectPool::RecycleActor(AActor* pooledActor)
{
	if(UPooledObject* poolCompRef = Cast<UPooledObject>(pooledActor->GetComponentByClass(UPooledObject::StaticClass())))
	{
		RecyclePooledObject(poolCompRef);
	}
}

void AObjectPool::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters spawnParams;
	for(int poolIndex = 0; poolIndex < _PooledObjectData.Num(); poolIndex++)
	{
		FSingleObjectPool currentPool;
		spawnParams.Name = FName(FString::Printf(TEXT("%s"), *_PooledObjectData[poolIndex]._ActorName));
		spawnParams.NameMode = FActorSpawnParameters::ESpawnActorNameMode::Requested;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		for(int objectIndex = 0; objectIndex < _PooledObjectData[poolIndex]._PoolSize; objectIndex++)
		{
			
			AActor* spawnedActor = GetWorld()->SpawnActor(_PooledObjectData[poolIndex]._ActorTemplate,
				&FVector::ZeroVector, &FRotator::ZeroRotator, spawnParams);
			spawnedActor->SetActorLabel(spawnedActor->GetName());
			UPooledObject* poolComp = NewObject<UPooledObject>(spawnedActor);
			poolComp->RegisterComponent();
			spawnedActor->AddInstanceComponent(poolComp);
			poolComp->Init(this);
			currentPool._PooledObjects.Add(poolComp);
			spawnedActor->SetActorHiddenInGame(true);
			spawnedActor->SetActorEnableCollision(false);
			spawnedActor->SetActorTickEnabled(false);
			spawnedActor->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
		_Pools.Add(currentPool);
	}
}

void AObjectPool::RegenItem(int poolIndex, int positionIndex)
{
	FActorSpawnParameters spawnParams;
	spawnParams.Name = FName(FString::Printf(TEXT("%s"), *_PooledObjectData[poolIndex]._ActorName));
	spawnParams.NameMode = FActorSpawnParameters::ESpawnActorNameMode::Requested;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* spawnedActor = GetWorld()->SpawnActor(_PooledObjectData[poolIndex]._ActorTemplate,
				&FVector::ZeroVector, &FRotator::ZeroRotator, spawnParams);
	spawnedActor->SetActorLabel(spawnedActor->GetName());
	UPooledObject* poolComp = NewObject<UPooledObject>(spawnedActor);
	poolComp->RegisterComponent();
	spawnedActor->AddInstanceComponent(poolComp);
	poolComp->Init(this);
	_Pools[poolIndex]._PooledObjects.Insert(poolComp, positionIndex);
	spawnedActor->SetActorHiddenInGame(true);
	spawnedActor->SetActorEnableCollision(false);
	spawnedActor->SetActorTickEnabled(false);
	spawnedActor->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}
