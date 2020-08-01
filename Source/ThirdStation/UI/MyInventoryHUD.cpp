// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInventoryHUD.h"

AMyInventoryHUD::AMyInventoryHUD(){
    
}

void AMyInventoryHUD::DrawHUD(){
    Super::DrawHUD();
}

void AMyInventoryHUD::BeginPlay(){
    Super::BeginPlay();

    
    
    //creating widgets
    if(ItemWidgetClass){
        ItemWidget = CreateWidget<UMyItemWidget>(GetWorld(), ItemWidgetClass);
        ItemWidget->AddToViewport();
        ItemWidget->SetVisibility(ESlateVisibility::Hidden);
        
    }
    
    if(InventoryWidgetClass){
        InventoryWidget = CreateWidget<UMyInventoryWidget>(GetWorld(), InventoryWidgetClass);
        // InventoryWidget->UpdateInventoryImage(*MyTextureMap.Find(FString(TEXT("Empty"))), true);
        InventoryWidget->AddToViewport();
        UE_LOG(LogTemp, Warning, TEXT("inventory yay"));
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
    
}

/////////////////////////////////////////////////
//ITEMWIDGET
void AMyInventoryHUD::UpdateItemText(FString ItemName){
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
void AMyInventoryHUD::UpdateMaterialView(FString MappingName, int8 InventoryType){
    UE_LOG(LogTemp, Warning, TEXT("start"));
    //null check
    // MW->SetText(FString(TEXT(")));

    makeMaterialViewMap();



    UMyMaterialViewWidget** FindMW = MyMaterialMap.Find(MappingName);
    // UMyMaterialViewWidget* MW = *FindMW;

    if(!FindMW  && (InventoryType == -1 || InventoryType == 1)) {
        FindMW = MyMaterialMap.Find(FString(TEXT("message no")));
        if(!FindMW){
            return;
        }
    }

    UMyMaterialViewWidget* MW = *FindMW;

    if(MW != nullptr){
        CurrentMaterialView = MW;
        
        UE_LOG(LogTemp, Warning, TEXT("in if"));
        if(CurrentMaterialView->Visibility == ESlateVisibility::Hidden){
            UE_LOG(LogTemp, Warning, TEXT("visibility"));
            CurrentMaterialView->SetVisibility(ESlateVisibility::Visible);
        }
        MVIndex=0;
        if(CurrentMaterialView->MaterialWidgetArray.IsValidIndex(MVIndex)){
            UE_LOG(LogTemp, Warning, TEXT("index"));
            CurrentMaterialView->MaterialWidgetArray[MVIndex]->setSelected(true);
        }
        switch(InventoryType){
            case -1:
                CurrentMaterialView->SetText(FString(TEXT("Looks like your inventory is empty. Please get something to trade in.")));
                break;
            case 0:
                CurrentMaterialView->SetText(FString(TEXT("What do you want trade for ")).Append(MappingName).Append(FString(TEXT("?"))));
                break;
            case 1:
                CurrentMaterialView->SetText(FString(TEXT("Sorry no take backs. Please find something else to trade in.")));
                break;
            default:
                break;
        }
        
    }
    UE_LOG(LogTemp, Warning, TEXT("end"));

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
void AMyInventoryHUD::makeMaterialViewMap(){
    if(MyMaterialMap.Find(FString(TEXT("shovel")))){
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Constructing MAterial View"));

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

    TArray<FString> empty;
    initMaterialView(FString(TEXT("shovel")), shovel);
    initMaterialView(FString(TEXT("incense dispenser")), incense);
    initMaterialView(FString(TEXT("shepard's staff")), staff);
    initMaterialView(FString(TEXT("perfume vial")), vial);
    initMaterialView(FString(TEXT("coin mold")), mold);
    initMaterialView(FString(TEXT("burial cloth")), cloth);

    
    initMaterialView(FString(TEXT("message no")), empty);
    UE_LOG(LogTemp, Warning, TEXT("beginplay"));
}


TArray<UMyMaterialWidget*> AMyInventoryHUD::MakeWidgetArray(TArray<FString> ValueArr){
//    if(!ValueArr) return nullptr;

    TArray<UMyMaterialWidget*> MWArr;
    for (auto& val : ValueArr)
    {
        if(MaterialWidgetClass){
            UMyMaterialWidget* MW = CreateWidget<UMyMaterialWidget>(GetWorld(), MaterialWidgetClass);
            MW->initMaterialText(val);
            UTexture2D** Texture2D = MyTextureMap.Find(val);
            if(Texture2D && *Texture2D){

                MW->initMaterialImage(*Texture2D, true);
            }
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
    
    if(MaterialViewWidgetClass){
        UMyMaterialViewWidget* MaterialViewWidget = CreateWidget<UMyMaterialViewWidget>(GetWorld(), MaterialViewWidgetClass);
        MaterialViewWidget->AddToViewport();
        MaterialViewWidget->AddChildren(MakeWidgetArray(ValueArr));
        MaterialViewWidget->SetVisibility(ESlateVisibility::Hidden);
        MyMaterialMap.Add(Key, MaterialViewWidget);
    }
    
}


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

            case 2: 
                FinalWidget->SetMessage(TEXT("Thanks for the help! I hope Jesus likes this :)"));
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
        UTexture2D** Texture2DPtr = MyTextureMap.Find(ItemName.ToString());
        if(!Texture2DPtr){
            Texture2DPtr = MyTextureMap.Find(FString(TEXT("Empty")));
            if(!Texture2DPtr) return;
        }

        if(Texture2DPtr) InventoryWidget->UpdateInventoryImage(*Texture2DPtr, true);
    }
}


void AMyInventoryHUD::ClearInventory(){
    if(InventoryWidget){
        InventoryWidget->ClearInventoryText();

        UTexture2D** Texture2DPtr = MyTextureMap.Find(FString(TEXT("Empty")));
        if(Texture2DPtr) InventoryWidget->UpdateInventoryImage(*Texture2DPtr, true);
        //InventoryWidget->ClearInventoryImage();
    }
    
}

