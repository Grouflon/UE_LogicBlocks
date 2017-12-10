// Fill out your copyright notice in the Description page of Project Settings.

#include "LogicBlocks.h"
#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

#include <LogicBlocksComponent.h>
#include <LogicInputBlock.h>
#include <LogicOutputBlock.h>

#include "IDetailCustomization.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SSeparator.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailGroup.h"
#include "IDetailPropertyRow.h"
#include "GameFramework/Actor.h"
#include "PropertyCustomizationHelpers.h"
#include "SSplitter.h"

#define LOCTEXT_NAMESPACE "LogicBlocks"

class FlogicBlocksDetailsCustomization : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance()
	{
		return MakeShareable(new FlogicBlocksDetailsCustomization);
	}

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override
	{
		m_detailLayout = &DetailLayout;

		// GET POINTER TO SELECTED COMPONENT
		const TArray< TWeakObjectPtr<UObject> >& selectedObjects = DetailLayout.GetDetailsView().GetSelectedObjects();
		m_selectedComponent = nullptr;
		for (int32 ObjectIndex = 0; ObjectIndex < selectedObjects.Num(); ++ObjectIndex)
		{
			UObject* TestObject = selectedObjects[ObjectIndex].Get();
			if (AActor* CurrentActor = Cast<AActor>(TestObject))
			{
				if (ULogicBlocksComponent* CurrentComponent = CurrentActor->FindComponentByClass<ULogicBlocksComponent>())
				{
					m_selectedComponent = CurrentComponent;
					break;
				}
			}
			else if (ULogicBlocksComponent* TestComponent = Cast<ULogicBlocksComponent>(TestObject))
			{
				m_selectedComponent = TestComponent;
				break;
			}
		}

		if (!m_selectedComponent)
			return;

		// INPUT BLOCKS
		{
			IDetailCategoryBuilder& inputsCategory = DetailLayout.EditCategory("Inputs", FText::GetEmpty(), ECategoryPriority::Important);

			// INPUT LIST + CREATION BUTTON
			IDetailPropertyRow& propertyRow = inputsCategory.AddProperty(GET_MEMBER_NAME_CHECKED(ULogicBlocksComponent, LogicInputBlockClass));
			propertyRow.DisplayName(LOCTEXT("InputClass", "Add Input"));
			propertyRow.ShowPropertyButtons(false);

			TSharedPtr<SWidget> nameWidget;
			TSharedPtr<SWidget> valueWidget;
			propertyRow.GetDefaultWidgets(nameWidget, valueWidget);

			propertyRow.CustomWidget()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(5)
				[
					nameWidget.ToSharedRef()
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(5)
				[
					valueWidget.ToSharedRef()
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(5)
				[
					PropertyCustomizationHelpers::MakeAddButton(FSimpleDelegate::CreateSP(this, &FlogicBlocksDetailsCustomization::CreateInput), FText(), TAttribute<bool>(this, &FlogicBlocksDetailsCustomization::CanCreateInput))
				]
			];

			// INPUT BLOCKS LIST
			for (ALogicInputBlock* logicBlock : m_selectedComponent->GetInputBlocks())
			{
				FText t = FText::FromString(logicBlock->GetName());
				IDetailGroup& group = inputsCategory.AddGroup(FName(*logicBlock->GetName()), t);

				for (TFieldIterator<UProperty> PropIt(logicBlock->GetClass()); PropIt; ++PropIt)
				{
					UProperty* TestProperty = *PropIt;

					if (!TestProperty->HasAnyPropertyFlags(CPF_Edit))
						continue;

					UObject* outer = TestProperty->GetOuter();
					UClass* outerClass = Cast<UClass>(outer);
					if (outerClass == nullptr)
						continue;

					if (!outerClass->IsChildOf(ALogicInputBlock::StaticClass()))
						continue;

					TArray<UObject*> a;
					a.Add(logicBlock);
					IDetailPropertyRow* propertyRow = inputsCategory.AddExternalProperty(a, TestProperty->GetFName());

					TSharedPtr<SWidget> nameWidget;
					TSharedPtr<SWidget> valueWidget;
					propertyRow->GetDefaultWidgets(nameWidget, valueWidget, group.AddWidgetRow());
					propertyRow->Visibility(EVisibility::Hidden);
				}
			}
		}

		// OUTPUT BLOCKS
		{
			IDetailCategoryBuilder& outputsCategory = DetailLayout.EditCategory("Outputs", FText::GetEmpty(), ECategoryPriority::Important);

			// OUTPUT LIST + CREATION BUTTON
			IDetailPropertyRow& propertyRow = outputsCategory.AddProperty(GET_MEMBER_NAME_CHECKED(ULogicBlocksComponent, LogicOutputBlockClass));
			propertyRow.DisplayName(LOCTEXT("OutputClass", "Add Output"));
			propertyRow.ShowPropertyButtons(false);

			TSharedPtr<SWidget> nameWidget;
			TSharedPtr<SWidget> valueWidget;
			propertyRow.GetDefaultWidgets(nameWidget, valueWidget);

			propertyRow.CustomWidget()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(5)
				[
					nameWidget.ToSharedRef()
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(5)
				[
					valueWidget.ToSharedRef()
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(5)
				[
					PropertyCustomizationHelpers::MakeAddButton(FSimpleDelegate::CreateSP(this, &FlogicBlocksDetailsCustomization::CreateOutput), FText(), TAttribute<bool>(this, &FlogicBlocksDetailsCustomization::CanCreateOutput))
				]
			];

			// INPUT BLOCKS LIST
			for (ALogicOutputBlock* logicBlock : m_selectedComponent->GetOutputBlocks())
			{
				FText t = FText::FromString(logicBlock->GetName());
				IDetailGroup& group = outputsCategory.AddGroup(FName(*logicBlock->GetName()), t);

				for (TFieldIterator<UProperty> PropIt(logicBlock->GetClass()); PropIt; ++PropIt)
				{
					UProperty* TestProperty = *PropIt;

					if (!TestProperty->HasAnyPropertyFlags(CPF_Edit))
						continue;

					UObject* outer = TestProperty->GetOuter();
					UClass* outerClass = Cast<UClass>(outer);
					if (outerClass == nullptr)
						continue;

					if (!outerClass->IsChildOf(ALogicOutputBlock::StaticClass()))
						continue;

					TArray<UObject*> a;
					a.Add(logicBlock);
					IDetailPropertyRow* propertyRow = outputsCategory.AddExternalProperty(a, TestProperty->GetFName());

					TSharedPtr<SWidget> nameWidget;
					TSharedPtr<SWidget> valueWidget;
					propertyRow->GetDefaultWidgets(nameWidget, valueWidget, group.AddWidgetRow());
					propertyRow->Visibility(EVisibility::Hidden);
				}
			}
		}
	}

	bool CanCreateInput() const
	{
		return m_selectedComponent->LogicInputBlockClass != nullptr;
	}

	void CreateInput()
	{
		m_selectedComponent->CreateInput(m_selectedComponent->LogicInputBlockClass);
		m_detailLayout->ForceRefreshDetails();
	}

	bool CanCreateOutput() const
	{
		return m_selectedComponent->LogicOutputBlockClass != nullptr;
	}

	void CreateOutput()
	{
		m_selectedComponent->CreateOutput(m_selectedComponent->LogicOutputBlockClass);
		m_detailLayout->ForceRefreshDetails();
	}

	ULogicBlocksComponent* m_selectedComponent = nullptr;
	IDetailLayoutBuilder* m_detailLayout = nullptr;
};


class FLogicBlocksModuleImpl
	: public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule() override
	{
		FDefaultGameModuleImpl::StartupModule();

		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.RegisterCustomClassLayout(ULogicBlocksComponent::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FlogicBlocksDetailsCustomization::MakeInstance));
		PropertyModule.NotifyCustomizationModuleChanged();
	}

	virtual void ShutdownModule() override
	{


		FDefaultGameModuleImpl::ShutdownModule();
	}
};

#undef LOCTEXT_NAMESPACE

IMPLEMENT_PRIMARY_GAME_MODULE( FLogicBlocksModuleImpl, LogicBlocks, "LogicBlocks" );
