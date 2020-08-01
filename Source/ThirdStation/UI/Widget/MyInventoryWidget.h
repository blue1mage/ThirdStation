// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Texture2D.h"
#include "Runtime/UMG/Public/UMG.h"
#include "MyInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class THIRDSTATION_API UMyInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
    
public:
    UMyInventoryWidget(const FObjectInitializer& ObjectInitializer);
       
    virtual void NativeConstruct() override;

    void UpdateInventoryText(FText InventoryName);

    void ClearInventoryText();
    
    void UpdateInventoryImage(UTexture2D* InventoryTexture, bool bMatchSize);

    // void ClearInventoryImage();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UTextBlock* InventoryTextBlock;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UImage* InventoryImage;
	
};
