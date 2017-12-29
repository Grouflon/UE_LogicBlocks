// Fill out your copyright notice in the Description page of Project Settings.

#include "LogicGraphSchema.h"

#include <UObject/UObjectIterator.h>
#include <ScopedTransaction.h>

#include <LogicGraph.h>
#include <LogicBlocksComponent.h>

#define LOCTEXT_NAMESPACE "LogicBlocks"


UEdGraphNode* FLogicGraphSchemaAction_NewNode::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode /*= true*/)
{
	check(LogicNodeClass);

	ULogicBlocksComponent* logicBlocksComponent = CastChecked<ULogicGraph>(ParentGraph)->GetLogicBlocksComponent();
	const FScopedTransaction Transaction(LOCTEXT("NewLogicNode", "Logic Blocks: New Node"));
	ParentGraph->Modify();

	ULogicNode* NewNode = logicBlocksComponent->ConstructLogicNode<ULogicNode>(LogicNodeClass/*, bSelectNewNode*/);
	NewNode->SetupGraphNode(ParentGraph);

	// If this node allows >0 children but by default has zero - create a connector for starters
	/*if (NewNode->GetMaxChildNodes() > 0 && NewNode->ChildNodes.Num() == 0)
	{
		NewNode->CreateStartingConnectors();
	}*/

	// Attempt to connect inputs to selected nodes, unless we're already dragging from a single output
	/*if (FromPin == NULL || FromPin->Direction == EGPD_Input)
	{
		ConnectToSelectedNodes(NewNode, ParentGraph);
	}*/

	NewNode->GetGraphNode()->NodePosX = Location.X;
	NewNode->GetGraphNode()->NodePosY = Location.Y;

	NewNode->GetGraphNode()->AutowireNewNode(FromPin);

	/*SoundCue->PostEditChange();
	SoundCue->MarkPackageDirty();*/

	return NewNode->GetGraphNode();
}

UEdGraphNode* FLogicGraphSchemaAction_NewInputNode::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode /*= true*/)
{
	ULogicBlocksComponent* logicBlocksComponent = CastChecked<ULogicGraph>(ParentGraph)->GetLogicBlocksComponent();
	const FScopedTransaction Transaction(LOCTEXT("NewLogicInputNode", "Logic Blocks: New Input Node"));
	ParentGraph->Modify();

	ULogicInputNode* NewNode = logicBlocksComponent->ConstructLogicNode<ULogicInputNode>(ULogicInputNode::StaticClass()/*, bSelectNewNode*/);
	NewNode->SetupGraphNode(ParentGraph);

	NewNode->GetGraphNode()->NodePosX = Location.X;
	NewNode->GetGraphNode()->NodePosY = Location.Y;

	NewNode->GetGraphNode()->AutowireNewNode(FromPin);

	NewNode->Input = Input;

	return NewNode->GetGraphNode();
}

UEdGraphNode* FLogicGraphSchemaAction_NewOutputNode::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode /*= true*/)
{
	ULogicBlocksComponent* logicBlocksComponent = CastChecked<ULogicGraph>(ParentGraph)->GetLogicBlocksComponent();
	const FScopedTransaction Transaction(LOCTEXT("NewLogicOutputNode", "Logic Blocks: New Output Node"));
	ParentGraph->Modify();

	ULogicOutputNode* NewNode = logicBlocksComponent->ConstructLogicNode<ULogicOutputNode>(ULogicOutputNode::StaticClass()/*, bSelectNewNode*/);
	NewNode->SetupGraphNode(ParentGraph);

	NewNode->GetGraphNode()->NodePosX = Location.X;
	NewNode->GetGraphNode()->NodePosY = Location.Y;

	NewNode->GetGraphNode()->AutowireNewNode(FromPin);

	NewNode->Output = Output;

	return NewNode->GetGraphNode();
}

TArray<UClass*> ULogicGraphSchema::s_nodeClasses;
bool ULogicGraphSchema::s_isNodeClassesInitialized = false;
FLinearColor ULogicGraphSchema::s_expressionTypeColor = FLinearColor(0.065f, 0.519f, 1.0f);

void ULogicGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	_InitNodeClasses();

	_GetAllNodeActions(ContextMenuBuilder);

	const ULogicGraph* logicGraph = Cast<ULogicGraph>(ContextMenuBuilder.CurrentGraph);
	check(logicGraph);

	ULogicBlocksComponent* logicBlocksComponent = logicGraph->GetLogicBlocksComponent();
	check(logicBlocksComponent);

	for (auto input : logicBlocksComponent->GetInputBlocks())
	{
		check(input.Get());

		const FText Name = FText::FromString(input->GetActorLabel());
		FFormatNamedArguments Arguments;
		Arguments.Add(TEXT("Name"), Name);
		const FText AddToolTip = FText::Format(LOCTEXT("NewInputNodeTooltip", "Adds {Name} Input node here"), Arguments);
		TSharedPtr<FLogicGraphSchemaAction_NewInputNode> NewNodeAction(new FLogicGraphSchemaAction_NewInputNode(LOCTEXT("InputNodeAction", "Logic Input Node"), Name, AddToolTip, 0));
		NewNodeAction->Input = input.Get();
		ContextMenuBuilder.AddAction(NewNodeAction);
	}

	for (auto output : logicBlocksComponent->GetOutputBlocks())
	{
		check(output.Get());

		const FText Name = FText::FromString(output->GetActorLabel());
		FFormatNamedArguments Arguments;
		Arguments.Add(TEXT("Name"), Name);
		const FText AddToolTip = FText::Format(LOCTEXT("NewOutputNodeTooltip", "Adds {Name} Output node here"), Arguments);
		TSharedPtr<FLogicGraphSchemaAction_NewOutputNode> NewNodeAction(new FLogicGraphSchemaAction_NewOutputNode(LOCTEXT("OutputNodeAction", "Logic Output Node"), Name, AddToolTip, 0));
		NewNodeAction->Output = output.Get();
		ContextMenuBuilder.AddAction(NewNodeAction);
	}
}

const FPinConnectionResponse ULogicGraphSchema::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	// Make sure the pins are not on the same node
	if (A->GetOwningNode() == B->GetOwningNode())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("ConnectionSameNode", "Both are on the same node"));
	}

	// Compare the directions
	const UEdGraphPin* InputPin = NULL;
	const UEdGraphPin* OutputPin = NULL;

	if (!CategorizePinsByDirection(A, B, /*out*/ InputPin, /*out*/ OutputPin))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("ConnectionIncompatible", "Directions are not compatible"));
	}

	/*if (ConnectionCausesLoop(InputPin, OutputPin))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("ConnectionLoop", "Connection would cause loop"));
	}*/

	// Break existing connections on inputs only - multiple output connections are acceptable
	if (InputPin->LinkedTo.Num() > 0)
	{
		ECanCreateConnectionResponse ReplyBreakOutputs;
		if (InputPin == A)
		{
			ReplyBreakOutputs = CONNECT_RESPONSE_BREAK_OTHERS_A;
		}
		else
		{
			ReplyBreakOutputs = CONNECT_RESPONSE_BREAK_OTHERS_B;
		}
		return FPinConnectionResponse(ReplyBreakOutputs, LOCTEXT("ConnectionReplace", "Replace existing connections"));
	}

	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, TEXT(""));
}

bool ULogicGraphSchema::TryCreateConnection(UEdGraphPin* A, UEdGraphPin* B) const
{
	bool isModified = UEdGraphSchema::TryCreateConnection(A, B);
	return isModified;
}

FLinearColor ULogicGraphSchema::GetPinTypeColor(const FEdGraphPinType& PinType) const
{
	if (PinType == ULogicGraph::s_ExpressionPinType)
	{
		return s_expressionTypeColor;
	}

	return FLinearColor::White;
}

void ULogicGraphSchema::_GetAllNodeActions(FGraphActionMenuBuilder& ActionMenuBuilder/*, bool bShowSelectedActions*/) const
{
	FText SelectedItemText;
	bool IsSoundWaveSelected = false;
	bool IsDialogueWaveSelected = false;

	/*if (bShowSelectedActions)
	{
		FEditorDelegates::LoadSelectedAssetsIfNeeded.Broadcast();

		// Get display text for any items that may be selected
		if (ActionMenuBuilder.FromPin == NULL)
		{
			TArray<USoundWave*> SelectedWavs;
			TArray<UDialogueWave*> SelectedDialogues;
			GEditor->GetSelectedObjects()->GetSelectedObjects<USoundWave>(SelectedWavs);
			GEditor->GetSelectedObjects()->GetSelectedObjects<UDialogueWave>(SelectedDialogues);

			int32 TotalWavs = SelectedWavs.Num() + SelectedDialogues.Num();

			if (TotalWavs > 1)
			{
				SelectedItemText = LOCTEXT("MultipleWAVsSelected", "Multiple WAVs");
			}
			else if (SelectedWavs.Num() == 1)
			{
				SelectedItemText = FText::FromString(SelectedWavs[0]->GetName());
				IsSoundWaveSelected = true;
			}
			else if (SelectedDialogues.Num() == 1)
			{
				SelectedItemText = FText::FromString(SelectedDialogues[0]->GetName());
				IsDialogueWaveSelected = true;
			}
		}
		else
		{
			USoundWave* SelectedWave = GEditor->GetSelectedObjects()->GetTop<USoundWave>();
			if (SelectedWave && ActionMenuBuilder.FromPin->Direction == EGPD_Input)
			{
				SelectedItemText = FText::FromString(SelectedWave->GetName());
				IsSoundWaveSelected = true;
			}
			else
			{
				UDialogueWave* SelectedDialogue = GEditor->GetSelectedObjects()->GetTop<UDialogueWave>();
				if (SelectedDialogue && ActionMenuBuilder.FromPin->Direction == EGPD_Input)
				{
					SelectedItemText = FText::FromString(SelectedDialogue->GetName());
					IsDialogueWaveSelected = true;
				}
			}
		}

		bShowSelectedActions = !SelectedItemText.IsEmpty();
	}*/

	for (UClass* nodeClass : s_nodeClasses)
	{
		if (nodeClass == ULogicInputNode::StaticClass())
			continue;

		if (nodeClass == ULogicOutputNode::StaticClass())
			continue;

		if (nodeClass != ULogicNOTNode::StaticClass()) // DEBUG
			continue;

		ULogicNode* LogicNode = nodeClass->GetDefaultObject<ULogicNode>();

		// when dragging from an output pin you can create anything but a wave player
		//if (!ActionMenuBuilder.FromPin || ActionMenuBuilder.FromPin->Direction == EGPD_Input || SoundNode->GetMaxChildNodes() > 0)
		{
			const FText Name = FText::FromString(nodeClass->GetDescription());

			{
				FFormatNamedArguments Arguments;
				Arguments.Add(TEXT("Name"), Name);
				const FText AddToolTip = FText::Format(LOCTEXT("NewNodeTooltip", "Adds {Name} node here"), Arguments);
				TSharedPtr<FLogicGraphSchemaAction_NewNode> NewNodeAction(new FLogicGraphSchemaAction_NewNode(LOCTEXT("NodeAction", "Logic Node"), Name, AddToolTip, 0));
				ActionMenuBuilder.AddAction(NewNodeAction);
				NewNodeAction->LogicNodeClass = nodeClass;
			}

			/*if (bShowSelectedActions &&
				(SoundNode->GetMaxChildNodes() == USoundNode::MAX_ALLOWED_CHILD_NODES ||
				((SoundNodeClass == USoundNodeWavePlayer::StaticClass() && IsSoundWaveSelected) ||
					(SoundNodeClass == USoundNodeDialoguePlayer::StaticClass() && IsDialogueWaveSelected))))
			{
				FFormatNamedArguments Arguments;
				Arguments.Add(TEXT("Name"), Name);
				Arguments.Add(TEXT("SelectedItems"), SelectedItemText);
				const FText MenuDesc = FText::Format(LOCTEXT("NewSoundNodeRandom", "{Name}: {SelectedItems}"), Arguments);
				const FText ToolTip = FText::Format(LOCTEXT("NewSoundNodeRandomTooltip", "Adds a {Name} node for {SelectedItems} here"), Arguments);
				TSharedPtr<FSoundCueGraphSchemaAction_NewFromSelected> NewNodeAction(new FSoundCueGraphSchemaAction_NewFromSelected(LOCTEXT("FromSelected", "From Selected"),
					MenuDesc,
					ToolTip, 0));
				ActionMenuBuilder.AddAction(NewNodeAction);
				NewNodeAction->SoundNodeClass = (SoundNodeClass == USoundNodeWavePlayer::StaticClass() || SoundNodeClass == USoundNodeDialoguePlayer::StaticClass() ? NULL : SoundNodeClass);
			}*/
		}
	}
}

void ULogicGraphSchema::_InitNodeClasses()
{
	if (s_isNodeClassesInitialized)
		return;

	// Construct list of non-abstract sound node classes.
	for (TObjectIterator<UClass> It; It; ++It)
	{
		if (It->IsChildOf(ULogicNode::StaticClass())
			&& !It->HasAnyClassFlags(CLASS_Abstract))
		{
			s_nodeClasses.Add(*It);
		}
	}

	s_nodeClasses.Sort();

	s_isNodeClassesInitialized = true;
}


#undef LOCTEXT_NAMESPACE
