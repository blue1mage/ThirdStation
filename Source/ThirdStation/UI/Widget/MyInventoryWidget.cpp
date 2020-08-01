// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInventoryWidget.h"

UMyInventoryWidget::UMyInventoryWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    
}

void UMyInventoryWidget::NativeConstruct(){
    Super::NativeConstruct();
    
    //Setup
    if(!IsInViewport()){
        AddToViewport();
    }
    
}

void UMyInventoryWidget::UpdateInventoryText(FText InventoryName){
    
    if(InventoryTextBlock){
        
        InventoryTextBlock->SetText(InventoryName);
        
        //Visibility
        if(InventoryTextBlock->Visibility == ESlateVisibility::Hidden){
            InventoryTextBlock->SetVisibility(ESlateVisibility::Visible);
        }
        
    }
}

void UMyInventoryWidget::ClearInventoryText(){
    
//    if(IsInViewport()){
//        RemoveFromViewport();
//    }
    if(InventoryTextBlock){
        InventoryTextBlock->SetText(FText::FromString(FString(TEXT("Empty"))));
    }
    
}


void UMyInventoryWidget::UpdateInventoryImage(UTexture2D* InventoryTexture, bool bMatchSize){
    if(InventoryTexture){
        UE_LOG(LogTemp, Warning, TEXT("there's a texture"));
        InventoryImage->SetBrushFromTexture(InventoryTexture, bMatchSize);
    }
    UE_LOG(LogTemp, Warning, TEXT("no texture"));
    
}

// void UMyInventoryWidget::ClearInventoryImage(){
//     //TODO
// }
