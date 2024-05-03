// Fill out your copyright notice in the Description page of Project Settings.


#include "Color/CMColorSponge.h"
#include "Color/CMGameplayTag.h"
#include "Character/CMMonster.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACMColorSponge::ACMColorSponge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Static Mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Mesh/Cube.Cube'"));
	if (StaticMeshRef.Object)
	{
		StaticMesh->SetStaticMesh(StaticMeshRef.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ColorSponge: Failed to Load Static Mesh Ref"));
	}
	// Material
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialRef(TEXT("/Script/Engine.Material'/Game/Mesh/BasicShapeMaterial.BasicShapeMaterial'"));
	if (MaterialRef.Object)
	{
		StaticMesh->SetMaterial(0, MaterialRef.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ColorSponge: Failed to Load Material Ref"));
	}
	StaticMesh->CreateDynamicMaterialInstance(0, nullptr);
	// Need BoxCollision Component
	
	CurrentColor = CM_COLOR_RED;
}

// Called when the game starts or when spawned
void ACMColorSponge::BeginPlay()
{
	Super::BeginPlay();
	ChangeColor(CurrentColor);
}

// Called every frame
void ACMColorSponge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACMColorSponge::ChangeColor(const FGameplayTag& InColor)
{
	UMaterialInstanceDynamic* MaterialInstance = Cast<UMaterialInstanceDynamic>(StaticMesh->GetMaterial(0));
	if(MaterialInstance)
	{
		MaterialInstance->SetVectorParameterValue(TEXT("Color"), ACMMonster::TranslateColor(InColor));
	}
	
}

