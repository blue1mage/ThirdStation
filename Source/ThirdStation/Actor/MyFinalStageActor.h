// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// #include "UnrealNetwork.h"
// #include "Net/UnrealNetwork.h"
#include "MyFinalStageActor.generated.h"

UCLASS()
class THIRDSTATION_API AMyFinalStageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyFinalStageActor();
	// AMyFinalStageActor( const class FPostConstructInitializeProperties & PCIP );


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
    void initFunction(FString FinalName, FString FinalMessage);
    
    bool IsCorrectItem(const FString& Check);

	UFUNCTION(BlueprintCallable)
	bool IsDone();

	// UFUNCTION(BlueprintCallable)
	// void SetDone();

	// UFUNCTION(BlueprintNativeEvent)
	// void turnToDone();

	// virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

	// UFUNCTION(reliable, Se
	// UFUNCTION(BlueprintCallable)
	// SetDone

	FString GetMessage();

	

    
private:
    FString Correct;
	FString DisplayMessage;

	UPROPERTY()
	bool bIsDone;
};
