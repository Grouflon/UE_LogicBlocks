// Fill out your copyright notice in the Description page of Project Settings.

#include "LogicOutputBlock.h"


ALogicOutputBlock::ALogicOutputBlock()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

void ALogicOutputBlock::ValidityBegin_Implementation()
{

}

void ALogicOutputBlock::ValidityTick_Implementation(float _deltaTime)
{

}

void ALogicOutputBlock::ValidityEnd_Implementation()
{

}
