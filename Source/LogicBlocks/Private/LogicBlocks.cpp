// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "LogicBlocks.h"

#include <Modules/ModuleManager.h>
#include <PropertyEditorModule.h>

#include <LogicBlocksComponent.h>
#include <LogicBlocksDetailsCustomization.h>

#define LOCTEXT_NAMESPACE "LogicBlocks"

void FLogicBlocksModule::StartupModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout(ULogicBlocksComponent::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FLogicBlocksDetailsCustomization::MakeInstance));
	PropertyModule.NotifyCustomizationModuleChanged();
}

void FLogicBlocksModule::ShutdownModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomClassLayout(ULogicBlocksComponent::StaticClass()->GetFName());
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLogicBlocksModule, LogicBlocks)