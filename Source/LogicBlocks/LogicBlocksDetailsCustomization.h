#pragma once

class ULogicBlocksComponent;
class ALogicInputBlock;
class ALogicOutputBlock;

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

	TWeakObjectPtr<ULogicBlocksComponent> m_selectedComponent;
	IDetailLayoutBuilder* m_detailLayout = nullptr;
};