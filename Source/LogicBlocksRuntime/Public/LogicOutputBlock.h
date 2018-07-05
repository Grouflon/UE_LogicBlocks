// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LogicOutputBlock.generated.h"

UCLASS(abstract)
class LOGICBLOCKSRUNTIME_API ALogicOutputBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	ALogicOutputBlock();

	UFUNCTION(BlueprintNativeEvent) void BeginValidity();
	UFUNCTION(BlueprintNativeEvent) void TickValidity(float DeltaTime);
	UFUNCTION(BlueprintNativeEvent) void EndValidity();

	UFUNCTION(BlueprintImplementableEvent, CallInEditor) void EditorTick(float _deltaSeconds);

protected:
	virtual void BeginValidity_Implementation();
	virtual void TickValidity_Implementation(float _deltaTime);
	virtual void EndValidity_Implementation();
};
