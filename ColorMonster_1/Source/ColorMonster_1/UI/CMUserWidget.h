// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h"
#include "CMUserWidget.generated.h"
/**
 * 
 */
UCLASS()
class COLORMONSTER_1_API UCMUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UCMUserWidget(const FObjectInitializer &ObjectInitializer);
	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateScore(const FText& Monster, const FText& Color, const FText& Number);

	UFUNCTION()
	void UpdateTime(int32 Minute, int32 Second);
	
private:
	UFUNCTION()
	void BindToGameState();
	UFUNCTION()
	void BindButtonClicked();
	UFUNCTION()
	void AddTextBoxAtContainer(const FText& InText, const FString& GroupName) const;
	UFUNCTION()
	void UpdateTextBoxAtContainer(const FString& InString, const FText& Value) const;

private:
	// 텍스트 박스를 추가할 컨테이너 위젯
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UOverlay> ScoreBox;

	// Timer Text Block
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Timer_Minute;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Timer_Second;

	// Win / Loose UI
public:
	UFUNCTION()
	void TurnWinWindow(bool IsTurnOn);
	
	UFUNCTION()
	void TurnLooseWindow(bool IsTurnOn);
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> WinWindow;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> LooseWindow;

	// RETRY BTN / SELECT STAGE BTN
public:
	UFUNCTION(BlueprintCallable)
	void ClickedRetryBtn();
	
	UFUNCTION(BlueprintCallable)
	void ClickedNextBtn();

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> RetryButton_Win;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> NextButton_Win;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> RetryButton_Loose;
	
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> StageWindow;

	// TITLE Window
public:	
	UFUNCTION(BlueprintCallable)
	void ClickedStartBtn();
	
	UFUNCTION(BlueprintCallable)
	void ClickedPlayBtn();

private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class USizeBox> Black_Size_Box;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Black_Image;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> TitleBackGroundImg;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> IntroduceImg;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> WinImg;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> LooseImg;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> StageImg;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> TitlePanel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> TitleImg;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UVerticalBox> InGameUI;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> InGameWindow;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> StartButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> QuitButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> PlayButton;

	// Ending
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> EndingImg;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> EndingWindow;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BackButton_Ending;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> StageButton_Ending;
public:
	UFUNCTION()
	void ClickedBackButton();
	
	UFUNCTION()
	void ClickedStageButton();

	// Stage
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> StageBtn1;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> StageBtn2;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> StageBtn3;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> StageBtn4;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> StageBtn5;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> StageButton_Win;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> StageButton_Loose;

public:
	UFUNCTION()
	void ClickedEachStageBtn1();
	UFUNCTION()
	void ClickedEachStageBtn2();
	UFUNCTION()
	void ClickedEachStageBtn3();
	UFUNCTION()
	void ClickedEachStageBtn4();
	UFUNCTION()
	void ClickedEachStageBtn5();

private:
	
	// Gun UI
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> LeftGunImg;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> LeftColorTxt;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> LeftCurrentNumTxt;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> LeftTotalNumTxt;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> LeftSlashTxt;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> RightCurrentNumTxt;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> RightTotalNumTxt;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> LeftGunWindow;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> RightGunWindow;
	
public:
	UFUNCTION()
	void ChangeColorUI(const FGameplayTag& InColor);
	
	UFUNCTION()
	void ChangeLeftNum(int32 CurrentNum, int32 MaxNum);
	
	UFUNCTION()
	void ChangeRightNum(int32 CurrentNum, int32 MaxNum);

	UFUNCTION()
	void ConvertGunUI(uint8 InIsLeft);

	// Player HP UI
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> PlayerHpBar;

	UPROPERTY()
	float PlayerMaxHP;

public:
	UFUNCTION()
	void UpdatePlayerHpBar(float InCurrentHP);

	void SetPlayerMaxHP(float InMaxHP) {PlayerMaxHP = InMaxHP;}
};
