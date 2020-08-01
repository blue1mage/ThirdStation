// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Engine/Texture2D.h"
#include "Math/Color.h"
#include "MyMaterialWidget.generated.h"

/**
 * 
 */
UCLASS()
class THIRDSTATION_API UMyMaterialWidget : public UUserWidget
{
	GENERATED_BODY()
    
public:
    UMyMaterialWidget(const FObjectInitializer& ObjectInitializer);
    
    virtual void NativeConstruct() override;
    
    void initMaterialText(FString MaterialName);
    
    UFUNCTION(BlueprintCallable)
    void initMaterialImage(UTexture2D* MaterialTexture, bool bMatchSize);

    void setSelected(bool selected);

    // void setChosen();

    FString getString();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UTextBlock* MaterialTextBlock;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UImage* MaterialImage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UButton* MaterialButton;
    
private:
    bool bIsInitText;
    bool bIsInitImage;

    UPROPERTY()
    FLinearColor Regular;

    UPROPERTY()
    FLinearColor Select;

    UPROPERTY()
    FLinearColor Chosen;

    UPROPERTY()
    FString ThisMaterialName;

};
