// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CMWidgetComponent.h"

#include "CMCharacterWidget.h"


void UCMWidgetComponent::InitWidget()
{
	Super::InitWidget();

	UCMCharacterWidget* CMCharacterWidget = Cast<UCMCharacterWidget>(GetWidget());
	
	if(CMCharacterWidget)
	{
		CMCharacterWidget->SetOwiningActor(GetOwner());
	}
}
