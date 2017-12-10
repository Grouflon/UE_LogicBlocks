// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "LogicBlocks.generated.dep.h"
PRAGMA_DISABLE_OPTIMIZATION
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCode1LogicBlocks() {}
#if USE_COMPILED_IN_NATIVES
// Cross Module References
	ENGINE_API class UClass* Z_Construct_UClass_AActor_NoRegister();
	ENGINE_API class UClass* Z_Construct_UClass_UActorComponent();
	ENGINE_API class UClass* Z_Construct_UClass_AGameModeBase();
	ENGINE_API class UClass* Z_Construct_UClass_AActor();

	LOGICBLOCKS_API class UFunction* Z_Construct_UFunction_ULogicBlocksComponent__OnInputBlockDestroyed();
	LOGICBLOCKS_API class UFunction* Z_Construct_UFunction_ULogicBlocksComponent__OnOutputBlockDestroyed();
	LOGICBLOCKS_API class UClass* Z_Construct_UClass_ULogicBlocksComponent_NoRegister();
	LOGICBLOCKS_API class UClass* Z_Construct_UClass_ULogicBlocksComponent();
	LOGICBLOCKS_API class UClass* Z_Construct_UClass_ALogicBlocksGameModeBase_NoRegister();
	LOGICBLOCKS_API class UClass* Z_Construct_UClass_ALogicBlocksGameModeBase();
	LOGICBLOCKS_API class UFunction* Z_Construct_UFunction_ALogicInputBlock_CheckInput();
	LOGICBLOCKS_API class UClass* Z_Construct_UClass_ALogicInputBlock_NoRegister();
	LOGICBLOCKS_API class UClass* Z_Construct_UClass_ALogicInputBlock();
	LOGICBLOCKS_API class UFunction* Z_Construct_UFunction_ALogicOutputBlock_ValidityStart();
	LOGICBLOCKS_API class UFunction* Z_Construct_UFunction_ALogicOutputBlock_ValidityStop();
	LOGICBLOCKS_API class UFunction* Z_Construct_UFunction_ALogicOutputBlock_ValidityTick();
	LOGICBLOCKS_API class UClass* Z_Construct_UClass_ALogicOutputBlock_NoRegister();
	LOGICBLOCKS_API class UClass* Z_Construct_UClass_ALogicOutputBlock();
	LOGICBLOCKS_API class UPackage* Z_Construct_UPackage__Script_LogicBlocks();
	void ULogicBlocksComponent::StaticRegisterNativesULogicBlocksComponent()
	{
		UClass* Class = ULogicBlocksComponent::StaticClass();
		static const TNameNativePtrPair<ANSICHAR> AnsiFuncs[] = {
			{ "_OnInputBlockDestroyed", (Native)&ULogicBlocksComponent::exec_OnInputBlockDestroyed },
			{ "_OnOutputBlockDestroyed", (Native)&ULogicBlocksComponent::exec_OnOutputBlockDestroyed },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, AnsiFuncs, 2);
	}
	UFunction* Z_Construct_UFunction_ULogicBlocksComponent__OnInputBlockDestroyed()
	{
		struct LogicBlocksComponent_event_OnInputBlockDestroyed_Parms
		{
			AActor* _destroyedActor;
		};
		UObject* Outer=Z_Construct_UClass_ULogicBlocksComponent();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("_OnInputBlockDestroyed"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x00040401, 65535, sizeof(LogicBlocksComponent_event_OnInputBlockDestroyed_Parms));
			UProperty* NewProp__destroyedActor = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("_destroyedActor"), RF_Public|RF_Transient|RF_MarkAsNative) UObjectProperty(CPP_PROPERTY_BASE(_destroyedActor, LogicBlocksComponent_event_OnInputBlockDestroyed_Parms), 0x0010000000000080, Z_Construct_UClass_AActor_NoRegister());
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("LogicBlocksComponent.h"));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_ULogicBlocksComponent__OnOutputBlockDestroyed()
	{
		struct LogicBlocksComponent_event_OnOutputBlockDestroyed_Parms
		{
			AActor* _destroyedActor;
		};
		UObject* Outer=Z_Construct_UClass_ULogicBlocksComponent();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("_OnOutputBlockDestroyed"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x00040401, 65535, sizeof(LogicBlocksComponent_event_OnOutputBlockDestroyed_Parms));
			UProperty* NewProp__destroyedActor = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("_destroyedActor"), RF_Public|RF_Transient|RF_MarkAsNative) UObjectProperty(CPP_PROPERTY_BASE(_destroyedActor, LogicBlocksComponent_event_OnOutputBlockDestroyed_Parms), 0x0010000000000080, Z_Construct_UClass_AActor_NoRegister());
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("LogicBlocksComponent.h"));
#endif
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ULogicBlocksComponent_NoRegister()
	{
		return ULogicBlocksComponent::StaticClass();
	}
	UClass* Z_Construct_UClass_ULogicBlocksComponent()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_UActorComponent();
			Z_Construct_UPackage__Script_LogicBlocks();
			OuterClass = ULogicBlocksComponent::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= 0x20B00080;

				OuterClass->LinkChild(Z_Construct_UFunction_ULogicBlocksComponent__OnInputBlockDestroyed());
				OuterClass->LinkChild(Z_Construct_UFunction_ULogicBlocksComponent__OnOutputBlockDestroyed());

PRAGMA_DISABLE_DEPRECATION_WARNINGS
				UProperty* NewProp_m_logicOutputs = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("m_logicOutputs"), RF_Public|RF_Transient|RF_MarkAsNative) UArrayProperty(CPP_PROPERTY_BASE(m_logicOutputs, ULogicBlocksComponent), 0x0040000000000000);
				UProperty* NewProp_m_logicOutputs_Inner = new(EC_InternalUseOnlyConstructor, NewProp_m_logicOutputs, TEXT("m_logicOutputs"), RF_Public|RF_Transient|RF_MarkAsNative) UObjectProperty(FObjectInitializer(), EC_CppProperty, 0, 0x0000000000000000, Z_Construct_UClass_ALogicOutputBlock_NoRegister());
				UProperty* NewProp_m_logicInputs = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("m_logicInputs"), RF_Public|RF_Transient|RF_MarkAsNative) UArrayProperty(CPP_PROPERTY_BASE(m_logicInputs, ULogicBlocksComponent), 0x0040000000000000);
				UProperty* NewProp_m_logicInputs_Inner = new(EC_InternalUseOnlyConstructor, NewProp_m_logicInputs, TEXT("m_logicInputs"), RF_Public|RF_Transient|RF_MarkAsNative) UObjectProperty(FObjectInitializer(), EC_CppProperty, 0, 0x0000000000000000, Z_Construct_UClass_ALogicInputBlock_NoRegister());
				UProperty* NewProp_LogicOutputBlockClass = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("LogicOutputBlockClass"), RF_Public|RF_Transient|RF_MarkAsNative) UClassProperty(CPP_PROPERTY_BASE(LogicOutputBlockClass, ULogicBlocksComponent), 0x0014000000000001, Z_Construct_UClass_ALogicOutputBlock_NoRegister(), UClass::StaticClass());
				UProperty* NewProp_LogicInputBlockClass = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("LogicInputBlockClass"), RF_Public|RF_Transient|RF_MarkAsNative) UClassProperty(CPP_PROPERTY_BASE(LogicInputBlockClass, ULogicBlocksComponent), 0x0014000000000001, Z_Construct_UClass_ALogicInputBlock_NoRegister(), UClass::StaticClass());
PRAGMA_ENABLE_DEPRECATION_WARNINGS
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_ULogicBlocksComponent__OnInputBlockDestroyed(), "_OnInputBlockDestroyed"); // 3220159366
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_ULogicBlocksComponent__OnOutputBlockDestroyed(), "_OnOutputBlockDestroyed"); // 2575601716
				static TCppClassTypeInfo<TCppClassTypeTraits<ULogicBlocksComponent> > StaticCppClassTypeInfo;
				OuterClass->SetCppTypeInfo(&StaticCppClassTypeInfo);
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("BlueprintSpawnableComponent"), TEXT(""));
				MetaData->SetValue(OuterClass, TEXT("ClassGroupNames"), TEXT("Custom"));
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("LogicBlocksComponent.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("LogicBlocksComponent.h"));
				MetaData->SetValue(NewProp_m_logicOutputs, TEXT("ModuleRelativePath"), TEXT("LogicBlocksComponent.h"));
				MetaData->SetValue(NewProp_m_logicInputs, TEXT("ModuleRelativePath"), TEXT("LogicBlocksComponent.h"));
				MetaData->SetValue(NewProp_LogicOutputBlockClass, TEXT("Category"), TEXT("LogicBlocksComponent"));
				MetaData->SetValue(NewProp_LogicOutputBlockClass, TEXT("ModuleRelativePath"), TEXT("LogicBlocksComponent.h"));
				MetaData->SetValue(NewProp_LogicInputBlockClass, TEXT("Category"), TEXT("LogicBlocksComponent"));
				MetaData->SetValue(NewProp_LogicInputBlockClass, TEXT("ModuleRelativePath"), TEXT("LogicBlocksComponent.h"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULogicBlocksComponent, 1394580382);
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULogicBlocksComponent(Z_Construct_UClass_ULogicBlocksComponent, &ULogicBlocksComponent::StaticClass, TEXT("/Script/LogicBlocks"), TEXT("ULogicBlocksComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULogicBlocksComponent);
	void ALogicBlocksGameModeBase::StaticRegisterNativesALogicBlocksGameModeBase()
	{
	}
	UClass* Z_Construct_UClass_ALogicBlocksGameModeBase_NoRegister()
	{
		return ALogicBlocksGameModeBase::StaticClass();
	}
	UClass* Z_Construct_UClass_ALogicBlocksGameModeBase()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_AGameModeBase();
			Z_Construct_UPackage__Script_LogicBlocks();
			OuterClass = ALogicBlocksGameModeBase::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= 0x20900288;


				static TCppClassTypeInfo<TCppClassTypeTraits<ALogicBlocksGameModeBase> > StaticCppClassTypeInfo;
				OuterClass->SetCppTypeInfo(&StaticCppClassTypeInfo);
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("HideCategories"), TEXT("Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation"));
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("LogicBlocksGameModeBase.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("LogicBlocksGameModeBase.h"));
				MetaData->SetValue(OuterClass, TEXT("ShowCategories"), TEXT("Input|MouseInput Input|TouchInput"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	IMPLEMENT_CLASS(ALogicBlocksGameModeBase, 4195441553);
	static FCompiledInDefer Z_CompiledInDefer_UClass_ALogicBlocksGameModeBase(Z_Construct_UClass_ALogicBlocksGameModeBase, &ALogicBlocksGameModeBase::StaticClass, TEXT("/Script/LogicBlocks"), TEXT("ALogicBlocksGameModeBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ALogicBlocksGameModeBase);
	static FName NAME_ALogicInputBlock_CheckInput = FName(TEXT("CheckInput"));
	bool ALogicInputBlock::CheckInput()
	{
		LogicInputBlock_eventCheckInput_Parms Parms;
		ProcessEvent(FindFunctionChecked(NAME_ALogicInputBlock_CheckInput),&Parms);
		return !!Parms.ReturnValue;
	}
	void ALogicInputBlock::StaticRegisterNativesALogicInputBlock()
	{
	}
	UFunction* Z_Construct_UFunction_ALogicInputBlock_CheckInput()
	{
		UObject* Outer=Z_Construct_UClass_ALogicInputBlock();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("CheckInput"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x08020800, 65535, sizeof(LogicInputBlock_eventCheckInput_Parms));
			CPP_BOOL_PROPERTY_BITMASK_STRUCT(ReturnValue, LogicInputBlock_eventCheckInput_Parms, bool);
			UProperty* NewProp_ReturnValue = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("ReturnValue"), RF_Public|RF_Transient|RF_MarkAsNative) UBoolProperty(FObjectInitializer(), EC_CppProperty, CPP_BOOL_PROPERTY_OFFSET(ReturnValue, LogicInputBlock_eventCheckInput_Parms), 0x0010000000000580, CPP_BOOL_PROPERTY_BITMASK(ReturnValue, LogicInputBlock_eventCheckInput_Parms), sizeof(bool), true);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("LogicInputBlock.h"));
#endif
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ALogicInputBlock_NoRegister()
	{
		return ALogicInputBlock::StaticClass();
	}
	UClass* Z_Construct_UClass_ALogicInputBlock()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_AActor();
			Z_Construct_UPackage__Script_LogicBlocks();
			OuterClass = ALogicInputBlock::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= 0x20900080;

				OuterClass->LinkChild(Z_Construct_UFunction_ALogicInputBlock_CheckInput());

PRAGMA_DISABLE_DEPRECATION_WARNINGS
				UProperty* NewProp_m_param2 = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("m_param2"), RF_Public|RF_Transient|RF_MarkAsNative) UFloatProperty(CPP_PROPERTY_BASE(m_param2, ALogicInputBlock), 0x0010000000000001);
				UProperty* NewProp_m_param1 = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("m_param1"), RF_Public|RF_Transient|RF_MarkAsNative) UFloatProperty(CPP_PROPERTY_BASE(m_param1, ALogicInputBlock), 0x0010000000000001);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_ALogicInputBlock_CheckInput(), "CheckInput"); // 362206358
				static TCppClassTypeInfo<TCppClassTypeTraits<ALogicInputBlock> > StaticCppClassTypeInfo;
				OuterClass->SetCppTypeInfo(&StaticCppClassTypeInfo);
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("LogicInputBlock.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("LogicInputBlock.h"));
				MetaData->SetValue(NewProp_m_param2, TEXT("Category"), TEXT("Logic"));
				MetaData->SetValue(NewProp_m_param2, TEXT("ModuleRelativePath"), TEXT("LogicInputBlock.h"));
				MetaData->SetValue(NewProp_m_param1, TEXT("Category"), TEXT("Logic"));
				MetaData->SetValue(NewProp_m_param1, TEXT("ModuleRelativePath"), TEXT("LogicInputBlock.h"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	IMPLEMENT_CLASS(ALogicInputBlock, 1427518206);
	static FCompiledInDefer Z_CompiledInDefer_UClass_ALogicInputBlock(Z_Construct_UClass_ALogicInputBlock, &ALogicInputBlock::StaticClass, TEXT("/Script/LogicBlocks"), TEXT("ALogicInputBlock"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ALogicInputBlock);
	static FName NAME_ALogicOutputBlock_ValidityStart = FName(TEXT("ValidityStart"));
	void ALogicOutputBlock::ValidityStart()
	{
		ProcessEvent(FindFunctionChecked(NAME_ALogicOutputBlock_ValidityStart),NULL);
	}
	static FName NAME_ALogicOutputBlock_ValidityStop = FName(TEXT("ValidityStop"));
	void ALogicOutputBlock::ValidityStop()
	{
		ProcessEvent(FindFunctionChecked(NAME_ALogicOutputBlock_ValidityStop),NULL);
	}
	static FName NAME_ALogicOutputBlock_ValidityTick = FName(TEXT("ValidityTick"));
	void ALogicOutputBlock::ValidityTick(float DeltaTime)
	{
		LogicOutputBlock_eventValidityTick_Parms Parms;
		Parms.DeltaTime=DeltaTime;
		ProcessEvent(FindFunctionChecked(NAME_ALogicOutputBlock_ValidityTick),&Parms);
	}
	void ALogicOutputBlock::StaticRegisterNativesALogicOutputBlock()
	{
	}
	UFunction* Z_Construct_UFunction_ALogicOutputBlock_ValidityStart()
	{
		UObject* Outer=Z_Construct_UClass_ALogicOutputBlock();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("ValidityStart"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x08020800, 65535);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("LogicOutputBlock.h"));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_ALogicOutputBlock_ValidityStop()
	{
		UObject* Outer=Z_Construct_UClass_ALogicOutputBlock();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("ValidityStop"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x08020800, 65535);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("LogicOutputBlock.h"));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_ALogicOutputBlock_ValidityTick()
	{
		UObject* Outer=Z_Construct_UClass_ALogicOutputBlock();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("ValidityTick"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x08020800, 65535, sizeof(LogicOutputBlock_eventValidityTick_Parms));
			UProperty* NewProp_DeltaTime = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("DeltaTime"), RF_Public|RF_Transient|RF_MarkAsNative) UFloatProperty(CPP_PROPERTY_BASE(DeltaTime, LogicOutputBlock_eventValidityTick_Parms), 0x0010000000000080);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("LogicOutputBlock.h"));
#endif
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ALogicOutputBlock_NoRegister()
	{
		return ALogicOutputBlock::StaticClass();
	}
	UClass* Z_Construct_UClass_ALogicOutputBlock()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_AActor();
			Z_Construct_UPackage__Script_LogicBlocks();
			OuterClass = ALogicOutputBlock::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= 0x20900080;

				OuterClass->LinkChild(Z_Construct_UFunction_ALogicOutputBlock_ValidityStart());
				OuterClass->LinkChild(Z_Construct_UFunction_ALogicOutputBlock_ValidityStop());
				OuterClass->LinkChild(Z_Construct_UFunction_ALogicOutputBlock_ValidityTick());

PRAGMA_DISABLE_DEPRECATION_WARNINGS
				UProperty* NewProp_m_param2 = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("m_param2"), RF_Public|RF_Transient|RF_MarkAsNative) UFloatProperty(CPP_PROPERTY_BASE(m_param2, ALogicOutputBlock), 0x0010000000000001);
				UProperty* NewProp_m_param1 = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("m_param1"), RF_Public|RF_Transient|RF_MarkAsNative) UFloatProperty(CPP_PROPERTY_BASE(m_param1, ALogicOutputBlock), 0x0010000000000001);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_ALogicOutputBlock_ValidityStart(), "ValidityStart"); // 2877346480
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_ALogicOutputBlock_ValidityStop(), "ValidityStop"); // 2868973816
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_ALogicOutputBlock_ValidityTick(), "ValidityTick"); // 139117416
				static TCppClassTypeInfo<TCppClassTypeTraits<ALogicOutputBlock> > StaticCppClassTypeInfo;
				OuterClass->SetCppTypeInfo(&StaticCppClassTypeInfo);
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("LogicOutputBlock.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("LogicOutputBlock.h"));
				MetaData->SetValue(NewProp_m_param2, TEXT("Category"), TEXT("LogicOutputBlock"));
				MetaData->SetValue(NewProp_m_param2, TEXT("ModuleRelativePath"), TEXT("LogicOutputBlock.h"));
				MetaData->SetValue(NewProp_m_param1, TEXT("Category"), TEXT("LogicOutputBlock"));
				MetaData->SetValue(NewProp_m_param1, TEXT("ModuleRelativePath"), TEXT("LogicOutputBlock.h"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	IMPLEMENT_CLASS(ALogicOutputBlock, 914170838);
	static FCompiledInDefer Z_CompiledInDefer_UClass_ALogicOutputBlock(Z_Construct_UClass_ALogicOutputBlock, &ALogicOutputBlock::StaticClass, TEXT("/Script/LogicBlocks"), TEXT("ALogicOutputBlock"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ALogicOutputBlock);
	UPackage* Z_Construct_UPackage__Script_LogicBlocks()
	{
		static UPackage* ReturnPackage = nullptr;
		if (!ReturnPackage)
		{
			ReturnPackage = CastChecked<UPackage>(StaticFindObjectFast(UPackage::StaticClass(), nullptr, FName(TEXT("/Script/LogicBlocks")), false, false));
			ReturnPackage->SetPackageFlags(PKG_CompiledIn | 0x00000000);
			FGuid Guid;
			Guid.A = 0xA04EFF13;
			Guid.B = 0x873269E9;
			Guid.C = 0x00000000;
			Guid.D = 0x00000000;
			ReturnPackage->SetGuid(Guid);

		}
		return ReturnPackage;
	}
#endif
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
PRAGMA_ENABLE_OPTIMIZATION
