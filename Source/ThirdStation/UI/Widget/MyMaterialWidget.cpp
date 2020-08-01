// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMaterialWidget.h"

UMyMaterialWidget::UMyMaterialWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    
}

void UMyMaterialWidget::NativeConstruct(){
    Super::NativeConstruct();
    
    bIsInitText = false;
    bIsInitImage = false;

    Regular = FLinearColor(0.25f, 0.32f, 0.71f, 0.7f);
    // Select = FLinearColor(0.1f, 0.73f, 0.83f, 0.7f);
    Select = FLinearColor(0.22f, 1.0f, 0.07f, 0.7f);
    Chosen = FLinearColor(0.8f, 0.86f, 0.22f, 0.7f);
    MaterialButton->SetBackgroundColor(Regular);

}


void UMyMaterialWidget::initMaterialText(FString MaterialName){
    if(MaterialTextBlock){
        MaterialTextBlock->SetText(FText::FromString(MaterialName));
        bIsInitText = !bIsInitText; 
        ThisMaterialName = MaterialName;
    }
    
}

FString UMyMaterialWidget::getString(){
    UE_LOG(LogTemp, Warning, TEXT("%s"), *ThisMaterialName);
    return ThisMaterialName;
}
   
void UMyMaterialWidget::initMaterialImage(UTexture2D* MaterialTexture, bool bMatchSize){
    if(!bIsInitImage && MaterialImage && MaterialTexture){
        MaterialImage->SetBrushFromTexture(MaterialTexture, bMatchSize);
        bIsInitText = !bIsInitText; 
    }
    
}


void UMyMaterialWidget::setSelected(bool selected){
    if(MaterialButton){
        if(!selected){
            UE_LOG(LogTemp, Warning, TEXT("true"));
            MaterialButton->SetBackgroundColor(Regular);
        }
        else{
            UE_LOG(LogTemp, Warning, TEXT("true"));
            MaterialButton->SetBackgroundColor(Select);
        }
    }
    
}

// void UMyMaterialWidget::setChosen(){
//     MaterialButton->SetBackgroundColor(Chosen);
// }


