// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	void AddTextBoxAtContainer(const FText& InText, const FString& GroupName) const;
	UFUNCTION()
	void UpdateTextBoxAtContainer(const FString& InString, const FText& Value) const;

private:
	// 텍스트 박스를 추가할 컨테이너 위젯
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UHorizontalBox> ScoreBox;

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
};
