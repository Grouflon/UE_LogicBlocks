// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class ALogicInputBlock;
class ALogicOutputBlock;
class ULogicGraph;
class ULogicGraphNode;
class ULogicNode;
class ULogicExpressionNode;
class ULogicOutputNode;

#include <CoreMinimal.h>
#include <Components/ActorComponent.h>

#include "LogicBlocksComponent.generated.h"


UCLASS(abstract, hidecategories = Object)
class ULogicNode : public UObject
{
	GENERATED_BODY()

public:
	ULogicGraphNode* GetGraphNode() const;
	void SetupGraphNode(UEdGraph* _graph);

	virtual void BeginDestroy() override;

protected:
	virtual ULogicGraphNode* _CreateGraphNode(UEdGraph* _graph) { return nullptr; }

private:
	UPROPERTY() ULogicGraphNode* m_graphNode = nullptr;
};


UCLASS(abstract, hidecategories = Object)
class ULogicExpressionNode : public ULogicNode
{
	GENERATED_BODY()

public:
	virtual bool Evaluate() const { return true; };
};


UCLASS(hidecategories = Object, editinlinenew, MinimalAPI)
class ULogicInputNode : public ULogicExpressionNode
{
	GENERATED_BODY()

public:
	virtual bool Evaluate() const override;

	UPROPERTY() ALogicInputBlock* Input = nullptr;

protected:
	virtual ULogicGraphNode* _CreateGraphNode(UEdGraph* _graph) override;

};


UCLASS(hidecategories = Object, editinlinenew, MinimalAPI)
class ULogicANDNode : public ULogicExpressionNode
{
	GENERATED_BODY()

public:
	virtual bool Evaluate() const override;

	UPROPERTY() TArray<ULogicExpressionNode*> Operands;

protected:
	virtual ULogicGraphNode* _CreateGraphNode(UEdGraph* _graph) override;
};


UCLASS(hidecategories = Object, editinlinenew, MinimalAPI)
class ULogicORNode : public ULogicExpressionNode
{
	GENERATED_BODY()

public:
	virtual bool Evaluate() const override;

	UPROPERTY() TArray<ULogicExpressionNode*> Operands;

protected:
	virtual ULogicGraphNode* _CreateGraphNode(UEdGraph* _graph) override;
};


UCLASS(hidecategories = Object, editinlinenew, MinimalAPI)
class ULogicNOTNode : public ULogicExpressionNode
{
	GENERATED_BODY()

public:
	virtual bool Evaluate() const override
	{
		return !Expression->Evaluate();
	}

	UPROPERTY() ULogicExpressionNode* Expression;

protected:
	virtual ULogicGraphNode* _CreateGraphNode(UEdGraph* _graph) override;
};


UCLASS(hidecategories = Object, editinlinenew, MinimalAPI)
class ULogicOutputNode : public ULogicNode
{
	GENERATED_BODY()

public:
	void Tick(float _dt);

	UPROPERTY() ULogicExpressionNode* Input;
	UPROPERTY() ALogicOutputBlock* Output;

protected:
	virtual ULogicGraphNode* _CreateGraphNode(UEdGraph* _graph) override;

private:
	bool m_previousEvaluation = false;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOGICBLOCKS_API ULogicBlocksComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULogicBlocksComponent();
	virtual ~ULogicBlocksComponent();

	virtual void BeginPlay() override;
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

	// When not in Advanced Mode, All Inputs will be combined with an AND operation, and the result of this will trigger all Outputs
	UPROPERTY(EditAnywhere, DisplayName = "Advanced Mode") bool IsAdvancedModeEnabled = false;

	ULogicGraph* GetLogicGraph() const;

	template<class T>
	T* ConstructLogicNode(TSubclassOf<ULogicNode> _logicNodeClass = T::StaticClass())
	{
		// Set flag to be transactional so it registers with undo system
		T* logicNode = NewObject<T>(this, _logicNodeClass, NAME_None, RF_Transactional);
		m_logicNodes.Add(logicNode);

		ULogicOutputNode* logicOutputNode = Cast<ULogicOutputNode>(logicNode);
		if (logicOutputNode)
		{
			m_logicOutputNodes.Add(logicOutputNode);
		}

		return logicNode;
	}

	void DestroyLogicNode(ULogicNode* _node);

private:
	void _EditorTick(float _deltaTime);

	UPROPERTY() TArray<TWeakObjectPtr<ALogicInputBlock>> m_logicInputs;
	UPROPERTY() TArray<TWeakObjectPtr<ALogicOutputBlock>> m_logicOutputs;

	bool m_previousValidity = false;

	UPROPERTY() ULogicGraph* m_logicGraph = nullptr;

	UPROPERTY() TArray<ULogicNode*> m_logicNodes;
	UPROPERTY() TArray<ULogicOutputNode*> m_logicOutputNodes;
};
