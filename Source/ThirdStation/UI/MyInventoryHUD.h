// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "Components/WidgetComponent.h"
#include "Widget/MyItemWidget.h"
#include "Widget/MyInventoryWidget.h"
#include "Widget/MyMaterialViewWidget.h"
#include "Widget/MyMaterialWidget.h"
#include "Widget/MyConfirmWidget.h"
#include "Widget/MyFinalWidget.h"

#include "Containers/Array.h"
#include "Engine/Texture2D.h"

#include "MyInventoryHUD.generated.h"


// USTRUCT()
// struct FMaterialViewArray
// {
//     GENERATED_BODY()
// public:    
//     TArray<UMyMaterialView*> MaterialViewArray;
// };


/**
 * 
 */
UCLASS()
class THIRDSTATION_API AMyInventoryHUD : public AHUD
{
	GENERATED_BODY()
public:
    AMyInventoryHUD();
    
    virtual void DrawHUD() override;

    virtual void BeginPlay() override;

    //Item 
    UFUNCTION()
    void UpdateItemText(FString ItemName);

    UFUNCTION()
    void ClearItemText();

    //MaterialView
    //get the MV
    UFUNCTION()
    void UpdateMaterialView(FString MappingName, int8 InventoryType);

    UFUNCTION()
    void ClearMaterialView();

    //move widget
    UFUNCTION()
    void UpdateMaterialViewSelection(bool Upwards);

    //get the string for the material & set hidden
    UFUNCTION()
    FString GetMaterial();

    UFUNCTION()
    void ResetMaterialView();

    UFUNCTION()
    void makeMaterialViewMap();

    // //Helper for MakeWidgetArray
    // UFUNCTION()
    // void initilizeTexture();
    //Helper for initMaterialView
    UFUNCTION()
    TArray<UMyMaterialWidget*> MakeWidgetArray(TArray<FString> ValueArr);
    
    UFUNCTION()
    void initMaterialView(FString Key, TArray<FString> ValueArr);

    //ConfirmWidget
    UFUNCTION()
    void UpdateConfirmWidget();

    UFUNCTION()
    void ShowConfirmWidget();

    UFUNCTION()
    bool ClearConfirmWidget();

    //FinalWidget
    UFUNCTION()
    void UpdateFinalWidget(int8 InventoryType, bool IsCorrect, FString PersonalMessage);

    UFUNCTION()
    void ClearFinalWidget();

    //update bools
    //Check final actor bool
    UFUNCTION()
    void SetIsDone(FString Item);

    UFUNCTION(BlueprintCallable)
	bool CheckIsDone();

    //Inventory
    UFUNCTION()
    void UpdateInventory(FText ItemName);

    UFUNCTION()
    void ClearInventory();

    // //Textures
    // UFUNCTION()
    // UTexture2D* LoadTextureFromPath(const FString& Path);



    
    UPROPERTY(EditDefaultsOnly, Category = "Widgets")
    TSubclassOf<UUserWidget> ItemWidgetClass;
    
    UPROPERTY(EditDefaultsOnly, Category = "Widgets")
    TSubclassOf<UUserWidget> InventoryWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "Widgets")
    TSubclassOf<UUserWidget> MaterialWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "Widgets")
    TSubclassOf<UUserWidget> MaterialViewWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "Widgets")
    TSubclassOf<UUserWidget> ConfirmWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "Widgets")
    TSubclassOf<UUserWidget> FinalWidgetClass;

    /**Map to index*/
    UPROPERTY(EditAnywhere)
    TMap<FString, UTexture2D*> MyTextureMap;
        
    
private:
    UPROPERTY()
    class UMyItemWidget* ItemWidget;
    
    UPROPERTY()
    class UMyInventoryWidget* InventoryWidget;

    UPROPERTY()
    class UMyConfirmWidget* ConfirmWidget;
    
    UPROPERTY()
    class UMyFinalWidget* FinalWidget;

    /**Map to index*/
    UPROPERTY()
    TMap<FString, UMyMaterialViewWidget*> MyMaterialMap;

    UPROPERTY()
    class UMyMaterialViewWidget* CurrentMaterialView;

    int8 MVIndex;

    UPROPERTY()
    UTexture2D* TestTexture;

    bool bGold;
    bool bMyrrh;
    bool bFrankincense;



};
