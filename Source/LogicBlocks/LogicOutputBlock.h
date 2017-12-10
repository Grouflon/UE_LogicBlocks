// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LogicOutputBlock.generated.h"

UCLASS()
class LOGICBLOCKS_API ALogicOutputBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	ALogicOutputBlock();

	UFUNCTION(BlueprintImplementableEvent) void ValidityStart();
	UFUNCTION(BlueprintImplementableEvent) void ValidityTick(float DeltaTime);
	UFUNCTION(BlueprintImplementableEvent) void ValidityStop();

	UPROPERTY(EditAnywhere) float m_param1 = 0.0f;
	UPROPERTY(EditAnywhere) float m_param2 = 0.0f;
};
