#include "PooledObject.h"

#include "ObjectPool.h"

void UPooledObject::Init(AObjectPool* owner)
{
	_IsActive = false;
	_ObjectPool = owner;
	
}

void UPooledObject::RecycleSelf()
{
	_ObjectPool->RecyclePooledObject(this);
}

void UPooledObject::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	_ObjectPool->OnPoolerCleanup.RemoveDynamic(this, &UPooledObject::RecycleSelf);
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}