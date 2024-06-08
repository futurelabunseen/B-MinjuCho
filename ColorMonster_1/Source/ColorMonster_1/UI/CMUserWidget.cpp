// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CMUserWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Game/CMGameState.h"
#include "Kismet/GameplayStatics.h"


UCMUserWidget::UCMUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UCMUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ScoreBox = Cast<UHorizontalBox>(GetWidgetFromName(TEXT("ScoreBox")));
	ensure(ScoreBox);

	BindToGameState();

	// 나중에 인터페이스로 구현부 빼기 ??
	// 게임 스테이트는 owning actor가 아니라서 안될 것 같다.
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
	if(IsTurnOn == true)
	{
		WinWindow->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		WinWindow->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UCMUserWidget::TurnLooseWindow(bool IsTurnOn)
{
	if(IsTurnOn == true)
	{
		LooseWindow->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		LooseWindow->SetVisibility(ESlateVisibility::Hidden);
	}
}
