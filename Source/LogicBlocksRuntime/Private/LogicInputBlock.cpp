// Fill out your copyright notice in the Description page of Project Settings.

#include "LogicInputBlock.h"


ALogicInputBlock::ALogicInputBlock()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

bool ALogicInputBlock::Evaluate_Implementation()
{
	return true;
}
