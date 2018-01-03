// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class ULogicBlocksComponent;
class ULogicNode;

#include <CoreMinimal.h>
#include <EdGraph/EdGraph.h>
#include <EdGraph/EdGraphNode.h>
#include <EdGraph/EdGraphPin.h>

#include "LogicGraph.generated.h"


UCLASS(MinimalAPI)
class ULogicGraphNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
	void SetLogicNode(ULogicNode* _node);
	ULogicNode* GetLogicNode() const;

private:
	UPROPERTY() ULogicNode* m_logicNode = nullptr;
};

UCLASS(MinimalAPI)
class ULogicInputGraphNode : public ULogicGraphNode
{
	GENERATED_BODY()

public:
	// UEdGraphNode interface.
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

	/*virtual void ReconstructNode() override;
	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;
	virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* Schema) const override;
	virtual FString GetDocumentationLink() const override;*/
	// End of UEdGraphNode interface.
};

UCLASS(MinimalAPI)
class ULogicOutputGraphNode : public ULogicGraphNode
{
	GENERATED_BODY()

public:
	// UEdGraphNode interface.
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void PinConnectionListChanged(UEdGraphPin* _pin) override;
	// End of UEdGraphNode interface.
};

UCLASS(MinimalAPI)
class ULogicNOTGraphNode : public ULogicGraphNode
{
	GENERATED_BODY()

public:
	// UEdGraphNode interface.
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void PinConnectionListChanged(UEdGraphPin* _pin) override;
	// End of UEdGraphNode interface.
};

UCLASS(MinimalAPI)
class ULogicANDGraphNode : public ULogicGraphNode
{
	GENERATED_BODY()

public:
	// UEdGraphNode interface.
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void PinConnectionListChanged(UEdGraphPin* _pin) override;
	// End of UEdGraphNode interface.

private:
	UEdGraphPin* m_firstOperand = nullptr;
	UEdGraphPin* m_secondOperand = nullptr;
};

UCLASS(MinimalAPI)
class ULogicORGraphNode : public ULogicGraphNode
{
	GENERATED_BODY()

public:
	// UEdGraphNode interface.
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void PinConnectionListChanged(UEdGraphPin* _pin) override;
	// End of UEdGraphNode interface.

private:
	UEdGraphPin* m_firstOperand = nullptr;
	UEdGraphPin* m_secondOperand = nullptr;
};

/**
 * 
 */
UCLASS()
class LOGICBLOCKS_API ULogicGraph : public UEdGraph
{
	GENERATED_BODY()

public:
	static FEdGraphPinType s_ExpressionPinType;

public:
	ULogicBlocksComponent* GetLogicBlocksComponent() const;
};
