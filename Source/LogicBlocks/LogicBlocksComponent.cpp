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

	// ...
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

	// ...
}

void ULogicBlocksComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	for (ALogicInputBlock* block : m_logicInputs)
	{
		block->OnDestroyed.RemoveDynamic(this, &ULogicBlocksComponent::_OnInputBlockDestroyed);
	}
	m_logicInputs.Empty();

	for (ALogicOutputBlock* block : m_logicOutputs)
	{
		block->OnDestroyed.RemoveDynamic(this, &ULogicBlocksComponent::_OnOutputBlockDestroyed);
	}
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

	inputBlock->OnDestroyed.AddDynamic(this, &ULogicBlocksComponent::_OnInputBlockDestroyed);
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

	outputBlock->OnDestroyed.AddDynamic(this, &ULogicBlocksComponent::_OnOutputBlockDestroyed);
}

const TArray<ALogicInputBlock*>& ULogicBlocksComponent::GetInputBlocks() const
{
	return m_logicInputs;
}

const TArray<ALogicOutputBlock*>& ULogicBlocksComponent::GetOutputBlocks() const
{
	return m_logicOutputs;
}

void ULogicBlocksComponent::_OnInputBlockDestroyed(AActor * _destroyedActor)
{
	ALogicInputBlock* block = Cast<ALogicInputBlock>(_destroyedActor);
	check(block);
	int32 ret = m_logicInputs.Remove(block);
	check(ret == 1);
	_destroyedActor->OnDestroyed.RemoveDynamic(this, &ULogicBlocksComponent::_OnInputBlockDestroyed);
}

void ULogicBlocksComponent::_OnOutputBlockDestroyed(AActor * _destroyedActor)
{
	ALogicOutputBlock* block = Cast<ALogicOutputBlock>(_destroyedActor);
	check(block);
	int32 ret = m_logicOutputs.Remove(block);
	check(ret == 1);
	_destroyedActor->OnDestroyed.RemoveDynamic(this, &ULogicBlocksComponent::_OnOutputBlockDestroyed);
}
