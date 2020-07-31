// Fill out your copyright notice in the Description page of Project Settings.



#include "MyItemActor.h"

// Sets default values
AMyItemActor::AMyItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    
    bIsInit = false;
    MyItemName = FString(TEXT("Item Box"));

}



// Called when the game starts or when spawned
void AMyItemActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMyItemActor::initFunction(FString ItemName){
    if(!bIsInit){
        MyItemName = ItemName;
        bIsInit = !bIsInit;
    }
}

FString AMyItemActor::getItemName(){
    return MyItemName;
}



