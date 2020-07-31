// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "MyFinalWidget.generated.h"

/**
 * 
 */
UCLASS()
class THIRDSTATION_API UMyFinalWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UMyFinalWidget(const FObjectInitializer& ObjectInitializer);
       
    virtual void NativeConstruct() override;

	void SetMessage(FString Present);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UTextBlock* FinalTextBlock;


	
};
