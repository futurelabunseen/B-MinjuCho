// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CMHpBarWidget.h"

#include "Components/ProgressBar.h"
#include "Interface/CMCharacterWidgetInterface.h"

UCMHpBarWidget::UCMHpBarWidget(const FObjectInitializer& ObjectInitializer)
{
	MaxHp = -1.0f;
}

void UCMHpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ICMCharacterWidgetInterface* CharacterWidget = Cast<ICMCharacterWidgetInterface>(OwningActor);
	if(CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}
}

void UCMHpBarWidget::UpdateHpBar(float InCurrentHp)
{
	ensure(MaxHp>0.0f);
	if(HpProgressBar)
	{
		HpProgressBar->SetPercent(InCurrentHp / MaxHp);
	}
}
