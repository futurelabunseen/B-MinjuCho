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
};
