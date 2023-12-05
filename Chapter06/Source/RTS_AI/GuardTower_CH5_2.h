// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "GuardTower_CH5_2.generated.h"

class UArrowComponent;
class USpotLightComponent;
UCLASS()
class RTS_AI_API AGuardTower_CH5_2 : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> _TowerMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> _LightPivot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> _LightMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TObjectPtr<USpotLightComponent> _SpotLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TObjectPtr<UArrowComponent> _Arrow;

	FOnTimelineFloat onTimeline_Update;
	FOnTimelineEventStatic onTimeline_Finished;
	UFUNCTION()
	void Handle_RotateLight_Update(float val);
	UFUNCTION()
	void Handle_RotateLight_Finished();
	void StartRotation();
	void StopRotation();

public:	
	
	AGuardTower_CH5_2();
	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _RotateForward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _EnemySpotted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _DetectionRange;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _DetectionRadius;

	UPROPERTY()
	TObjectPtr<UTimelineComponent> T_RotateLight;

	UPROPERTY(EditAnywhere)
	UCurveFloat* _Curve;
	
	virtual void BeginPlay() override;

};