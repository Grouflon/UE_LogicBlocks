// Fill out your copyright notice in the Description page of Project Settings.

#include "LogicBlocks.h"

#include <Modules/ModuleManager.h>
#include <PropertyEditorModule.h>

#include <LogicBlocksComponent.h>
#include <LogicBlocksDetailsCustomization.h>

#define LOCTEXT_NAMESPACE "LogicBlocks"

void FLogicBlocksModuleImpl::StartupModule()
{
	FDefaultGameModuleImpl::StartupModule();

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout(ULogicBlocksComponent::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FLogicBlocksDetailsCustomization::MakeInstance));
	PropertyModule.NotifyCustomizationModuleChanged();
}

void FLogicBlocksModuleImpl::ShutdownModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomClassLayout(ULogicBlocksComponent::StaticClass()->GetFName());

	FDefaultGameModuleImpl::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_PRIMARY_GAME_MODULE(FLogicBlocksModuleImpl, LogicBlocks, "LogicBlocks");
