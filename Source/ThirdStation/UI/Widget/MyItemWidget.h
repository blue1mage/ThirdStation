// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "MyItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class THIRDSTATION_API UMyItemWidget : public UUserWidget
{
	GENERATED_BODY()
    
public:
    UMyItemWidget(const FObjectInitializer& ObjectInitializer);
    
    virtual void NativeConstruct() override;
    
    void UpdateItemText(FText ItemName);
    
    void ClearItemText();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UTextBlock* ItemTextBlock;
    
    
	
};
