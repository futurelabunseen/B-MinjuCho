// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CMUserWidget.h"

#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Game/CMGameMode.h"
#include "Game/CMGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Player/CMPlayerController.h"
#include "CMSharedDefinition.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"


UCMUserWidget::UCMUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UCMUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ScoreBox = Cast<UVerticalBox>(GetWidgetFromName(TEXT("ScoreBox")));
	ensure(ScoreBox);

	BindToGameState();
	BindButtonClicked();
}

void UCMUserWidget::UpdateScore(const FText& Monster, const FText& Color, const FText& Number)
{
	FString WidgetMonsterKey = TEXT("Score_") + Monster.ToString();
	UTextBlock* ExistMonsterTextBlock = Cast<UTextBlock>(GetWidgetFromName(FName(WidgetMonsterKey)));
	if(ExistMonsterTextBlock)
	{
		ExistMonsterTextBlock->SetText(Monster);
		
		// 색이 일치해야만 숫자 업데이트 가능
		FString WidgetColorKey = WidgetMonsterKey + TEXT("_COLOR");
		UTextBlock* ExistColorTextBlock = Cast<UTextBlock>(GetWidgetFromName(FName(WidgetColorKey)));
		if(ExistColorTextBlock)
		{
			ExistColorTextBlock->SetText(Color);
			
			FString WidgetNumberKey = WidgetMonsterKey + TEXT("_NUMBER");
			UTextBlock* ExistNumberTextBlock = Cast<UTextBlock>(GetWidgetFromName(FName(WidgetNumberKey)));
			if(ExistNumberTextBlock)
			{
				ExistNumberTextBlock->SetText(Number);
			}
		}
	}
}

void UCMUserWidget::UpdateTime(int32 Minute, int32 Second)
{
	Timer_Minute->SetText(FText::AsNumber(Minute));
	Timer_Second->SetText(FText::AsNumber(Second));
}

void UCMUserWidget::BindToGameState()
{
	// 현재 월드의 GameState 가져오기
	ACMGameState* GameState = Cast<ACMGameState>(UGameplayStatics::GetGameState(this));
	if (GameState)
	{
		// 델리게이트에 함수 바인딩
		GameState->OnScoreChanged.AddDynamic(this, &UCMUserWidget::UpdateScore);
		GameState->OnTimeChanged.AddDynamic(this, &UCMUserWidget::UpdateTime);
		
		GameState->OnWinWindowChanged.AddDynamic(this, &UCMUserWidget::TurnWinWindow);
		GameState->OnLooseWindowChanged.AddDynamic(this, &UCMUserWidget::TurnLooseWindow);

	}
	
}

void UCMUserWidget::BindButtonClicked()
{
	RetryButton_Win->OnClicked.AddDynamic(this, &UCMUserWidget::ClickedRetryBtn);
	RetryButton_Loose->OnClicked.AddDynamic(this, &UCMUserWidget::ClickedRetryBtn);
	StageButton_Win->OnClicked.AddDynamic(this, &UCMUserWidget::ClickedStageBtn);
	StageButton_Loose->OnClicked.AddDynamic(this, &UCMUserWidget::ClickedStageBtn);
	PlayButton->OnClicked.AddDynamic(this, &UCMUserWidget::ClickedPlayBtn);
	StartButton->OnClicked.AddDynamic(this, &UCMUserWidget::ClickedStartBtn);
}

void UCMUserWidget::AddTextBoxAtContainer(const FText& InText, const FString& GroupName) const
{
	if(ScoreBox)
	{
		UTextBlock* NewTextBox = NewObject<UTextBlock>(ScoreBox);
		if(NewTextBox)
		{
			NewTextBox->SetText(InText);
			NewTextBox->SynchronizeProperties();
			ScoreBox->AddChild(NewTextBox);
			NewTextBox->SetCategoryName(GroupName);
		}
	}
}

void UCMUserWidget::UpdateTextBoxAtContainer(const FString& InString, const FText& Value) const
{
	UTextBlock* ExistTextBox = Cast<UTextBlock>(GetWidgetFromName(FName(InString)));
	if(ExistTextBox)
	{
		ExistTextBox->SetText(Value);
	}
}

void UCMUserWidget::TurnWinWindow(bool IsTurnOn)
{
	
	UE_LOG(LogTemp, Warning, TEXT("UCMUserWidget::TurnWinWindow"));
	// 마우스 위치 해제 필요
	ACMPlayerController* PlayerController = Cast<ACMPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if(PlayerController)
	{
		PlayerController->SetPlayerInputMode(false);
	}
	if(IsTurnOn == true)
	{
		Black_Image->SetVisibility(ESlateVisibility::Visible);
		int8 IsVisible = Black_Image->GetVisibility() == ESlateVisibility::Visible ? 1 : 0;
		UE_LOG(LogTemp, Warning, TEXT("Black_Image: %d"), IsVisible);
		WinWindow->SetVisibility(ESlateVisibility::Visible);
		WinImg->SetVisibility(ESlateVisibility::Visible);
		InGameWindow->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		WinWindow->SetVisibility(ESlateVisibility::Hidden);
		WinImg->SetVisibility(ESlateVisibility::Hidden);
		Black_Image->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UCMUserWidget::TurnLooseWindow(bool IsTurnOn)
{
	UE_LOG(LogTemp, Warning, TEXT("UCMUserWidget::TurnWinWindow"));
	// 마우스 위치 해제 필요
	ACMPlayerController* PlayerController = Cast<ACMPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if(PlayerController)
	{
		PlayerController->SetPlayerInputMode(false);
	}
	if(IsTurnOn == true)
	{
		Black_Image->SetVisibility(ESlateVisibility::Visible);
		LooseWindow->SetVisibility(ESlateVisibility::Visible);
		LooseImg->SetVisibility(ESlateVisibility::Visible);
		InGameWindow->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		LooseWindow->SetVisibility(ESlateVisibility::Hidden);
		LooseImg->SetVisibility(ESlateVisibility::Hidden);
		Black_Image->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UCMUserWidget::ClickedRetryBtn()
{
	// 열릴 레벨이 Title UI가 아닌 경우
	// ACMPlayerController* PlayerController = Cast<ACMPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	// if(PlayerController)
	// {
	// 	PlayerController->SetPlayerInputMode(true);
	// }
	ACMGameMode* GameMode = Cast<ACMGameMode>(GetWorld()->GetAuthGameMode());
	if(GameMode)
	{
		GameMode->SetLevelAndLoad(GameMode->GetGameLevel());
		// 레벨 초기화 필요
		WinWindow->SetVisibility(ESlateVisibility::Hidden);
		LooseWindow->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UCMUserWidget::ClickedStageBtn()
{
	StageWindow->SetVisibility(ESlateVisibility::Visible);
	StageImg->SetVisibility(ESlateVisibility::Visible);
	Black_Image->SetVisibility(ESlateVisibility::Visible);
}

void UCMUserWidget::ClickedStartBtn()
{
	TitleBackGroundImg->SetVisibility(ESlateVisibility::Hidden);
	TitleImg->SetVisibility(ESlateVisibility::Hidden);
	StartButton->SetVisibility(ESlateVisibility::Hidden);
	IntroduceImg->SetVisibility(ESlateVisibility::Visible);
	PlayButton->SetVisibility(ESlateVisibility::Visible);
}

void UCMUserWidget::ClickedPlayBtn()
{
	IntroduceImg->SetVisibility(ESlateVisibility::Hidden);
	PlayButton->SetVisibility(ESlateVisibility::Hidden);
	
	// 마우스 위치 해제 필요
	ACMPlayerController* PlayerController = Cast<ACMPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if(PlayerController)
	{
		PlayerController->SetPlayerInputMode(true);
	}
	TitlePanel->SetVisibility(ESlateVisibility::Hidden);
	Black_Image->SetVisibility(ESlateVisibility::Hidden);
	InGameWindow->SetVisibility(ESlateVisibility::Visible);
	// Game START
	ACMGameMode* GameMode = Cast<ACMGameMode>(GetWorld()->GetAuthGameMode());
	if(GameMode)
	{
		GameMode->SetLevelAndLoad(GameMode->GetGameLevel() + 1);
	}
}

void UCMUserWidget::ChangeColorUI(const FGameplayTag& InColor)
{
	FLinearColor RealColor = CMSharedDefinition::TranslateColor(InColor);
	FText TextFromColorTag = CMSharedDefinition::ColorTagToText(InColor);
	LeftGunImg->SetColorAndOpacity(RealColor);
	LeftColorTxt->SetText(TextFromColorTag);
	LeftColorTxt->SetColorAndOpacity(RealColor);
	LeftCurrentNumTxt->SetColorAndOpacity(RealColor);
	LeftTotalNumTxt->SetColorAndOpacity(RealColor);
	LeftSlashTxt->SetColorAndOpacity(RealColor);
}

void UCMUserWidget::ChangeLeftNum(int32 CurrentNum, int32 MaxNum)
{
	LeftCurrentNumTxt->SetText(FText::AsNumber(CurrentNum));
	LeftTotalNumTxt->SetText(FText::AsNumber(MaxNum));
}

void UCMUserWidget::ChangeRightNum(int32 CurrentNum, int32 MaxNum)
{
	RightCurrentNumTxt->SetText(FText::AsNumber(CurrentNum));
	RightTotalNumTxt->SetText(FText::AsNumber(MaxNum));
}

void UCMUserWidget::ConvertGunUI(uint8 InIsLeft)
{
	ESlateVisibility visibleLeft = (InIsLeft == 1) ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	ESlateVisibility visibleRight = (InIsLeft == 0) ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	LeftGunWindow->SetVisibility(visibleLeft);
	RightGunWindow->SetVisibility(visibleRight);
}

