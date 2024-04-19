// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CMFPSHUD.h"

#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
ACMFPSHUD::ACMFPSHUD()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTextureRef(TEXT("/Script/Engine.Texture2D'/Game/UI/crosshair.crosshair'"));
	if (CrosshairTextureRef.Object)
	{
		CrosshairTexture = CrosshairTextureRef.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load CrosshairTexture"));
	}
}
void ACMFPSHUD::DrawHUD()
{
	Super::DrawHUD();
	if (CrosshairTexture)
	{
		FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
		FVector2D CrosshairDrawPosition(Center.X - (CrosshairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5f));

		FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTexture->Resource, FLinearColor::White);
		TileItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(TileItem);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NULL CrosshairTexture"));
	}
}
