// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectMacros.h"
#include "ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef LOGICBLOCKS_LogicInputBlock_generated_h
#error "LogicInputBlock.generated.h already included, missing '#pragma once' in LogicInputBlock.h"
#endif
#define LOGICBLOCKS_LogicInputBlock_generated_h

#define LogicBlocks_Source_LogicBlocks_LogicInputBlock_h_12_RPC_WRAPPERS
#define LogicBlocks_Source_LogicBlocks_LogicInputBlock_h_12_RPC_WRAPPERS_NO_PURE_DECLS
#define LogicBlocks_Source_LogicBlocks_LogicInputBlock_h_12_EVENT_PARMS \
	struct LogicInputBlock_eventCheckInput_Parms \
	{ \
		bool ReturnValue; \
 \
		/** Constructor, initializes return property only **/ \
		LogicInputBlock_eventCheckInput_Parms() \
			: ReturnValue(false) \
		{ \
		} \
	};


#define LogicBlocks_Source_LogicBlocks_LogicInputBlock_h_12_CALLBACK_WRAPPERS
#define LogicBlocks_Source_LogicBlocks_LogicInputBlock_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesALogicInputBlock(); \
	friend LOGICBLOCKS_API class UClass* Z_Construct_UClass_ALogicInputBlock(); \
public: \
	DECLARE_CLASS(ALogicInputBlock, AActor, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/LogicBlocks"), NO_API) \
	DECLARE_SERIALIZER(ALogicInputBlock) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define LogicBlocks_Source_LogicBlocks_LogicInputBlock_h_12_INCLASS \
private: \
	static void StaticRegisterNativesALogicInputBlock(); \
	friend LOGICBLOCKS_API class UClass* Z_Construct_UClass_ALogicInputBlock(); \
public: \
	DECLARE_CLASS(ALogicInputBlock, AActor, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/LogicBlocks"), NO_API) \
	DECLARE_SERIALIZER(ALogicInputBlock) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define LogicBlocks_Source_LogicBlocks_LogicInputBlock_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ALogicInputBlock(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ALogicInputBlock) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ALogicInputBlock); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ALogicInputBlock); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ALogicInputBlock(ALogicInputBlock&&); \
	NO_API ALogicInputBlock(const ALogicInputBlock&); \
public:


#define LogicBlocks_Source_LogicBlocks_LogicInputBlock_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ALogicInputBlock(ALogicInputBlock&&); \
	NO_API ALogicInputBlock(const ALogicInputBlock&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ALogicInputBlock); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ALogicInputBlock); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ALogicInputBlock)


#define LogicBlocks_Source_LogicBlocks_LogicInputBlock_h_12_PRIVATE_PROPERTY_OFFSET
#define LogicBlocks_Source_LogicBlocks_LogicInputBlock_h_9_PROLOG \
	LogicBlocks_Source_LogicBlocks_LogicInputBlock_h_12_EVENT_PARMS


#define LogicBlocks_Source_LogicBlocks_LogicInputBlock_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	LogicBlocks_Source_LogicBlocks_LogicInputBlock_h_12_PRIVATE_PROPERTY_OFFSET \
	LogicBlocks_Source_LogicBlocks_LogicInputBlock_h_12_RPC_WRAPPERS \
	LogicBlocks_Source_LogicBlocks_LogicInputBlock_h_12_CALLBACK_WRAPPERS \
	LogicBlocks_Source_LogicBlocks_LogicInputBlock_h_12_INCLASS \
	LogicBlocks_Source_LogicBlocks_LogicInputBlock_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define LogicBlocks_Source_LogicBlocks_LogicInputBlock_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	LogicBlocks_Source_LogicBlocks_LogicInputBlock_h_12_PRIVATE_PROPERTY_OFFSET \
	LogicBlocks_Source_LogicBlocks_LogicInputBlock_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	LogicBlocks_Source_LogicBlocks_LogicInputBlock_h_12_CALLBACK_WRAPPERS \
	LogicBlocks_Source_LogicBlocks_LogicInputBlock_h_12_INCLASS_NO_PURE_DECLS \
	LogicBlocks_Source_LogicBlocks_LogicInputBlock_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID LogicBlocks_Source_LogicBlocks_LogicInputBlock_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
