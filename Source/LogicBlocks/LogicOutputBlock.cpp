// Fill out your copyright notice in the Description page of Project Settings.

#include "LogicOutputBlock.h"


ALogicOutputBlock::ALogicOutputBlock()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

void ALogicOutputBlock::BeginValidity_Implementation()
{

}

void ALogicOutputBlock::TickValidity_Implementation(float _deltaTime)
{

}

void ALogicOutputBlock::EndValidity_Implementation()
{

}
