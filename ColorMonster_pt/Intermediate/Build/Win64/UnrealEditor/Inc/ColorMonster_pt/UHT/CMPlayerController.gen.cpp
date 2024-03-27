// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Player/CMPlayerController.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCMPlayerController() {}
// Cross Module References
	COLORMONSTER_PT_API UClass* Z_Construct_UClass_ACMPlayerController();
	COLORMONSTER_PT_API UClass* Z_Construct_UClass_ACMPlayerController_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_APlayerController();
	UPackage* Z_Construct_UPackage__Script_ColorMonster_pt();
// End Cross Module References
	void ACMPlayerController::StaticRegisterNativesACMPlayerController()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ACMPlayerController);
	UClass* Z_Construct_UClass_ACMPlayerController_NoRegister()
	{
		return ACMPlayerController::StaticClass();
	}
	struct Z_Construct_UClass_ACMPlayerController_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ACMPlayerController_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APlayerController,
		(UObject* (*)())Z_Construct_UPackage__Script_ColorMonster_pt,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACMPlayerController_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACMPlayerController_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "Player/CMPlayerController.h" },
		{ "ModuleRelativePath", "Player/CMPlayerController.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ACMPlayerController_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACMPlayerController>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ACMPlayerController_Statics::ClassParams = {
		&ACMPlayerController::StaticClass,
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
		0x009002A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ACMPlayerController_Statics::Class_MetaDataParams), Z_Construct_UClass_ACMPlayerController_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_ACMPlayerController()
	{
		if (!Z_Registration_Info_UClass_ACMPlayerController.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACMPlayerController.OuterSingleton, Z_Construct_UClass_ACMPlayerController_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ACMPlayerController.OuterSingleton;
	}
	template<> COLORMONSTER_PT_API UClass* StaticClass<ACMPlayerController>()
	{
		return ACMPlayerController::StaticClass();
	}
	ACMPlayerController::ACMPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ACMPlayerController);
	ACMPlayerController::~ACMPlayerController() {}
	struct Z_CompiledInDeferFile_FID_Users_UNSEEN_Documents_Minju_ColorMonster_pt_Source_ColorMonster_pt_Player_CMPlayerController_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_UNSEEN_Documents_Minju_ColorMonster_pt_Source_ColorMonster_pt_Player_CMPlayerController_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ACMPlayerController, ACMPlayerController::StaticClass, TEXT("ACMPlayerController"), &Z_Registration_Info_UClass_ACMPlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACMPlayerController), 1504977473U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_UNSEEN_Documents_Minju_ColorMonster_pt_Source_ColorMonster_pt_Player_CMPlayerController_h_3697509712(TEXT("/Script/ColorMonster_pt"),
		Z_CompiledInDeferFile_FID_Users_UNSEEN_Documents_Minju_ColorMonster_pt_Source_ColorMonster_pt_Player_CMPlayerController_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_UNSEEN_Documents_Minju_ColorMonster_pt_Source_ColorMonster_pt_Player_CMPlayerController_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
