// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectMacros.h"
#include "ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
#ifdef LOGICBLOCKS_LogicBlocksComponent_generated_h
#error "LogicBlocksComponent.generated.h already included, missing '#pragma once' in LogicBlocksComponent.h"
#endif
#define LOGICBLOCKS_LogicBlocksComponent_generated_h

#define LogicBlocks_Source_LogicBlocks_LogicBlocksComponent_h_44_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(exec_OnOutputBlockDestroyed) \
	{ \
		P_GET_OBJECT(AActor,Z_Param__destroyedActor); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->_OnOutputBlockDestroyed(Z_Param__destroyedActor); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(exec_OnInputBlockDestroyed) \
	{ \
		P_GET_OBJECT(AActor,Z_Param__destroyedActor); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->_OnInputBlockDestroyed(Z_Param__destroyedActor); \
		P_NATIVE_END; \
	}


#define LogicBlocks_Source_LogicBlocks_LogicBlocksComponent_h_44_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(exec_OnOutputBlockDestroyed) \
	{ \
		P_GET_OBJECT(AActor,Z_Param__destroyedActor); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->_OnOutputBlockDestroyed(Z_Param__destroyedActor); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(exec_OnInputBlockDestroyed) \
	{ \
		P_GET_OBJECT(AActor,Z_Param__destroyedActor); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->_OnInputBlockDestroyed(Z_Param__destroyedActor); \
		P_NATIVE_END; \
	}


#define LogicBlocks_Source_LogicBlocks_LogicBlocksComponent_h_44_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULogicBlocksComponent(); \
	friend LOGICBLOCKS_API class UClass* Z_Construct_UClass_ULogicBlocksComponent(); \
public: \
	DECLARE_CLASS(ULogicBlocksComponent, UActorComponent, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/LogicBlocks"), NO_API) \
	DECLARE_SERIALIZER(ULogicBlocksComponent) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define LogicBlocks_Source_LogicBlocks_LogicBlocksComponent_h_44_INCLASS \
private: \
	static void StaticRegisterNativesULogicBlocksComponent(); \
	friend LOGICBLOCKS_API class UClass* Z_Construct_UClass_ULogicBlocksComponent(); \
public: \
	DECLARE_CLASS(ULogicBlocksComponent, UActorComponent, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/LogicBlocks"), NO_API) \
	DECLARE_SERIALIZER(ULogicBlocksComponent) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define LogicBlocks_Source_LogicBlocks_LogicBlocksComponent_h_44_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULogicBlocksComponent(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULogicBlocksComponent) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULogicBlocksComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULogicBlocksComponent); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULogicBlocksComponent(ULogicBlocksComponent&&); \
	NO_API ULogicBlocksComponent(const ULogicBlocksComponent&); \
public:


#define LogicBlocks_Source_LogicBlocks_LogicBlocksComponent_h_44_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULogicBlocksComponent(ULogicBlocksComponent&&); \
	NO_API ULogicBlocksComponent(const ULogicBlocksComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULogicBlocksComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULogicBlocksComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ULogicBlocksComponent)


#define LogicBlocks_Source_LogicBlocks_LogicBlocksComponent_h_44_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__m_logicInputs() { return STRUCT_OFFSET(ULogicBlocksComponent, m_logicInputs); } \
	FORCEINLINE static uint32 __PPO__m_logicOutputs() { return STRUCT_OFFSET(ULogicBlocksComponent, m_logicOutputs); }


#define LogicBlocks_Source_LogicBlocks_LogicBlocksComponent_h_41_PROLOG
#define LogicBlocks_Source_LogicBlocks_LogicBlocksComponent_h_44_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	LogicBlocks_Source_LogicBlocks_LogicBlocksComponent_h_44_PRIVATE_PROPERTY_OFFSET \
	LogicBlocks_Source_LogicBlocks_LogicBlocksComponent_h_44_RPC_WRAPPERS \
	LogicBlocks_Source_LogicBlocks_LogicBlocksComponent_h_44_INCLASS \
	LogicBlocks_Source_LogicBlocks_LogicBlocksComponent_h_44_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define LogicBlocks_Source_LogicBlocks_LogicBlocksComponent_h_44_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	LogicBlocks_Source_LogicBlocks_LogicBlocksComponent_h_44_PRIVATE_PROPERTY_OFFSET \
	LogicBlocks_Source_LogicBlocks_LogicBlocksComponent_h_44_RPC_WRAPPERS_NO_PURE_DECLS \
	LogicBlocks_Source_LogicBlocks_LogicBlocksComponent_h_44_INCLASS_NO_PURE_DECLS \
	LogicBlocks_Source_LogicBlocks_LogicBlocksComponent_h_44_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID LogicBlocks_Source_LogicBlocks_LogicBlocksComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
