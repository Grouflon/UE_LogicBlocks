// Fill out your copyright notice in the Description page of Project Settings.

#include "LogicGraph.h"

#include <EdGraphSchema_K2.h>

#include <LogicBlocksComponent.h>
#include <LogicInputBlock.h>
#include <LogicOutputBlock.h>

void ULogicGraphNode::SetLogicNode(ULogicNode* _node)
{
	m_logicNode = _node;
}

ULogicNode* ULogicGraphNode::GetLogicNode() const
{
	return m_logicNode;
}


void ULogicInputGraphNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, ULogicGraph::s_ExpressionPinType, FString());
}

FText ULogicInputGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	ULogicInputNode* logicInput = Cast<ULogicInputNode>(GetLogicNode());
	check(logicInput);

	FString title = TEXT("Input: ");
	check(logicInput->Input);
	
	title += logicInput->Input->GetActorLabel();

	return FText::FromString(title);
}

void ULogicNOTGraphNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, ULogicGraph::s_ExpressionPinType, FString());
	CreatePin(EGPD_Output, ULogicGraph::s_ExpressionPinType, FString());
}

FText ULogicNOTGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(TEXT("NOT"));
}

void ULogicNOTGraphNode::PinConnectionListChanged(UEdGraphPin* _pin)
{
	if (_pin->Direction.GetValue() == EEdGraphPinDirection::EGPD_Output)
		return;

	ULogicNOTNode* logicNOT = Cast<ULogicNOTNode>(GetLogicNode());
	check(logicNOT);

	logicNOT->Expression = nullptr;

	if (_pin->LinkedTo.Num() > 0)
	{
		check(_pin->LinkedTo.Num() == 1);

		ULogicGraphNode* linkedNode = Cast<ULogicGraphNode>(_pin->LinkedTo[0]->GetOwningNode());
		check(linkedNode);

		ULogicExpressionNode* linkedExpression = Cast<ULogicExpressionNode>(linkedNode->GetLogicNode());
		check(linkedExpression);

		logicNOT->Expression = linkedExpression;
	}
}

FEdGraphPinType ULogicGraph::s_ExpressionPinType = FEdGraphPinType(TEXT("Expression"), FString(), nullptr, EPinContainerType::None, false, FEdGraphTerminalType());

ULogicBlocksComponent* ULogicGraph::GetLogicBlocksComponent() const
{
	return CastChecked<ULogicBlocksComponent>(GetOuter());
}

void ULogicOutputGraphNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, ULogicGraph::s_ExpressionPinType, FString());
}

FText ULogicOutputGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	ULogicOutputNode* logicOutput = Cast<ULogicOutputNode>(GetLogicNode());
	check(logicOutput);

	FString title = TEXT("Output: ");
	check(logicOutput->Output);

	title += logicOutput->Output->GetActorLabel();

	return FText::FromString(title);
}

void ULogicOutputGraphNode::PinConnectionListChanged(UEdGraphPin* _pin)
{
	if (_pin->Direction.GetValue() == EEdGraphPinDirection::EGPD_Output)
		return;

	ULogicOutputNode* logicOutput = Cast<ULogicOutputNode>(GetLogicNode());
	check(logicOutput);

	logicOutput->Input = nullptr;

	if (_pin->LinkedTo.Num() > 0)
	{
		check(_pin->LinkedTo.Num() == 1);

		ULogicGraphNode* linkedNode = Cast<ULogicGraphNode>(_pin->LinkedTo[0]->GetOwningNode());
		check(linkedNode);

		ULogicExpressionNode* linkedExpression = Cast<ULogicExpressionNode>(linkedNode->GetLogicNode());
		check(linkedExpression);

		logicOutput->Input = linkedExpression;
	}
}
