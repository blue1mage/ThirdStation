// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UI/MyInventoryHUD.h"
#include "Actor/MyItemActor.h"
#include "Actor/MyTraderActor.h"
#include "Actor/MyFinalStageActor.h"
#include "ThirdStationCharacter.generated.h"

UCLASS(config=Game)
class AThirdStationCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AThirdStationCharacter();

	/** Returns type of inventory, empty -1, item 0, or material 1*/
    int8 getInventoryType();

	/** Returns inventory string*/
    FString getInventory();
    
    /**Update Item Widget*/
    void updateItemWidget(FString InventoryItem);

	/**Update Material View Widget*/
    void updateMaterialViewWidget();
    
    /**Update Item Overlapping*/
    void updateItemOverlap(FString ItemOverlap);
    
    /**Update Inventory and Type*/
    void updateInventory(int8 InventoryType, FString InventoryObject);
    
    /**Clear Item Widget*/
    void clearItemWidget();

	/**Clear Material View Widget*/
    void clearMaterialViewWidget();
    
    /**Set FString to empty string*/
    void clearInventory();
    
    /**detect overlap begin */
    UFUNCTION()
    void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
    
    /**detect overlapend*/
    UFUNCTION()
    void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);
    
    /**input enter*/
    UFUNCTION()
    void OnEnterPressed();

	/**input a, upwards/left*/
    UFUNCTION()
    void OnZPressed();

	/**input d, downwards/right*/
    UFUNCTION()
    void OnXPressed();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

private:
	UPROPERTY()
	class AActor* ActorOverlapping;

    /**Helper to get the gameHUD*/
    AMyInventoryHUD* getGameHUD();
    
    //UProperty???
    FString CurrInventory;
    FString CurrItemOverlap;
    //-1 = empty
    //0 = item
    //1 = material
    int8 CurrInventoryType;
    //0 = none
    //1 = item
    //2 = trader
    //3 = offering
    int8 CurrOverlapType;

	bool bIsCorrect;
	bool bActorIsDone;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

