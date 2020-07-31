// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "Containers/Array.h"
#include "Containers/Map.h"
#include "MyMaterialWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "MyMaterialViewWidget.generated.h"

/**
 * 
 */
UCLASS()
class THIRDSTATION_API UMyMaterialViewWidget : public UUserWidget
{
	GENERATED_BODY()
    
public:
    UMyMaterialViewWidget(const FObjectInitializer& ObjectInitializer);
       
    virtual void NativeConstruct() override;
    
    void AddChildren(TArray<UMyMaterialWidget*> MWArray);

    // TArray<UMyMaterialWidget*>* GetMaterialWidgetArray(); 

    // //Helper for initMap
    // TArray<UMyMaterialWidget*> MakeWidgetArray(TArray<FString> ValueArr);
    
    // void initMap(FString Key, TArray<FString> ValueArr);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UVerticalBox* MaterialListBox;

    UPROPERTY()
    TArray<UMyMaterialWidget*> MaterialWidgetArray;

private:
    bool bIsVisible;
    
    
    
    
	
};
