// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/CMColorDecalEffect.h"

#include "CMSharedDefinition.h"
#include "Components/DecalComponent.h"

ACMColorDecalEffect::ACMColorDecalEffect()
{
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> DecalMaterialRef(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Vefects/Blood_VFX/VFX/Decals/MI_VFX_Blood_Decal_WallSplatter01_Censor.MI_VFX_Blood_Decal_WallSplatter01_Censor'"));
	if(DecalMaterialRef.Object)
	{
		SetDecalMaterial(DecalMaterialRef.Object);
	}
	
}

void ACMColorDecalEffect::BeginPlay()
{
	Super::BeginPlay();
	//GetDecalMaterial()->CreateAndSetMaterialInstanceDynamic(i);

	// 데칼 컴포넌트에 접근
	UDecalComponent* DecalComp = this->FindComponentByClass<UDecalComponent>();
	if (DecalComp)
	{
		// 동적 머티리얼 인스턴스 생성
		UMaterialInstanceDynamic* DynamicMaterialInstance = DecalComp->CreateDynamicMaterialInstance();
	}
	
}

void ACMColorDecalEffect::ChangeColor(const FGameplayTag& InColor)
{
	CurrentColor = InColor;
	const FLinearColor RealColor = CMSharedDefinition::TranslateColor(CurrentColor);

	
	
	// 각 매터리얼에 설정된 Dynamic 가져오기
	UMaterialInterface* SkeletalMeshMaterial = GetDecalMaterial();
	UMaterialInstanceDynamic* DynamicMaterial = 
		Cast<UMaterialInstanceDynamic>(SkeletalMeshMaterial);
	
	if(DynamicMaterial)
	{
		// 현재 컬러로 곱하기
		DynamicMaterial->SetVectorParameterValue(FName("Tint"), RealColor);

		// 전체 Parameter 훑는 방법
		TArray<FMaterialParameterInfo> MaterialParameters;
		TArray<FGuid> Guid;
		DynamicMaterial->GetAllVectorParameterInfo(MaterialParameters, Guid);
		for(FMaterialParameterInfo MaterialParam : MaterialParameters)
		{
			FLinearColor ColorInformation;
			DynamicMaterial->GetVectorParameterValue(MaterialParam, ColorInformation);
			UE_LOG(LogTemp, Warning, TEXT("ACMColorDecalEffect::Set Color as %s"), *ColorInformation.ToString());
	
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ACMColorDecalEffect::Failed to Load DynmaicMaterial"));
	}
}

