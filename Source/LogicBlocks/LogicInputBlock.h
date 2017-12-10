// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LogicInputBlock.generated.h"

UCLASS()
class LOGICBLOCKS_API ALogicInputBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	ALogicInputBlock();

	UFUNCTION(BlueprintImplementableEvent) bool CheckInput();

	UPROPERTY(EditAnywhere, Category = "Logic") float m_param1 = 0.0f;
	UPROPERTY(EditAnywhere, Category = "Logic") float m_param2 = 0.0f;
	
};
