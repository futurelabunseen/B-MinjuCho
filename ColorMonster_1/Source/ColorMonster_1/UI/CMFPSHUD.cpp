// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CMFPSHUD.h"

#include "CMUserWidget.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "Player/CMPlayer.h"
#include "Weapon/CMColorGun.h"
#include "Weapon/CMLineGun.h"

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
	
	static ConstructorHelpers::FClassFinder<UCMUserWidget> CMWidgetRef(TEXT("/Game/Blueprint/UI/WBP_CM.WBP_CM_C"));
	if (CMWidgetRef.Class)
	{
		CMWidgetClass = CMWidgetRef.Class;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load CMUserWidgetClass"));
	}
}

void ACMFPSHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if(CMWidgetClass)
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), CMWidgetClass);
		if(Widget)
		{
			Widget->AddToViewport();
			CMWidget = Cast<UCMUserWidget>(Widget);
		}
	}

	// 현재 HUD 소유 Pawn 가져오기
	ACMPlayer* Player = Cast<ACMPlayer>(GetOwningPawn());
	if(Player)
	{
		Player->OnSetGun.AddDynamic(this, &ACMFPSHUD::BindPlayerDelagate);
		if(CMWidget)
		{
			CMWidget->SetPlayerMaxHP(Player->GetMaxHP());
			Player->OnHpChanged.AddDynamic(CMWidget, &UCMUserWidget::UpdatePlayerHpBar);
		}
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

void ACMFPSHUD::BindPlayerDelagate()
{
	// 현재 HUD 소유 Pawn 가져오기
	ACMPlayer* Player = Cast<ACMPlayer>(GetOwningPawn());
	if (Player && CMWidget)
	{
		// 델리게이트에 함수 바인딩
		if(Player->GetLeftGun())
		{
			Player->GetLeftGun()->OnColorChanged.AddDynamic(CMWidget, &UCMUserWidget::ChangeColorUI);
			Player->GetLeftGun()->OnBulletChanged.AddDynamic(CMWidget, &UCMUserWidget::ChangeLeftNum);
		}

		if(Player->GetRightGun())
		{
			Player->GetRightGun()->OnBulletChanged.AddDynamic(CMWidget, &UCMUserWidget::ChangeRightNum);
		}
		
		Player->OnConvertedGun.AddDynamic(CMWidget, &UCMUserWidget::ConvertGunUI);
	}
}
