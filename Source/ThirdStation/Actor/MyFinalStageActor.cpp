// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFinalStageActor.h"

// Sets default values
AMyFinalStageActor::AMyFinalStageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    bIsDone = false;
    Correct = FString(TEXT(""));
    DisplayMessage = FString(TEXT(""));
    bReplicates = true;
    // SetReplicates(true);

}

// AMyFinalStageActor::AMyFinalStageActor( const class FPostConstructInitializeProperties & PCIP ) : Super( PCIP )
// { 
//     bReplicates = true;
//     AMyFinalStageActor();

// }

// Called when the game starts or when spawned
void AMyFinalStageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyFinalStageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    SetActorTickEnabled(false);

}

bool AMyFinalStageActor::IsCorrectItem(const FString& Check){
    // UE_LOG(LogTemp, Warning, TEXT("Check : %s"), *Check);
    // UE_LOG(LogTemp, Warning, TEXT("Correct : %s"), *Correct);
    if(Correct.Equals(Check)){
        bIsDone = true;
        // SetDone();
        // turnToDone();
        // ClientRPCCFunction();
        // ClientFunc();
        return true;
    }
       
    else{
        return false;
    }
}

bool AMyFinalStageActor::IsDone(){
    return bIsDone;
}

// void AMyFinalStageActor::SetDone(){
//     bIsDone = true;
// }

// void AMyFinalStageActor::turnToDone_Implementation(){
//     bIsDone = true;
// }

void AMyFinalStageActor::initFunction(FString FinalName, FString FinalMessage){
    Correct = FinalName;
    DisplayMessage = FinalMessage;
    // UE_LOG(LogTemp, Warning, TEXT("The message is : %s"), *Correct);
    // UE_LOG(LogTemp, Warning, TEXT("The message is : %s"), *DisplayMessage);

}

FString AMyFinalStageActor::GetMessage(){
    return DisplayMessage;
}



// // /// replication
// void AMyFinalStageActor::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const{
//     Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//     DOREPLIFETIME(AMyFinalStageActor, bIsDone);
// }

// bool AMyFinalStageActor::ClientRPCCFunction_Validate()
//  {
//      return true;
//  }

//  void AMyFinalStageActor::ClientRPCCFunction_Implementation()
//  {
//      UE_LOG(LogTemp, Warning, TEXT("client"));
//      bIsDone = true;
//      ClientFunc();
//  }
 
//  void AMyFinalStageActor::ClientFunc_Implementation()
//  {
//      UE_LOG(LogTemp, Warning, TEXT("server"));
//      bIsDone = true;
 
//  }
