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
	virtual ~ULogicBlocksComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

	void CreateInput(TSubclassOf<ALogicInputBlock> _logicInputBlockClass);
	void CreateOutput(TSubclassOf<ALogicOutputBlock> _logicOutputBlockClass);

	void RemoveInput(ALogicInputBlock* _input);
	void RemoveOutput(ALogicOutputBlock* _output);
		
	const TArray<TWeakObjectPtr<ALogicInputBlock>>& GetInputBlocks() const;
	const TArray<TWeakObjectPtr<ALogicOutputBlock>>& GetOutputBlocks() const;

	// NOTE: Could move to details customization
	UPROPERTY(EditAnywhere) TSubclassOf<ALogicInputBlock> LogicInputBlockClass;
	UPROPERTY(EditAnywhere) TSubclassOf<ALogicOutputBlock> LogicOutputBlockClass;

private:
	void _EditorTick(float _deltaTime);

	UPROPERTY() TArray<TWeakObjectPtr<ALogicInputBlock>> m_logicInputs;
	UPROPERTY() TArray<TWeakObjectPtr<ALogicOutputBlock>> m_logicOutputs;

	bool m_previousValidity = false;
};
