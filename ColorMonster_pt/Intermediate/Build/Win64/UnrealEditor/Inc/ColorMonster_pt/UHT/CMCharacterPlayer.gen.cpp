// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Character/CMCharacterPlayer.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCMCharacterPlayer() {}
// Cross Module References
	COLORMONSTER_PT_API UClass* Z_Construct_UClass_ACMCharacterBase();
	COLORMONSTER_PT_API UClass* Z_Construct_UClass_ACMCharacterPlayer();
	COLORMONSTER_PT_API UClass* Z_Construct_UClass_ACMCharacterPlayer_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
	UPackage* Z_Construct_UPackage__Script_ColorMonster_pt();
// End Cross Module References
	void ACMCharacterPlayer::StaticRegisterNativesACMCharacterPlayer()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ACMCharacterPlayer);
	UClass* Z_Construct_UClass_ACMCharacterPlayer_NoRegister()
	{
		return ACMCharacterPlayer::StaticClass();
	}
	struct Z_Construct_UClass_ACMCharacterPlayer_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FirstPersonCameraComponent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_FirstPersonCameraComponent;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ACMCharacterPlayer_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACMCharacterBase,
		(UObject* (*)())Z_Construct_UPackage__Script_ColorMonster_pt,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACMCharacterPlayer_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACMCharacterPlayer_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Character/CMCharacterPlayer.h" },
		{ "ModuleRelativePath", "Character/CMCharacterPlayer.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACMCharacterPlayer_Statics::NewProp_FirstPersonCameraComponent_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** First person camera */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Character/CMCharacterPlayer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "First person camera" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACMCharacterPlayer_Statics::NewProp_FirstPersonCameraComponent = { "FirstPersonCameraComponent", nullptr, (EPropertyFlags)0x00200800000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACMCharacterPlayer, FirstPersonCameraComponent), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ACMCharacterPlayer_Statics::NewProp_FirstPersonCameraComponent_MetaData), Z_Construct_UClass_ACMCharacterPlayer_Statics::NewProp_FirstPersonCameraComponent_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ACMCharacterPlayer_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACMCharacterPlayer_Statics::NewProp_FirstPersonCameraComponent,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ACMCharacterPlayer_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACMCharacterPlayer>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ACMCharacterPlayer_Statics::ClassParams = {
		&ACMCharacterPlayer::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ACMCharacterPlayer_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ACMCharacterPlayer_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ACMCharacterPlayer_Statics::Class_MetaDataParams), Z_Construct_UClass_ACMCharacterPlayer_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACMCharacterPlayer_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_ACMCharacterPlayer()
	{
		if (!Z_Registration_Info_UClass_ACMCharacterPlayer.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACMCharacterPlayer.OuterSingleton, Z_Construct_UClass_ACMCharacterPlayer_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ACMCharacterPlayer.OuterSingleton;
	}
	template<> COLORMONSTER_PT_API UClass* StaticClass<ACMCharacterPlayer>()
	{
		return ACMCharacterPlayer::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ACMCharacterPlayer);
	ACMCharacterPlayer::~ACMCharacterPlayer() {}
	struct Z_CompiledInDeferFile_FID_Users_UNSEEN_Documents_Minju_ColorMonster_pt_Source_ColorMonster_pt_Character_CMCharacterPlayer_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_UNSEEN_Documents_Minju_ColorMonster_pt_Source_ColorMonster_pt_Character_CMCharacterPlayer_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ACMCharacterPlayer, ACMCharacterPlayer::StaticClass, TEXT("ACMCharacterPlayer"), &Z_Registration_Info_UClass_ACMCharacterPlayer, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACMCharacterPlayer), 3077917317U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_UNSEEN_Documents_Minju_ColorMonster_pt_Source_ColorMonster_pt_Character_CMCharacterPlayer_h_3816813858(TEXT("/Script/ColorMonster_pt"),
		Z_CompiledInDeferFile_FID_Users_UNSEEN_Documents_Minju_ColorMonster_pt_Source_ColorMonster_pt_Character_CMCharacterPlayer_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_UNSEEN_Documents_Minju_ColorMonster_pt_Source_ColorMonster_pt_Character_CMCharacterPlayer_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
