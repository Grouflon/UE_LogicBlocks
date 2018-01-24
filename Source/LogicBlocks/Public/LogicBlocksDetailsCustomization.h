#pragma once

class ULogicBlocksComponent;
class ALogicInputBlock;
class ALogicOutputBlock;
class SGraphEditor;

#include <IDetailCustomization.h>

// NOTE(Remi|2018/01/24): Quick temp fix for issue UE-54352
#define GRAPH_REFERENCELEAK_FIX 1

#if GRAPH_REFERENCELEAK_FIX
#include <UnrealEdMisc.h>
#endif

class FLogicBlocksDetailsCustomization : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

	FLogicBlocksDetailsCustomization();
	virtual ~FLogicBlocksDetailsCustomization();

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;

private:

	bool _CanCreateInput() const;
	void _CreateInput();
	void _RemoveInput(TWeakObjectPtr<ALogicInputBlock> _input);
	
	bool _CanCreateOutput() const;
	void _CreateOutput();
	void _RemoveOutput(TWeakObjectPtr<ALogicOutputBlock> _output);

	FText _GetActorName(TWeakObjectPtr<AActor> _input) const;
	void _OnActorNameCommited(const FText& _text, ETextCommit::Type _commitType, TWeakObjectPtr<AActor> _input);

	void _DeleteSelectedNodes();
	bool _CanDeleteNodes();

	void _MakeDirty();

	void _OnSelectionChanged(UObject* _object);

	TWeakObjectPtr<ULogicBlocksComponent> m_selectedComponent;
	TWeakPtr<SGraphEditor> m_logicGraphEditor;
	IDetailLayoutBuilder* m_detailLayout = nullptr;

	TSharedPtr<FUICommandList> m_graphEditorCommands;

#if GRAPH_REFERENCELEAK_FIX
	void _OnMapChanged(UWorld* _newWorld, EMapChangeType _mapChangeType);
	TSharedPtr<SBox> m_graphEditorContainer;
#endif
};