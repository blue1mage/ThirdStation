// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1,1.5,FColor::Green, text)
#define printFString(text, fstring) if(GEngine) GEngine->AddOnScreenDebugMessage(-1,1.5,FColor::Green, FString::Printf(Text(text), fstring))

#include "MyMaterialViewWidget.h"
#include "Types/SlateEnums.h"

UMyMaterialViewWidget::UMyMaterialViewWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    
}

void UMyMaterialViewWidget::NativeConstruct(){
    Super::NativeConstruct();
    
    //Setup
    if(!IsInViewport()){
        AddToViewport();
    }
}

// /////////////////////////////////////
// //Widget Construction
// TArray<UMyMaterialWidget*> UMyMaterialViewWidget::MakeWidgetArray(TArray<FString> ValueArr){
// //    if(!ValueArr) return nullptr;

//     TArray<UMyMaterialWidget*> MWArr;
//     for (auto& val : ValueArr)
//     {
//         if(MaterialWidgetClass){
//             UMyMaterialWidget* MW = CreateWidget<UMyMaterialWidget>(GetWorld(), MaterialWidgetClass);
//             MW->initMaterialText(val);
//             MWArr.Add(MW);
//             if(!MW->IsInViewport()){
//                 MW->AddToViewport();
//             }
//             // MW->SetVisibility(ESlateVisibility::Hidden);
//         }
        
//     }
//     return MWArr;
// }

// void UMyMaterialViewWidget::initMap(FString Key,  TArray<FString> ValueArr){
    
//     if(!MyMaterialMap.Contains(Key) || (MyMaterialMap.Contains(Key) && Replace)){
//         //TODO
//         //ItemWidget = CreateWidget<UMaterialWidget>(GetWorld(), MaterialWidgetClass);
//         FMaterialWidgetArray FMWArr{};
//         FMWArr.MaterialWidgetArray = MakeWidgetArray(ValueArr);
//         MyMaterialMap.Add(Key, FMWArr);

//     }
    
// }


//////////////////////////////////////////////
//Add Remove Widgets
void UMyMaterialViewWidget::AddChildren(TArray<UMyMaterialWidget*> MWArray){

    // TArray<UMyMaterialWidget*> MWArray = GetMaterialWidgetArray(MappingName);
    MaterialWidgetArray = MWArray;
    for (auto& MW : MWArray)
    {
        MaterialListBox->AddChildToVerticalBox(MW);
    }
    
}

// void UMyMaterialViewWidget::ClearChildren(){
//     MaterialListBox->ClearChildren();
// }

// TArray<UMyMaterialWidget*>* UMyMaterialViewWidget::GetMaterialWidgetArray{
//     return MaterialWidgetArray;
// }
