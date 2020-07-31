// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInventoryHUD.h"

AMyInventoryHUD::AMyInventoryHUD(){
    
}

void AMyInventoryHUD::DrawHUD(){
    Super::DrawHUD();
}

void AMyInventoryHUD::BeginPlay(){
    Super::BeginPlay();
    
    if(ItemWidgetClass){
        ItemWidget = CreateWidget<UMyItemWidget>(GetWorld(), ItemWidgetClass);
        ItemWidget->AddToViewport();
        ItemWidget->SetVisibility(ESlateVisibility::Hidden);
        
    }
    
    if(InventoryWidgetClass){
        InventoryWidget = CreateWidget<UMyInventoryWidget>(GetWorld(), InventoryWidgetClass);
        InventoryWidget->AddToViewport();
    }

    if(ConfirmWidgetClass){
        ConfirmWidget = CreateWidget<UMyConfirmWidget>(GetWorld(), ConfirmWidgetClass);
        ConfirmWidget->AddToViewport();
        ConfirmWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if(FinalWidgetClass){
        FinalWidget = CreateWidget<UMyFinalWidget>(GetWorld(), FinalWidgetClass);
        FinalWidget->AddToViewport();
        FinalWidget->SetVisibility(ESlateVisibility::Hidden);
    }


    TArray<FString> shovel;
        shovel.Add(FString(TEXT("mustard seeds")));
        shovel.Add(FString(TEXT("wheat seeds")));
        shovel.Add(FString(TEXT("olive seeds")));

        TArray<FString> incense;
        incense.Add(FString(TEXT("frankincense")));
        incense.Add(FString(TEXT("stacte")));
        incense.Add(FString(TEXT("cinnimon bark")));
        incense.Add(FString(TEXT("saffron")));


        TArray<FString> staff;
        staff.Add(FString(TEXT("wool")));
        staff.Add(FString(TEXT("meat")));
        staff.Add(FString(TEXT("milk")));

        TArray<FString> vial;
        vial.Add(FString(TEXT("spikenard")));

        TArray<FString> cloth;
        cloth.Add(FString(TEXT("myrrh")));
        cloth.Add(FString(TEXT("aloe")));

        TArray<FString> mold;
        mold.Add(FString(TEXT("copper")));
        mold.Add(FString(TEXT("silver")));
        mold.Add(FString(TEXT("gold")));

    //     initMap(FString(TEXT("1")), One, false);
    //     initMap(FString(TEXT("2")), Two, false);
    //     initMap(FString(TEXT("3")), Three, false);
        initMaterialView(FString(TEXT("shovel")), shovel);
        initMaterialView(FString(TEXT("incense dispenser")), incense);
        initMaterialView(FString(TEXT("shepard's staff")), staff);
        initMaterialView(FString(TEXT("perfume vial")), vial);
        initMaterialView(FString(TEXT("coin mold")), mold);
        initMaterialView(FString(TEXT("burial cloth")), cloth);
        UE_LOG(LogTemp, Warning, TEXT("beginplay"));
    
}

/////////////////////////////////////////////////
//ITEMWIDGET
void AMyInventoryHUD::UpdateItemText(FString ItemName){
    
//    if(ItemWidget && !(ItemWidget->IsInViewport())){
//        ItemWidget->AddToViewport();
//    }
//
//    if(ItemWidget){
//        ItemWidget->UpdateItemText(ItemName);
//    }
    if(ItemWidget){
        ItemWidget->UpdateItemText(FText::FromString(ItemName));
        
         if(ItemWidget->Visibility == ESlateVisibility::Hidden){
             ItemWidget->SetVisibility(ESlateVisibility::Visible);
         }
    }
}

void AMyInventoryHUD::ClearItemText(){
    if(ItemWidget){
        ItemWidget->ClearItemText();
        
        if(ItemWidget->Visibility == ESlateVisibility::Visible){
         ItemWidget->SetVisibility(ESlateVisibility::Hidden);
        }
    }
    
    
}

/////////////////////////////////////////////////
//MATERIALVIEW WIDGET
void AMyInventoryHUD::UpdateMaterialView(FString MappingName){
    UE_LOG(LogTemp, Warning, TEXT("start"));
    //null check
    if(!MyMaterialMap.Find(MappingName)) return;

    UMyMaterialViewWidget* MW = *MyMaterialMap.Find(MappingName);
    if(MW != nullptr){
        UE_LOG(LogTemp, Warning, TEXT("in if"));
        if(MW->Visibility == ESlateVisibility::Hidden){
            UE_LOG(LogTemp, Warning, TEXT("visibility"));
            MW->SetVisibility(ESlateVisibility::Visible);
        }
        MVIndex=0;
        if(MW->MaterialWidgetArray.IsValidIndex(MVIndex)){
            UE_LOG(LogTemp, Warning, TEXT("index"));
            CurrentMaterialView = MW;
            MW->MaterialWidgetArray[MVIndex]->setSelected(true);
        }

    }
    UE_LOG(LogTemp, Warning, TEXT("end"));
    // if(MaterialViewWidget){
    //     MaterialViewWidget->AddChildren(MappingName);

    //     if(MaterialViewWidget->Visibility == ESlateVisibility::Hidden){
    //      MaterialViewWidget->SetVisibility(ESlateVisibility::Visible);
    //     }
    // }

}

void AMyInventoryHUD::ClearMaterialView(){
    if(CurrentMaterialView){
        if(CurrentMaterialView->Visibility == ESlateVisibility::Visible){
         CurrentMaterialView->SetVisibility(ESlateVisibility::Hidden);
        }
        //reset color and index
        TArray<UMyMaterialWidget*>* MWArr = &CurrentMaterialView->MaterialWidgetArray;
        if(MWArr && MWArr->IsValidIndex(MVIndex)){
            (*MWArr)[MVIndex]->setSelected(false);
        }

        
    }
}

void AMyInventoryHUD::UpdateMaterialViewSelection(bool Upwards){
    // MaterialViewWidget->MoveIndexInArray(Upwards);
    if(CurrentMaterialView){ // && CurrentMaterialView->MaterialWidgetArray){
        TArray<UMyMaterialWidget*>* MWArr = &CurrentMaterialView->MaterialWidgetArray;
        if(MWArr && MWArr->IsValidIndex(MVIndex)){
            (*MWArr)[MVIndex]->setSelected(false);
            if(Upwards && MWArr->IsValidIndex(MVIndex+1)){
                MVIndex++;
            }
            else if(!Upwards && MWArr->IsValidIndex(MVIndex-1)){
                MVIndex--;
            }
            (*MWArr)[MVIndex]->setSelected(true);
        }
        
    }
}

FString AMyInventoryHUD::GetMaterial(){
    if(CurrentMaterialView){// && CurrentMaterialView->MaterialWidgetArray){
        TArray<UMyMaterialWidget*>* MWArr = &CurrentMaterialView->MaterialWidgetArray;
        if(MWArr && MWArr->IsValidIndex(MVIndex)){
            return (*MWArr)[MVIndex]->getString();
        }
        
    }
    return FString(TEXT(""));
    
}

void AMyInventoryHUD::ResetMaterialView(){
    // UE_LOG(LogTemp, Warning, TEXT("In reset"));
    // if(CurrentMWArray && CurrentMWArray->IsValidIndex(Index) && CurrentMWArray->Num()>0){
    //     UE_LOG(LogTemp, Warning, TEXT("In if"));
    //     UMyMaterialWidget* MW = (*CurrentMWArray)[Index];
    //     if(MW) {
    //         MW->setSelected(false);
    //     }
    // }
    // UE_LOG(LogTemp, Warning, TEXT("after if"));
    // // Index = 0;

    if(CurrentMaterialView){ // && CurrentMaterialView->MaterialWidgetArray){
        TArray<UMyMaterialWidget*>* MWArr = &CurrentMaterialView->MaterialWidgetArray;
        if(MWArr){
            for(auto&val : *MWArr){
                val->setSelected(false);
            }
        }
    }
    
}

/////////////////////////////////////
//Widget Construction
TArray<UMyMaterialWidget*> AMyInventoryHUD::MakeWidgetArray(TArray<FString> ValueArr){
//    if(!ValueArr) return nullptr;

    TArray<UMyMaterialWidget*> MWArr;
    for (auto& val : ValueArr)
    {
        if(MaterialWidgetClass){
            UMyMaterialWidget* MW = CreateWidget<UMyMaterialWidget>(GetWorld(), MaterialWidgetClass);
            MW->initMaterialText(val);
            if(!MW->IsInViewport()){
                MW->AddToViewport();
            }
            MWArr.Add(MW);
            // MW->SetVisibility(ESlateVisibility::Hidden);
        }
        
    }
    return MWArr;
}

void AMyInventoryHUD::initMaterialView(FString Key, TArray<FString> ValueArr){
    
    // if(!MyMaterialMap.Contains(Key) || (MyMaterialMap.Contains(Key) && Replace)){
    //     //TODO
    //     //ItemWidget = CreateWidget<UMaterialWidget>(GetWorld(), MaterialWidgetClass);
    //     FMaterialWidgetArray FMWArr{};
    //     FMWArr.MaterialViewArray = MakeWidgetArray(ValueArr);
    //     MyMaterialMap.Add(Key, FMWArr);

    
    if(MaterialViewWidgetClass){
        UMyMaterialViewWidget* MaterialViewWidget = CreateWidget<UMyMaterialViewWidget>(GetWorld(), MaterialViewWidgetClass);
        MaterialViewWidget->AddToViewport();
        MaterialViewWidget->AddChildren(MakeWidgetArray(ValueArr));
        MaterialViewWidget->SetVisibility(ESlateVisibility::Hidden);
        MyMaterialMap.Add(Key, MaterialViewWidget);
    }
    
}

// /////////////////////////////////
// //Get From Map
// TArray<UMyMaterialWidget*> AMyInventoryHUD::GetMaterialWidgetArray(FString MappingName){
// //    MaterialWidgetArray MWArr = MyMWMap.find(MappingName.ToString());
//     FMaterialWidgetArray* MWArr = MyMaterialMap.Find(MappingName);
//     if(MWArr){
//         // print("not empty");
        
//         TArray<UMyMaterialWidget*> MaterialWidgetArr = MWArr->MaterialWidgetArray;
//         // for(auto& val: MaterialWidgetarr){
// 		// 	print(val->getString());
// 		// }
//         CurrentMWArray = &MaterialWidgetArr;
//         Index = 0;//just in case
//         if(MaterialWidgetArr.Num()>0) MaterialWidgetArr[Index]->setSelected(true);
//         return MaterialWidgetArr;
//     }
//     else{
//         // print("Empty");
//         TArray<UMyMaterialWidget*> Empty;
//         return Empty;
//     }
    
    
// }

///////////////////////////////////////////
//Indexing

// void AMyInventoryHUD::MoveIndexInArray(bool Upwards){
//     if(CurrentMWArray && CurrentMWArray->IsValidIndex(Index) && CurrentMWArray->Num()>0){
//         (*CurrentMWArray)[Index]->setSelected(false);
//         if(Upwards && CurrentMWArray->IsValidIndex(Index+1)){
//             Index++;
//         }
//         else if(!Upwards && CurrentMWArray->IsValidIndex(Index-1)){
//             Index--;
//         }
//         (*CurrentMWArray)[Index]->setSelected(true);
//     }
// }




// FString AMyInventoryHUD::SelectMaterialWidget(){
//     FString Str = FString(TEXT(""));
//     if(CurrentMWArray && CurrentMWArray->IsValidIndex(Index) && CurrentMWArray->Num()>0){
//         UMyMaterialWidget* MW = (*CurrentMWArray)[Index];
//         if(MW){
//             MW->setChosen();
//             Str = MW->getString();
//             MW->setSelected(false);

//         }
//     }
//     return Str;
// }

/////////////////////////////////////////////////
//CONFIRM WIDGET
void AMyInventoryHUD::UpdateConfirmWidget(){
    if(ConfirmWidget){
        ConfirmWidget->Confirm(ConfirmWidget->IsConfirm());
    }   
}

void AMyInventoryHUD::ShowConfirmWidget(){
    if(ConfirmWidget && ConfirmWidget->Visibility == ESlateVisibility::Hidden){
        ConfirmWidget->Confirm(true);
        ConfirmWidget->SetVisibility(ESlateVisibility::Visible);
    }
}

bool AMyInventoryHUD::ClearConfirmWidget(){
    if(ConfirmWidget) {
        if(ConfirmWidget->Visibility == ESlateVisibility::Visible){
            ConfirmWidget->SetVisibility(ESlateVisibility::Hidden);
            
        }
        return ConfirmWidget->IsConfirm();
    }
    return false;

}



/////////////////////////////////////////////////
//FINAL WIDGET
void AMyInventoryHUD::UpdateFinalWidget(int8 InventoryType, bool IsCorrect, FString PersonalMessage){
    if(FinalWidget){
        switch(InventoryType){
            case -1:
                FinalWidget->SetMessage(TEXT("Hmmm ... You have nothing. Please help me find a present."));
                break;

            case 0:
                FinalWidget->SetMessage(TEXT("I was hoping for some raw materials. Please go to the Trader to find something."));
                break;

            case 1:
                
                if(IsCorrect){
                    UE_LOG(LogTemp, Warning, TEXT("Correct"));
                    FinalWidget->SetMessage(TEXT("YES! This is it! Thank you!"));
                }
                else{
                    UE_LOG(LogTemp, Warning, TEXT("Not correct"));
                    FinalWidget->SetMessage(PersonalMessage);
                }
                break;

            default:
                return;
        }

        if(FinalWidget->Visibility == ESlateVisibility::Hidden){
            FinalWidget->SetVisibility(ESlateVisibility::Visible);
            
        }
    }
}

void AMyInventoryHUD::ClearFinalWidget(){
    if(FinalWidget && FinalWidget->Visibility == ESlateVisibility::Visible){
        FinalWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}


/////////////////////////////////////////////////
//INVENTORY WIDGET
void AMyInventoryHUD::UpdateInventory(FText ItemName){
    if(InventoryWidget){
        InventoryWidget->UpdateInventoryText(ItemName);
        //InventoryWidget->UpdateInventoryImage(getTexture(), true);
    }
}


void AMyInventoryHUD::ClearInventory(){
    if(InventoryWidget){
        InventoryWidget->ClearInventoryText();
        //InventoryWidget->ClearInventoryImage();
    }
    
}
