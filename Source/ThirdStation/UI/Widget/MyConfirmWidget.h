// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "MyConfirmWidget.generated.h"

/**
 * 
 */
UCLASS()
class THIRDSTATION_API UMyConfirmWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UMyConfirmWidget(const FObjectInitializer& ObjectInitializer);
    
    virtual void NativeConstruct() override;

	void Reset();

	void Confirm(bool select);

	bool IsConfirm();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UButton* YesButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UButton* NoButton;

private:
	UPROPERTY()
    FLinearColor Regular;

    UPROPERTY()
    FLinearColor Select;

    UPROPERTY()
    FLinearColor Chosen;

	bool bConfirm;

	
};
