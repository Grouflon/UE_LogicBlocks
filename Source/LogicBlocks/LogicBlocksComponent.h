// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class ALogicInputBlock;
class ALogicOutputBlock;

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Input/Reply.h>
#include "LogicBlocksComponent.generated.h"

class LogicOperation
{
public:
	virtual bool Evaluate() const = 0;
};

class LogicOperationInput : public LogicOperation
{
public:
	virtual bool Evaluate() const
	{
		return false;
	}
};

class LogicOperationAnd : public LogicOperation
{
public:
	virtual bool Evaluate() const override
	{
		return false;
	}

private:
	TArray<LogicOperation*> m_operands;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOGICBLOCKS_API ULogicBlocksComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULogicBlocksComponent();
	~ULogicBlocksComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

	void CreateInput(TSubclassOf<ALogicInputBlock> _logicInputBlockClass);
	void CreateOutput(TSubclassOf<ALogicOutputBlock> _logicOutputBlockClass);
		
	const TArray<ALogicInputBlock*>& GetInputBlocks() const;
	const TArray<ALogicOutputBlock*>& GetOutputBlocks() const;

	UPROPERTY(EditAnywhere) TSubclassOf<ALogicInputBlock> LogicInputBlockClass;
	UPROPERTY(EditAnywhere) TSubclassOf<ALogicOutputBlock> LogicOutputBlockClass;

private:
	UFUNCTION() void _OnInputBlockDestroyed(AActor* _destroyedActor);
	UFUNCTION() void _OnOutputBlockDestroyed(AActor* _destroyedActor);

	UPROPERTY() TArray<ALogicInputBlock*> m_logicInputs;
	UPROPERTY() TArray<ALogicOutputBlock*> m_logicOutputs;
	
};
