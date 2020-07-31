// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFinalWidget.h"

UMyFinalWidget::UMyFinalWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

}
       
void UMyFinalWidget::NativeConstruct(){
    Super::NativeConstruct();
}

void UMyFinalWidget::SetMessage(FString Present){
    if(FinalTextBlock){
        // UE_LOG(LogTemp, Warning, TEXT("The message is : %s"), *Present);
        FinalTextBlock->SetText(FText::FromString(Present));
    }
    
}