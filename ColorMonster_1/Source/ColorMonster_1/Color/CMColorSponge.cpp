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
	
	// Static Mesh (고정된 매터리얼 존재)
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshRef(TEXT("/Game/Mesh/Cube1.Cube1"));
	if (StaticMeshRef.Object)
	{
		StaticMesh->SetStaticMesh(StaticMeshRef.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ColorSponge: Failed to Load Static Mesh Ref"));
	}
	// Need BoxCollision Component
	
	CurrentColor = CM_COLOR_RED;
}

// Called when the game starts or when spawned
void ACMColorSponge::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh->CreateAndSetMaterialInstanceDynamic(0);
	ChangeColor(CurrentColor);
}

// Called every frame
void ACMColorSponge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACMColorSponge::ChangeColor(const FGameplayTag& InColor)
{
	UMaterialInterface* StaticMeshMaterial = StaticMesh->GetMaterial(0);
	UMaterialInstanceDynamic* DynamicMaterial = 
		Cast<UMaterialInstanceDynamic>(StaticMeshMaterial);
	
	if(DynamicMaterial)
	{
		DynamicMaterial->SetVectorParameterValue(FName("Tint"), ACMMonster::TranslateColor(InColor));
	}
}

