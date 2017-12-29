// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class ALogicInputBlock;
class ALogicOutputBlock;
class ULogicGraph;

class ULogicNode;
class ULogicExpressionNode;
class ULogicOutputNode;

#include <CoreMinimal.h>
#include <Components/ActorComponent.h>
#include <BlueprintEditorUtils.h>

#include <LogicInputBlock.h>
#include <LogicOutputBlock.h>
#include <LogicGraph.h>

#include "LogicBlocksComponent.generated.h"

UCLASS(abstract, hidecategories = Object)
class ULogicNode : public UObject
{
	GENERATED_BODY()

public:
	ULogicGraphNode* GetGraphNode() const { return m_graphNode; }

	void SetupGraphNode(UEdGraph* _graph)
	{
		m_graphNode = _CreateGraphNode(_graph);
		check(m_graphNode);
		m_graphNode->SetLogicNode(this);
	}

	virtual void BeginDestroy() override
	{
		if (m_graphNode)
		{
			FBlueprintEditorUtils::RemoveNode(NULL, m_graphNode, true);
			m_graphNode = nullptr;
		}

		Super::BeginDestroy();
	}

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
	virtual bool Evaluate() const override
	{
		return Input ? Input->Evaluate() : false;
	}

	ALogicInputBlock* Input = nullptr;

protected:
	virtual ULogicGraphNode* _CreateGraphNode(UEdGraph* _graph) override
	{
		FGraphNodeCreator<ULogicInputGraphNode> nodeCreator(*_graph);
		ULogicInputGraphNode* graphNode = nodeCreator.CreateNode();
		nodeCreator.Finalize();
		return graphNode;
	}

};

UCLASS(hidecategories = Object, editinlinenew, MinimalAPI)
class ULogicANDNode : public ULogicExpressionNode
{
	GENERATED_BODY()

public:
	virtual bool Evaluate() const override
	{
		bool result = Operands.Num() > 0 ? true : false;
		for (auto operand : Operands)
		{
			result = result && operand->Evaluate();

			if (result == false)
				break;
		}
		return result;
	}

	TArray<ULogicExpressionNode*> Operands;
};

UCLASS(hidecategories = Object, editinlinenew, MinimalAPI)
class ULogicORNode : public ULogicExpressionNode
{
	GENERATED_BODY()

public:
	virtual bool Evaluate() const override
	{
		bool result = false;
		for (auto operand : Operands)
		{
			result = result || operand->Evaluate();

			if (result == true)
				break;
		}
		return result;
	}

	TArray<ULogicExpressionNode*> Operands;
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

	ULogicExpressionNode* Expression;

protected:
	virtual ULogicGraphNode* _CreateGraphNode(UEdGraph* _graph) override
	{
		FGraphNodeCreator<ULogicNOTGraphNode> nodeCreator(*_graph);
		ULogicNOTGraphNode* graphNode = nodeCreator.CreateNode();
		nodeCreator.Finalize();
		return graphNode;
	}
};

UCLASS(hidecategories = Object, editinlinenew, MinimalAPI)
class ULogicOutputNode : public ULogicNode
{
	GENERATED_BODY()

public:

	void Tick(float _dt)
	{
		check(Output);

		bool evaluation = Input ? Input->Evaluate() : false;

		if (!m_previousEvaluation && evaluation)
		{
			Output->BeginValidity();
		}

		if (evaluation)
		{
			Output->TickValidity(_dt);
		}

		if (!evaluation && m_previousEvaluation)
		{
			Output->EndValidity();
		}

		m_previousEvaluation = evaluation;
	}

	ULogicExpressionNode* Input;
	ALogicOutputBlock* Output;

protected:
	virtual ULogicGraphNode* _CreateGraphNode(UEdGraph* _graph) override
	{
		FGraphNodeCreator<ULogicOutputGraphNode> nodeCreator(*_graph);
		ULogicOutputGraphNode* graphNode = nodeCreator.CreateNode();
		nodeCreator.Finalize();
		return graphNode;
	}

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

	ULogicGraph* GetLogicGraph() const;

	template<class T>
	T* ConstructLogicNode(TSubclassOf<ULogicNode> LogicNodeClass = T::StaticClass())
	{
		// Set flag to be transactional so it registers with undo system
		T* LogicNode = NewObject<T>(this, LogicNodeClass, NAME_None, RF_Transactional);
		m_logicNodes.Add(LogicNode);
		return LogicNode;
	}

	void DestroyLogicNode(ULogicNode* _node);

private:
	void _EditorTick(float _deltaTime);

	UPROPERTY() TArray<TWeakObjectPtr<ALogicInputBlock>> m_logicInputs;
	UPROPERTY() TArray<TWeakObjectPtr<ALogicOutputBlock>> m_logicOutputs;

	bool m_previousValidity = false;

	UPROPERTY() ULogicGraph* m_logicGraph = nullptr;

	TArray<ULogicNode*> m_logicNodes;
};
