// Fill out your copyright notice in the Description page of Project Settings.


#include "MyConfirmWidget.h"

UMyConfirmWidget::UMyConfirmWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    
}

void UMyConfirmWidget::NativeConstruct(){
    Super::NativeConstruct();
    
    bConfirm = false;

    Regular = FLinearColor(0.25f, 0.32f, 0.71f, 0.7f);
    Select = FLinearColor(0.1f, 0.73f, 0.83f, 0.7f);
    Chosen = FLinearColor(0.8f, 0.86f, 0.22f, 0.7f);

}

void UMyConfirmWidget::Reset(){
    bConfirm = false;

    YesButton->SetBackgroundColor(Regular);
    NoButton->SetBackgroundColor(Select);

}

void UMyConfirmWidget::Confirm(bool select){
    if(select){
        YesButton->SetBackgroundColor(Regular);
        NoButton->SetBackgroundColor(Select);
        bConfirm = false;
    }
    else{
        YesButton->SetBackgroundColor(Select);
        NoButton->SetBackgroundColor(Regular);
        bConfirm = true;
    }
}

bool UMyConfirmWidget::IsConfirm(){
    return bConfirm;
}