#include "LogicBlocksDetailsCustomization.h"

#include <Widgets/Layout/SBox.h>
#include <Widgets/Layout/SSeparator.h>
#include <Widgets/Text/STextBlock.h>
#include <Widgets/Input/SButton.h>
#include <Widgets/Input/SEditableTextBox.h>
#include <Widgets/SBoxPanel.h>
#include <DetailLayoutBuilder.h>
#include <DetailCategoryBuilder.h>
#include <DetailWidgetRow.h>
#include <IDetailGroup.h>
#include <IDetailPropertyRow.h>
#include <GameFramework/Actor.h>
#include <PropertyCustomizationHelpers.h>
#include <SSplitter.h>
#include <GraphEditor.h>
#include <GenericCommands.h>
#include <ScopedTransaction.h>
#include <BlueprintEditorUtils.h>
#include <Editor.h>
#include <Engine/Selection.h>

#include <LogicBlocksComponent.h>
#include <LogicInputBlock.h>
#include <LogicOutputBlock.h>
#include <LogicGraph.h>

#define LOCTEXT_NAMESPACE "LogicBlocks"

TSharedRef<IDetailCustomization> FLogicBlocksDetailsCustomization::MakeInstance()
{
	return MakeShareable(new FLogicBlocksDetailsCustomization);
}

void FLogicBlocksDetailsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{
	m_detailLayout = &DetailLayout;

	// GET POINTER TO SELECTED COMPONENT
	const TArray< TWeakObjectPtr<UObject> >& selectedObjects = DetailLayout.GetDetailsView()->GetSelectedObjects();
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

	if (!m_selectedComponent.Get())
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
				PropertyCustomizationHelpers::MakeAddButton(FSimpleDelegate::CreateSP(this, &FLogicBlocksDetailsCustomization::_CreateInput), FText(), TAttribute<bool>(this, &FLogicBlocksDetailsCustomization::_CanCreateInput))
			]
		];

		// INPUT BLOCKS LIST
		for (TWeakObjectPtr<ALogicInputBlock> logicBlock : m_selectedComponent->GetInputBlocks())
		{
			check(logicBlock.Get());

			FText t = FText::FromString(logicBlock->GetName());
			IDetailGroup& group = inputsCategory.AddGroup(FName(*logicBlock->GetName()), t);

			group.HeaderRow()
			.NameContent()
			.HAlign(HAlign_Left)
			.MinDesiredWidth(0.0f)
			.MaxDesiredWidth(100.0f)
			[
				SNew(SEditableTextBox)
				.Text(this, &FLogicBlocksDetailsCustomization::_GetActorName, TWeakObjectPtr<AActor>(logicBlock.Get()))
				.OnTextCommitted(this, &FLogicBlocksDetailsCustomization::_OnActorNameCommited, TWeakObjectPtr<AActor>(logicBlock.Get()))
			]
			.ValueContent()
			.HAlign(HAlign_Left)
			.MinDesiredWidth(0.0f)
			[
				PropertyCustomizationHelpers::MakeDeleteButton(FSimpleDelegate::CreateSP(this, &FLogicBlocksDetailsCustomization::_RemoveInput, logicBlock))
			];

			for (TFieldIterator<UProperty> PropIt(logicBlock->GetClass()); PropIt; ++PropIt)
			{
				UProperty* TestProperty = *PropIt;

				if (!TestProperty->HasAnyPropertyFlags(CPF_Edit))
					continue;

				if (TestProperty->HasAnyPropertyFlags(CPF_DisableEditOnInstance))
					continue;

				UObject* outer = TestProperty->GetOuter();
				UClass* outerClass = Cast<UClass>(outer);
				if (outerClass == nullptr)
					continue;

				if (!outerClass->IsChildOf(ALogicInputBlock::StaticClass()))
					continue;

				TArray<UObject*> a;
				a.Add(logicBlock.Get());
				IDetailPropertyRow* invisiblePropertyRow = inputsCategory.AddExternalObjectProperty(a, TestProperty->GetFName());
				IDetailPropertyRow& actualPropertyRow = group.AddPropertyRow(invisiblePropertyRow->GetPropertyHandle().ToSharedRef());
				invisiblePropertyRow->Visibility(EVisibility::Hidden);

				actualPropertyRow.GetPropertyHandle()->SetOnPropertyValueChanged(FSimpleDelegate::CreateRaw(this, &FLogicBlocksDetailsCustomization::_MakeDirty));
				actualPropertyRow.GetPropertyHandle()->SetOnChildPropertyValueChanged(FSimpleDelegate::CreateRaw(this, &FLogicBlocksDetailsCustomization::_MakeDirty));
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
				PropertyCustomizationHelpers::MakeAddButton(FSimpleDelegate::CreateSP(this, &FLogicBlocksDetailsCustomization::_CreateOutput), FText(), TAttribute<bool>(this, &FLogicBlocksDetailsCustomization::_CanCreateOutput))
			]
		];

		// OUTPUT BLOCKS LIST
		for (TWeakObjectPtr<ALogicOutputBlock> logicBlock : m_selectedComponent->GetOutputBlocks())
		{
			check(logicBlock.Get());

			FText t = FText::FromString(logicBlock->GetName());
			IDetailGroup& group = outputsCategory.AddGroup(FName(*logicBlock->GetName()), t);

			group.HeaderRow()
			.NameContent()
			.HAlign(HAlign_Left)
			.MinDesiredWidth(0.0f)
			.MaxDesiredWidth(100.0f)
			[
				SNew(SEditableTextBox)
				.Text(this, &FLogicBlocksDetailsCustomization::_GetActorName, TWeakObjectPtr<AActor>(logicBlock.Get()))
				.OnTextCommitted(this, &FLogicBlocksDetailsCustomization::_OnActorNameCommited, TWeakObjectPtr<AActor>(logicBlock.Get()))
			]
			.ValueContent()
			.HAlign(HAlign_Left)
			.MinDesiredWidth(0.0f)
			[
				PropertyCustomizationHelpers::MakeDeleteButton(FSimpleDelegate::CreateSP(this, &FLogicBlocksDetailsCustomization::_RemoveOutput, logicBlock))
			];

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
				a.Add(logicBlock.Get());
				IDetailPropertyRow* invisiblePropertyRow = outputsCategory.AddExternalObjectProperty(a, TestProperty->GetFName());
				IDetailPropertyRow& actualPropertyRow = group.AddPropertyRow(invisiblePropertyRow->GetPropertyHandle().ToSharedRef());
				invisiblePropertyRow->Visibility(EVisibility::Hidden);

				actualPropertyRow.GetPropertyHandle()->SetOnPropertyValueChanged(FSimpleDelegate::CreateRaw(this, &FLogicBlocksDetailsCustomization::_MakeDirty));
				actualPropertyRow.GetPropertyHandle()->SetOnChildPropertyValueChanged(FSimpleDelegate::CreateRaw(this, &FLogicBlocksDetailsCustomization::_MakeDirty));
			}
		}
	}

	// LOGIC
	{
		IDetailCategoryBuilder& logicCategory = DetailLayout.EditCategory("Logic", FText::GetEmpty(), ECategoryPriority::Important);

		IDetailPropertyRow& propertyRow = logicCategory.AddProperty(TEXT("IsAdvancedModeEnabled"));
		propertyRow.GetPropertyHandle()->SetOnPropertyValueChanged(FSimpleDelegate::CreateSP(this, &FLogicBlocksDetailsCustomization::_MakeDirty));

		if (m_selectedComponent->IsAdvancedModeEnabled)
		{
			if (!m_graphEditorCommands.IsValid())
			{
				m_graphEditorCommands = MakeShareable(new FUICommandList);

				m_graphEditorCommands->MapAction(FGenericCommands::Get().Delete,
					FExecuteAction::CreateSP(this, &FLogicBlocksDetailsCustomization::_DeleteSelectedNodes),
					FCanExecuteAction::CreateSP(this, &FLogicBlocksDetailsCustomization::_CanDeleteNodes)
				);
			}

			TSharedPtr<SGraphEditor> graphEditor = SNew(SGraphEditor)
				.AdditionalCommands(m_graphEditorCommands)
				.GraphToEdit(m_selectedComponent->GetLogicGraph())
				.IsEditable(true)
				.AutoExpandActionMenu(true);

			m_logicGraphEditor = TWeakPtr<SGraphEditor>(graphEditor);

			FText t = FText::FromString(TEXT("Graph"));
			logicCategory.AddCustomRow(t)
			[
				SNew(SBox)
				.VAlign(VAlign_Fill)
				.HeightOverride(300.f)
				[
					graphEditor.ToSharedRef()
				]
			];
		}
	}
}

FLogicBlocksDetailsCustomization::FLogicBlocksDetailsCustomization()
{
	GEditor->OnBlueprintCompiled().AddRaw(this, &FLogicBlocksDetailsCustomization::_MakeDirty);

	USelection::SelectionChangedEvent.AddRaw(this, &FLogicBlocksDetailsCustomization::_OnSelectionChanged);
}

FLogicBlocksDetailsCustomization::~FLogicBlocksDetailsCustomization()
{
	USelection::SelectionChangedEvent.RemoveAll(this);
	GEditor->OnBlueprintCompiled().RemoveAll(this);
}

bool FLogicBlocksDetailsCustomization::_CanCreateInput() const
{
	if (!m_selectedComponent.Get())
		return false;

	return m_selectedComponent->LogicInputBlockClass != nullptr;
}

void FLogicBlocksDetailsCustomization::_CreateInput()
{
	if (!m_selectedComponent.Get())
		return;

	m_selectedComponent->CreateInput(m_selectedComponent->LogicInputBlockClass);
	m_detailLayout->ForceRefreshDetails();
}

void FLogicBlocksDetailsCustomization::_RemoveInput(TWeakObjectPtr<ALogicInputBlock> _input)
{
	if (!m_selectedComponent.Get())
		return;

	if (!_input.Get())
		return;

	m_selectedComponent->RemoveInput(_input.Get());
	m_detailLayout->ForceRefreshDetails();
}

bool FLogicBlocksDetailsCustomization::_CanCreateOutput() const
{
	if (!m_selectedComponent.Get())
		return false;

	return m_selectedComponent->LogicOutputBlockClass != nullptr;
}

void FLogicBlocksDetailsCustomization::_CreateOutput()
{
	if (!m_selectedComponent.Get())
		return;

	m_selectedComponent->CreateOutput(m_selectedComponent->LogicOutputBlockClass);
	m_detailLayout->ForceRefreshDetails();
}

void FLogicBlocksDetailsCustomization::_RemoveOutput(TWeakObjectPtr<ALogicOutputBlock> _output)
{
	if (!m_selectedComponent.Get())
		return;

	if (!_output.Get())
		return;

	m_selectedComponent->RemoveOutput(_output.Get());
	m_detailLayout->ForceRefreshDetails();
}

FText FLogicBlocksDetailsCustomization::_GetActorName(TWeakObjectPtr<AActor> _actor) const
{
	if (!m_selectedComponent.Get())
		return FText::GetEmpty();

	if (!_actor.Get())
		return FText::GetEmpty();

	return FText::FromString(_actor->GetActorLabel());
}

void FLogicBlocksDetailsCustomization::_OnActorNameCommited(const FText& _text, ETextCommit::Type _commitType, TWeakObjectPtr<AActor> _actor)
{
	if (!_actor.Get())
		return;

	if (!m_selectedComponent.Get())
		return;

	if (_commitType != ETextCommit::OnEnter)
		return;

	_actor->SetActorLabel(_text.ToString());
}

void FLogicBlocksDetailsCustomization::_DeleteSelectedNodes()
{
	check(m_logicGraphEditor.IsValid());

	const FScopedTransaction Transaction(LOCTEXT("LogicBlocksDeleteSelectedNode", "Delete Selected Logic Node"));

	ULogicGraph* logicGraph = Cast<ULogicGraph>(m_logicGraphEditor.Pin()->GetCurrentGraph());
	check(logicGraph);

	logicGraph->Modify();

	FGraphPanelSelectionSet selectedNodes = m_logicGraphEditor.Pin()->GetSelectedNodes();

	m_logicGraphEditor.Pin()->ClearSelectionSet();

	for (FGraphPanelSelectionSet::TConstIterator nodeIt(selectedNodes); nodeIt; ++nodeIt)
	{
		ULogicGraphNode* graphNode = Cast<ULogicGraphNode>(*nodeIt);
		check(graphNode);

		if (graphNode->CanUserDeleteNode())
		{
			ULogicNode* toDeleteNode = graphNode->GetLogicNode();
			logicGraph->GetLogicBlocksComponent()->DestroyLogicNode(toDeleteNode);
		}
	}
}

bool FLogicBlocksDetailsCustomization::_CanDeleteNodes()
{
	check(m_logicGraphEditor.IsValid());

	return m_logicGraphEditor.Pin()->GetSelectedNodes().Num() > 0;
}

void FLogicBlocksDetailsCustomization::_MakeDirty()
{
	if (!m_detailLayout)
		return;

	m_detailLayout->ForceRefreshDetails();
}

void FLogicBlocksDetailsCustomization::_OnSelectionChanged(UObject* _object)
{
	if (!m_selectedComponent.Get())
		return;

	USelection* selection = Cast<USelection>(_object); // WTF unreal ? why not typing the delegate ??
	check(selection);

	TArray<TWeakObjectPtr<UObject>> selectedObjects;
	selection->GetSelectedObjects(selectedObjects);

	bool isComponentInSelection = false;
	for (TWeakObjectPtr<UObject> selectedObject : selectedObjects)
	{
		if (selectedObject.Get() == m_selectedComponent.Get())
		{
			isComponentInSelection = true;
			break;
		}
	}

	if (!isComponentInSelection)
	{
		m_selectedComponent.Reset();
		m_detailLayout = nullptr;
		m_logicGraphEditor.Reset();
	}
}

#undef LOCTEXT_NAMESPACE
