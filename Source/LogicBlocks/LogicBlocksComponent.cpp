// Fill out your copyright notice in the Description page of Project Settings.

#include "LogicBlocksComponent.h"

#include <Engine/World.h>

#include <LogicInputBlock.h>
#include <LogicOutputBlock.h>

// Sets default values for this component's properties
ULogicBlocksComponent::ULogicBlocksComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bTickInEditor = true;
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
	else
	{
#endif

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
			output->ValidityBegin();
		}
	}

	if (validity)
	{
		for (auto output : m_logicOutputs)
		{
			output->ValidityTick(DeltaTime);
		}
	}

	if (!validity && m_previousValidity)
	{
		for (auto output : m_logicOutputs)
		{
			output->ValidityEnd();
		}
	}

	m_previousValidity = validity;

#if WITH_EDITOR
	}
#endif
}

void ULogicBlocksComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	m_logicInputs.Empty();
	m_logicOutputs.Empty();
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

	PrimaryComponentTick.RemovePrerequisite(_input, _input->PrimaryActorTick);

	int32 ret = m_logicInputs.Remove(_input);
	check(ret == 1);

	_input->Destroy();
}

void ULogicBlocksComponent::RemoveOutput(ALogicOutputBlock* _output)
{
	check(m_logicOutputs.Find(_output) != INDEX_NONE);

	_output->PrimaryActorTick.RemovePrerequisite(this, PrimaryComponentTick);

	int32 ret = m_logicOutputs.Remove(_output);
	check(ret == 1);

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

void ULogicBlocksComponent::_EditorTick(float _deltaTime)
{

}

