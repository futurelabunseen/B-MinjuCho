// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Character/CMCharacterBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCMCharacterBase() {}
// Cross Module References
	COLORMONSTER_PT_API UClass* Z_Construct_UClass_ACMCharacterBase();
	COLORMONSTER_PT_API UClass* Z_Construct_UClass_ACMCharacterBase_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	UPackage* Z_Construct_UPackage__Script_ColorMonster_pt();
// End Cross Module References
	void ACMCharacterBase::StaticRegisterNativesACMCharacterBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ACMCharacterBase);
	UClass* Z_Construct_UClass_ACMCharacterBase_NoRegister()
	{
		return ACMCharacterBase::StaticClass();
	}
	struct Z_Construct_UClass_ACMCharacterBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ACMCharacterBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_ColorMonster_pt,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACMCharacterBase_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACMCharacterBase_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Character/CMCharacterBase.h" },
		{ "ModuleRelativePath", "Character/CMCharacterBase.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ACMCharacterBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACMCharacterBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ACMCharacterBase_Statics::ClassParams = {
		&ACMCharacterBase::StaticClass,
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
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ACMCharacterBase_Statics::Class_MetaDataParams), Z_Construct_UClass_ACMCharacterBase_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_ACMCharacterBase()
	{
		if (!Z_Registration_Info_UClass_ACMCharacterBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACMCharacterBase.OuterSingleton, Z_Construct_UClass_ACMCharacterBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ACMCharacterBase.OuterSingleton;
	}
	template<> COLORMONSTER_PT_API UClass* StaticClass<ACMCharacterBase>()
	{
		return ACMCharacterBase::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ACMCharacterBase);
	ACMCharacterBase::~ACMCharacterBase() {}
	struct Z_CompiledInDeferFile_FID_Users_UNSEEN_Documents_Minju_ColorMonster_pt_Source_ColorMonster_pt_Character_CMCharacterBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_UNSEEN_Documents_Minju_ColorMonster_pt_Source_ColorMonster_pt_Character_CMCharacterBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ACMCharacterBase, ACMCharacterBase::StaticClass, TEXT("ACMCharacterBase"), &Z_Registration_Info_UClass_ACMCharacterBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACMCharacterBase), 1200966552U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_UNSEEN_Documents_Minju_ColorMonster_pt_Source_ColorMonster_pt_Character_CMCharacterBase_h_42974360(TEXT("/Script/ColorMonster_pt"),
		Z_CompiledInDeferFile_FID_Users_UNSEEN_Documents_Minju_ColorMonster_pt_Source_ColorMonster_pt_Character_CMCharacterBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_UNSEEN_Documents_Minju_ColorMonster_pt_Source_ColorMonster_pt_Character_CMCharacterBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
