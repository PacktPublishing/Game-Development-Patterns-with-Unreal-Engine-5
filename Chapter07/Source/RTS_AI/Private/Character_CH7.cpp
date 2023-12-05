#include "Character_CH7.h"

#include "AIUnit_CH7.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

ACharacter_CH7::ACharacter_CH7()
{
	
}

void ACharacter_CH7::Init()
{
}

void ACharacter_CH7::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ACharacter_CH7::Fire);
}

void ACharacter_CH7::Fire()
{
	TArray<AActor*> outActors;
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(), 10000.f, {UEngineTypes::ConvertToObjectType(ECC_Pawn)}, AAIUnit_CH7::StaticClass(), {this}, outActors);
	if(outActors.Num() == 0) {return;}

	FHitResult hit(ForceInit);
	if(UKismetSystemLibrary::LineTraceSingle(GetWorld(), GetActorLocation(), outActors[0]->GetActorLocation(), UEngineTypes::ConvertToTraceType(ECC_Visibility), true, {this}, EDrawDebugTrace::ForDuration, hit, true))
	{
		UGameplayStatics::ApplyDamage(outActors[0], 100.f, Controller, this, UDamageType::StaticClass());
	}
}

