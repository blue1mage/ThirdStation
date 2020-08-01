// Fill out your copyright notice in the Description page of Project Settings.


#include "MyItemWidget.h"

UMyItemWidget::UMyItemWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    
}

void UMyItemWidget::NativeConstruct(){
    Super::NativeConstruct();
    
}

void UMyItemWidget::UpdateItemText(FText ItemName){
    
    if(ItemTextBlock){
        
        ItemTextBlock->SetText(ItemName);
        
// //        if(!IsInViewport()){
// //            AddToViewport();
// //        }
        
//         //Use code to set visibility of Another Widget
//         if(ItemTextBlock->Visibility == ESlateVisibility::Hidden){
//             ItemTextBlock->SetVisibility(ESlateVisibility::Visible);
//         }
//         //end
        
        
    }
}

void UMyItemWidget::ClearItemText(){
    
//    if(IsInViewport()){
//        RemoveFromViewport();
//    }
    ItemTextBlock->SetText(FText::FromString(FString(TEXT(""))));
    
    
}

