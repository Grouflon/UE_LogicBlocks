// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LogicOutputBlock.generated.h"

UCLASS(abstract)
class LOGICBLOCKS_API ALogicOutputBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	ALogicOutputBlock();

	UFUNCTION(BlueprintNativeEvent) void BeginValidity();
	UFUNCTION(BlueprintNativeEvent) void TickValidity(float DeltaTime);
	UFUNCTION(BlueprintNativeEvent) void EndValidity();

	UFUNCTION(BlueprintImplementableEvent) void EditorTick(float _deltaTime);

protected:
	virtual void BeginValidity_Implementation();
	virtual void TickValidity_Implementation(float _deltaTime);
	virtual void EndValidity_Implementation();
};
