// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class ALogicInputBlock;
class ALogicOutputBlock;

#include "CoreMinimal.h"
#include "EdGraphSchema_K2.h"
#include "LogicGraphSchema.generated.h"


USTRUCT()
struct LOGICBLOCKS_API FLogicGraphSchemaAction_NewNode : public FEdGraphSchemaAction
{
	GENERATED_BODY()

	UClass* LogicNodeClass = nullptr;

	FLogicGraphSchemaAction_NewNode()
		: FEdGraphSchemaAction()
	{}

	FLogicGraphSchemaAction_NewNode(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping)
		: FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping)
	{}

	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
};


USTRUCT()
struct LOGICBLOCKS_API FLogicGraphSchemaAction_NewInputNode : public FEdGraphSchemaAction
{
	GENERATED_BODY()

	ALogicInputBlock* Input = nullptr;

	FLogicGraphSchemaAction_NewInputNode()
		: FEdGraphSchemaAction()
	{}

	FLogicGraphSchemaAction_NewInputNode(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping)
		: FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping)
	{}

	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
};

USTRUCT()
struct LOGICBLOCKS_API FLogicGraphSchemaAction_NewOutputNode : public FEdGraphSchemaAction
{
	GENERATED_BODY()

	ALogicOutputBlock* Output = nullptr;

	FLogicGraphSchemaAction_NewOutputNode()
		: FEdGraphSchemaAction()
	{}

	FLogicGraphSchemaAction_NewOutputNode(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping)
		: FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping)
	{}

	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
};


/**
 * 
 */
UCLASS()
class LOGICBLOCKS_API ULogicGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()
	
public:

	//~ Begin EdGraphSchema Interface
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
	virtual void GetContextMenuActions(const UEdGraph* CurrentGraph, const UEdGraphNode* InGraphNode, const UEdGraphPin* InGraphPin, class FMenuBuilder* MenuBuilder, bool bIsDebugging) const override;
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;
	virtual bool TryCreateConnection(UEdGraphPin* A, UEdGraphPin* B) const override;
	virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;
	//~ End EdGraphSchema Interface
	
	static FLinearColor s_expressionTypeColor;

private:
	void _GetAllNodeActions(FGraphActionMenuBuilder& ActionMenuBuilder/*, bool bShowSelectedActions*/) const;

	/** Generates a list of all available LogicNode classes */
	static void _InitNodeClasses();

	/** A list of all available LogicNode classes */
	static TArray<UClass*> s_nodeClasses;
	/** Whether the list of LogicNode classes has been populated */
	static bool s_isNodeClassesInitialized;

};
