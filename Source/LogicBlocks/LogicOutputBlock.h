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

	UFUNCTION(BlueprintNativeEvent) void ValidityBegin();
	UFUNCTION(BlueprintNativeEvent) void ValidityTick(float DeltaTime);
	UFUNCTION(BlueprintNativeEvent) void ValidityEnd();

protected:
	virtual void ValidityBegin_Implementation();
	virtual void ValidityTick_Implementation(float _deltaTime);
	virtual void ValidityEnd_Implementation();
};
