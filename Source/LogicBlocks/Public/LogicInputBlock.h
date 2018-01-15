// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LogicInputBlock.generated.h"

UCLASS(abstract)
class LOGICBLOCKS_API ALogicInputBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	ALogicInputBlock();

	UFUNCTION(BlueprintNativeEvent) bool Evaluate();
	UFUNCTION(BlueprintImplementableEvent) void EditorTick(float _deltaTime);


protected:
	virtual bool Evaluate_Implementation();
};
