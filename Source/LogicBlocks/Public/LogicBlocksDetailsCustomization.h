#pragma once

class ULogicBlocksComponent;
class ALogicInputBlock;
class ALogicOutputBlock;
class SGraphEditor;

#include <IDetailCustomization.h>

class FLogicBlocksDetailsCustomization : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

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

	TWeakObjectPtr<ULogicBlocksComponent> m_selectedComponent;
	TWeakPtr<SGraphEditor> m_logicGraphEditor;
	IDetailLayoutBuilder* m_detailLayout = nullptr;

	TSharedPtr<FUICommandList> m_graphEditorCommands;
};