// Fill out your copyright notice in the Description page of Project Settings.

#include "LogicBlocksComponent.h"

#include <Engine/World.h>
#include <BlueprintEditorUtils.h>

#include <LogicInputBlock.h>
#include <LogicOutputBlock.h>
#include <LogicGraph.h>
#include <LogicGraphSchema.h>

// Sets default values for this component's properties
ULogicBlocksComponent::ULogicBlocksComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bTickInEditor = true;

	m_logicGraph = CreateDefaultSubobject<ULogicGraph>(TEXT("LogicGraph"));
	m_logicGraph->Schema = ULogicGraphSchema::StaticClass();
}


ULogicBlocksComponent::~ULogicBlocksComponent()
{
	
}

// Called when the game starts
void ULogicBlocksComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void ULogicBlocksComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

#if WITH_EDITOR
	if (GetWorld()->WorldType == EWorldType::Editor)
	{
		_EditorTick(DeltaTime);
	}
	else
	{
#endif

	if (!IsAdvancedModeEnabled)
	{
		bool validity = true;
		for (auto input : m_logicInputs)
		{
			validity = validity && input->Evaluate();
			if (!validity)
				break;
		}

		if (validity && !m_previousValidity)
		{
			for (auto output : m_logicOutputs)
			{
				output->BeginValidity();
			}
		}

		if (validity)
		{
			for (auto output : m_logicOutputs)
			{
				output->TickValidity(DeltaTime);
			}
		}

		if (!validity && m_previousValidity)
		{
			for (auto output : m_logicOutputs)
			{
				output->EndValidity();
			}
		}

		m_previousValidity = validity;
	}
	else
	{
		for (ULogicOutputNode* outputNode : m_logicOutputNodes)
		{
			outputNode->Tick(DeltaTime);
		}
	}
	

#if WITH_EDITOR
	}
#endif
}

void ULogicBlocksComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	/*for (int32 i = m_logicNodes.Num() - 1; i >= 0; --i)
	{
		DestroyLogicNode(m_logicNodes[i]);
	}
	check(m_logicNodes.Num() == 0);
	check(m_logicOutputNodes.Num() == 0);

	for (int32 i = m_logicInputs.Num() - 1; i >= 0; --i)
	{
		RemoveInput(m_logicInputs[i].Get());
	}
	check(m_logicInputs.Num() == 0);

	for (int32 i = m_logicOutputs.Num() - 1; i >= 0; --i)
	{
		RemoveOutput(m_logicOutputs[i].Get());
	}
	check(m_logicOutputs.Num() == 0);*/
}


void ULogicBlocksComponent::CreateInput(TSubclassOf<ALogicInputBlock> _logicInputBlockClass)
{
	if (_logicInputBlockClass == nullptr)
		return;

	FActorSpawnParameters spawnParameters;
	spawnParameters.Owner = GetOwner();
	ALogicInputBlock* inputBlock = GetWorld()->SpawnActor<ALogicInputBlock>(_logicInputBlockClass, GetOwner()->GetTransform(), spawnParameters);
	inputBlock->AttachToActor(GetOwner(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	m_logicInputs.Add(inputBlock);

	PrimaryComponentTick.AddPrerequisite(inputBlock, inputBlock->PrimaryActorTick);
}

void ULogicBlocksComponent::CreateOutput(TSubclassOf<ALogicOutputBlock> _logicOutputBlockClass)
{
	if (_logicOutputBlockClass == nullptr)
		return;

	FActorSpawnParameters spawnParameters;
	spawnParameters.Owner = GetOwner();
	ALogicOutputBlock* outputBlock = GetWorld()->SpawnActor<ALogicOutputBlock>(_logicOutputBlockClass, GetOwner()->GetTransform(), spawnParameters);
	outputBlock->AttachToActor(GetOwner(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	m_logicOutputs.Add(outputBlock);

	outputBlock->PrimaryActorTick.AddPrerequisite(this, PrimaryComponentTick);
}

void ULogicBlocksComponent::RemoveInput(ALogicInputBlock* _input)
{
	check(m_logicInputs.Find(_input) != INDEX_NONE);

	// REMOVE PREREQUISITES
	PrimaryComponentTick.RemovePrerequisite(_input, _input->PrimaryActorTick);

	// DESTROY MATCHING NODES
	for (int32 i = m_logicNodes.Num() - 1; i >= 0; --i)
	{
		ULogicInputNode* inputNode = Cast<ULogicInputNode>(m_logicNodes[i]);
		if (!inputNode)
			continue;

		if (inputNode->Input == _input)
		{
			DestroyLogicNode(inputNode);
		}
	}

	// REMOVE FROM INPUT LIST
	int32 ret = m_logicInputs.Remove(_input);
	check(ret == 1);

	// DESTROY
	_input->Destroy();
}

void ULogicBlocksComponent::RemoveOutput(ALogicOutputBlock* _output)
{
	check(m_logicOutputs.Find(_output) != INDEX_NONE);

	// REMOVE PREREQUISITES
	_output->PrimaryActorTick.RemovePrerequisite(this, PrimaryComponentTick);

	// DESTROY MATCHING NODES
	for (int32 i = m_logicNodes.Num() - 1; i >= 0; --i)
	{
		ULogicOutputNode* outputNode = Cast<ULogicOutputNode>(m_logicNodes[i]);
		if (!outputNode)
			continue;

		if (outputNode->Output == _output)
		{
			DestroyLogicNode(outputNode);
		}
	}

	// REMOVE FROM INPUT LIST
	int32 ret = m_logicOutputs.Remove(_output);
	check(ret == 1);

	// DESTROY
	_output->Destroy();
}

const TArray < TWeakObjectPtr<ALogicInputBlock>>& ULogicBlocksComponent::GetInputBlocks() const
{
	return m_logicInputs;
}

const TArray<TWeakObjectPtr<ALogicOutputBlock>>& ULogicBlocksComponent::GetOutputBlocks() const
{
	return m_logicOutputs;
}

ULogicGraph* ULogicBlocksComponent::GetLogicGraph() const
{
	return m_logicGraph;
}

void ULogicBlocksComponent::DestroyLogicNode(ULogicNode* _node)
{
	check(_node->IsValidLowLevel());
	check(m_logicNodes.Find(_node) != INDEX_NONE);

	m_logicNodes.Remove(_node);

	ULogicOutputNode* logicOutputNode = Cast<ULogicOutputNode>(_node);
	if (logicOutputNode)
	{
		m_logicOutputNodes.Remove(logicOutputNode);
	}

	// TODO: Remove all references from other nodes.

	_node->ConditionalBeginDestroy();
}

void ULogicBlocksComponent::_EditorTick(float _deltaTime)
{
	// GARBAGE COLLECTION
	for (int32 i = m_logicInputs.Num() - 1; i >= 0; --i)
	{
		if (m_logicInputs[i].Get() == nullptr)
		{
			m_logicInputs.RemoveAt(i);
		}
	}

	for (int32 i = m_logicOutputs.Num() - 1; i >= 0; --i)
	{
		if (m_logicOutputs[i].Get() == nullptr)
		{
			m_logicOutputs.RemoveAt(i);
		}
	}
}

ULogicGraphNode* ULogicNode::GetGraphNode() const
{
	return m_graphNode;
}

void ULogicNode::SetupGraphNode(UEdGraph* _graph)
{
	check(!m_graphNode);

	m_graphNode = _CreateGraphNode(_graph);
	check(m_graphNode);
	m_graphNode->SetLogicNode(this);
}

void ULogicNode::BeginDestroy()
{
	if (m_graphNode)
	{
		FBlueprintEditorUtils::RemoveNode(NULL, m_graphNode, true);
		m_graphNode = nullptr;
	}

	Super::BeginDestroy();
}

bool ULogicInputNode::Evaluate() const
{
	return Input ? Input->Evaluate() : false;
}

ULogicGraphNode* ULogicInputNode::_CreateGraphNode(UEdGraph* _graph)
{
	FGraphNodeCreator<ULogicInputGraphNode> nodeCreator(*_graph);
	ULogicInputGraphNode* graphNode = nodeCreator.CreateNode();
	nodeCreator.Finalize();
	return graphNode;
}

bool ULogicANDNode::Evaluate() const
{
	bool result = true;
	bool hasOperands = false;
	for (auto operand : Operands)
	{
		if (operand == nullptr)
			continue;

		hasOperands = true;
		result = result && operand->Evaluate();

		if (result == false)
			break;
	}
	return hasOperands ? result : true;
}

ULogicGraphNode* ULogicANDNode::_CreateGraphNode(UEdGraph* _graph)
{
	FGraphNodeCreator<ULogicANDGraphNode> nodeCreator(*_graph);
	ULogicANDGraphNode* graphNode = nodeCreator.CreateNode();
	nodeCreator.Finalize();
	return graphNode;
}

bool ULogicORNode::Evaluate() const
{
	bool result = false;
	bool hasOperands = false;
	for (auto operand : Operands)
	{
		if (operand == nullptr)
			continue;

		hasOperands = true;
		result = result || operand->Evaluate();

		if (result == true)
			break;
	}
	return hasOperands ? result : true;
}

ULogicGraphNode* ULogicORNode::_CreateGraphNode(UEdGraph* _graph)
{
	FGraphNodeCreator<ULogicORGraphNode> nodeCreator(*_graph);
	ULogicORGraphNode* graphNode = nodeCreator.CreateNode();
	nodeCreator.Finalize();
	return graphNode;
}

void ULogicOutputNode::Tick(float _dt)
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

ULogicGraphNode* ULogicOutputNode::_CreateGraphNode(UEdGraph* _graph)
{
	FGraphNodeCreator<ULogicOutputGraphNode> nodeCreator(*_graph);
	ULogicOutputGraphNode* graphNode = nodeCreator.CreateNode();
	nodeCreator.Finalize();
	return graphNode;
}

ULogicGraphNode* ULogicNOTNode::_CreateGraphNode(UEdGraph* _graph)
{
	FGraphNodeCreator<ULogicNOTGraphNode> nodeCreator(*_graph);
	ULogicNOTGraphNode* graphNode = nodeCreator.CreateNode();
	nodeCreator.Finalize();
	return graphNode;
}
