// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Game/CMGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCMGameMode() {}
// Cross Module References
	COLORMONSTER_PT_API UClass* Z_Construct_UClass_ACMGameMode();
	COLORMONSTER_PT_API UClass* Z_Construct_UClass_ACMGameMode_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_ColorMonster_pt();
// End Cross Module References
	void ACMGameMode::StaticRegisterNativesACMGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ACMGameMode);
	UClass* Z_Construct_UClass_ACMGameMode_NoRegister()
	{
		return ACMGameMode::StaticClass();
	}
	struct Z_Construct_UClass_ACMGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ACMGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_ColorMonster_pt,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACMGameMode_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACMGameMode_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "Game/CMGameMode.h" },
		{ "ModuleRelativePath", "Game/CMGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ACMGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACMGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ACMGameMode_Statics::ClassParams = {
		&ACMGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ACMGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ACMGameMode_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_ACMGameMode()
	{
		if (!Z_Registration_Info_UClass_ACMGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACMGameMode.OuterSingleton, Z_Construct_UClass_ACMGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ACMGameMode.OuterSingleton;
	}
	template<> COLORMONSTER_PT_API UClass* StaticClass<ACMGameMode>()
	{
		return ACMGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ACMGameMode);
	ACMGameMode::~ACMGameMode() {}
	struct Z_CompiledInDeferFile_FID_Users_UNSEEN_Documents_Minju_ColorMonster_pt_Source_ColorMonster_pt_Game_CMGameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_UNSEEN_Documents_Minju_ColorMonster_pt_Source_ColorMonster_pt_Game_CMGameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ACMGameMode, ACMGameMode::StaticClass, TEXT("ACMGameMode"), &Z_Registration_Info_UClass_ACMGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACMGameMode), 1032394259U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_UNSEEN_Documents_Minju_ColorMonster_pt_Source_ColorMonster_pt_Game_CMGameMode_h_1302458319(TEXT("/Script/ColorMonster_pt"),
		Z_CompiledInDeferFile_FID_Users_UNSEEN_Documents_Minju_ColorMonster_pt_Source_ColorMonster_pt_Game_CMGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_UNSEEN_Documents_Minju_ColorMonster_pt_Source_ColorMonster_pt_Game_CMGameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
