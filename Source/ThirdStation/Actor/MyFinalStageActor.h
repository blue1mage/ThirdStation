// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyFinalStageActor.generated.h"

UCLASS()
class THIRDSTATION_API AMyFinalStageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyFinalStageActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
    void initFunction(FString FinalName, FString FinalMessage);
    
    bool IsCorrectItem(FString Check);

	UFUNCTION(BlueprintCallable)
	bool IsDone();

	FString GetMessage();


    
private:
    FString Correct;
	FString DisplayMessage;
	bool bIsDone;

};
