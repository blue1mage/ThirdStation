// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ThirdStationCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// AThirdStationCharacter

AThirdStationCharacter::AThirdStationCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	//collision binding
    OnActorBeginOverlap.AddDynamic(this, &AThirdStationCharacter::OnOverlapBegin);
    OnActorEndOverlap.AddDynamic(this, &AThirdStationCharacter::OnOverlapEnd);
    
    //Setup variables
    CurrInventory = FString(TEXT(""));
    //empty inventory
    CurrInventoryType = -1;
    CurrOverlapType = 0;

	ActorOverlapping = nullptr;

	bIsCorrect = false;
	bActorIsDone = false;
	bServerClient = false;
}


//////////////////////////////////////////////////////////////////////////
// Input

void AThirdStationCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Confirm", IE_Pressed, this, &AThirdStationCharacter::OnEnterPressed);
	PlayerInputComponent->BindAction("Upwards", IE_Pressed, this, &AThirdStationCharacter::OnZPressed);
	PlayerInputComponent->BindAction("Downwards", IE_Pressed, this, &AThirdStationCharacter::OnXPressed);

	PlayerInputComponent->BindAxis("MoveForward", this, &AThirdStationCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AThirdStationCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AThirdStationCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AThirdStationCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AThirdStationCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AThirdStationCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AThirdStationCharacter::OnResetVR);
}


void AThirdStationCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AThirdStationCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AThirdStationCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AThirdStationCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AThirdStationCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AThirdStationCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AThirdStationCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}


//////////////////////////////////////////////////////////////////////////
// Helper Functions

AMyInventoryHUD* AThirdStationCharacter::getGameHUD(){
    return Cast<AMyInventoryHUD>(GetWorld()->
    GetFirstPlayerController()->
    GetHUD());
}

void AThirdStationCharacter::updateInventory(int8 InventoryType, FString InventoryObject){
    
	if(InventoryType != -1 && InventoryType != 0 && InventoryType != 1){
		return;
	}

    if(InventoryType == -1){
        CurrInventory = FString(TEXT("Empty"));
    }
    else{
        CurrInventory = InventoryObject;
    }
	AMyInventoryHUD* MyInventoryHUD = getGameHUD();
	if(MyInventoryHUD){
		MyInventoryHUD->UpdateInventory(FText::FromString(InventoryObject));
	}
    
    CurrInventoryType = InventoryType;
}

//////////////////////////////////////////////////////////////////////////
// Key Input
void AThirdStationCharacter::OnEnterPressed(){
	if(!ActorOverlapping) return;

	AMyInventoryHUD* MyInventoryHUD = getGameHUD();
	if(!MyInventoryHUD) return;


	switch(CurrOverlapType){
		case 1:
			updateInventory(0, CurrItemOverlap);
			// clearItemWidget();
			MyInventoryHUD->ClearItemText();
			break;
		case 2:
			updateInventory(1, MyInventoryHUD->GetMaterial());
			MyInventoryHUD->ClearMaterialView();
			break;
		case 3:
			if(ActorOverlapping){
				AMyFinalStageActor* MyFinalStageActor = Cast<AMyFinalStageActor>(ActorOverlapping);
				if(MyFinalStageActor){
					if(MyInventoryHUD->ClearConfirmWidget() && !MyFinalStageActor->IsDone()){
						// UE_LOG(LogTemp, Warning, TEXT("CurrIn is : %s"), *CurrInventory);
						// MyInventoryHUD->UpdateFinalWidget(CurrInventoryType, MyFinalStageActor->IsCorrectItem(CurrInventory), MyFinalStageActor->GetMessage());
						// if(CurrInventoryType) updateInventory(-1, FString(TEXT("Empty")));



						UE_LOG(LogTemp, Warning, TEXT("check my final is : %s"), *CurrInventory);
						bool haveCorrectItem = MyFinalStageActor->IsCorrectItem(CurrInventory);
						MyInventoryHUD->UpdateFinalWidget(CurrInventoryType, haveCorrectItem, MyFinalStageActor->GetMessage());
						UE_LOG(LogTemp, Warning, TEXT("after is : %s"), *CurrInventory);

						if(haveCorrectItem){
							MyInventoryHUD->SetIsDone(CurrInventory);
							UE_LOG(LogTemp, Warning, TEXT("CurrInventory : %s"), *CurrInventory);
							UpdateMVRPC(CurrInventory, MyFinalStageActor);
							UpdateMVClient(CurrInventory, MyFinalStageActor);
							ShowMatThu();
							bServerClient = true;
						}
						UE_LOG(LogTemp, Warning, TEXT("after if : %s"), *CurrInventory);
						//should be very end
						// if(CurrInventoryType) updateInventory(-1, FString(TEXT("Empty")));


					}
					//check here
					MyFinalStageActor = nullptr;
				}
			}
			bIsCorrect = false;
			break;
		default:
			return;
	}
	
    
}

void AThirdStationCharacter::OnZPressed(){
	if(!ActorOverlapping) return;

	AMyInventoryHUD* MyInventoryHUD = getGameHUD();
	if(!MyInventoryHUD) return;

	if(CurrOverlapType == 2){
		MyInventoryHUD->UpdateMaterialViewSelection(true);
	}
	else if(CurrOverlapType == 3){
		MyInventoryHUD->UpdateConfirmWidget();
	}

}


void AThirdStationCharacter::OnXPressed(){
	if(!ActorOverlapping) return;

	AMyInventoryHUD* MyInventoryHUD = getGameHUD();
	if(!MyInventoryHUD) return;
	
	if(CurrOverlapType == 2){

		MyInventoryHUD->UpdateMaterialViewSelection(false);

	}
	else if(CurrOverlapType == 3){
		MyInventoryHUD->UpdateConfirmWidget();
	}
}


//////////////////////////////////////////////////////////////////////////
// Collision
void AThirdStationCharacter::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("calling overlap"));
    //since all clients are being called
    if(!IsLocallyControlled()) return;
    
    if(OtherActor && (OtherActor != this))
    {
		ActorOverlapping = OtherActor;
//        print("Overlap Begin");
//        print(this->getItemName().ToString());

		AMyInventoryHUD* MyInventoryHUD = getGameHUD();
		if(!MyInventoryHUD) return;


		//UPDATE WIDGET HERE
        AMyItemActor* MyItemActor = Cast<AMyItemActor>(OtherActor);
        if(MyItemActor){
			CurrOverlapType = 1;
            FString ItemName = MyItemActor->getItemName();
            MyInventoryHUD->UpdateItemText(ItemName);
            CurrItemOverlap = ItemName;// updateItemOverlap(ItemName);
			

        }

		AMyTraderActor* MyTraderActor = Cast<AMyTraderActor>(OtherActor);
        if(MyTraderActor){
			CurrOverlapType = 2;
            MyInventoryHUD->UpdateMaterialView(CurrInventory, CurrInventoryType);
			
        }

		AMyFinalStageActor* MyFinalStageActor = Cast<AMyFinalStageActor>(OtherActor);
        if(MyFinalStageActor){
			bActorIsDone = MyFinalStageActor->IsDone();
			UE_LOG(LogTemp, Warning, TEXT("here"));
			if(MyFinalStageActor->IsDone()){
				UE_LOG(LogTemp, Warning, TEXT("updating with correct message"));
				MyInventoryHUD->UpdateFinalWidget(2, false, TEXT(""));
			}
			else {
				MyInventoryHUD->ShowConfirmWidget();
			}
			
			CurrOverlapType = 3;
			// bIsCorrect = MyFinalStageActor->IsCorrectItem(CurrInventory);
            // MyInventoryHUD->UpdateMaterialView(CurrInventory);
			
        }


    }
}

void AThirdStationCharacter::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
    if(!IsLocallyControlled()) return;

    CurrOverlapType = 0;

    if(OtherActor && (OtherActor != this))
    {
		ActorOverlapping = nullptr;
//        print("Overlap End");
//        print(*OtherActor->GetName());
        AMyInventoryHUD* MyInventoryHUD = getGameHUD();
		if(!MyInventoryHUD) return;

        AMyItemActor* MyItemActor = Cast<AMyItemActor>(OtherActor);
        if(MyItemActor){
            // clearItemWidget();
			MyInventoryHUD->ClearItemText();
        }

		AMyTraderActor* MyTraderActor = Cast<AMyTraderActor>(OtherActor);
        if(MyTraderActor){
            // clearMaterialViewWidget();
			MyInventoryHUD->ClearMaterialView();
        }

		AMyFinalStageActor* MyFinalStageActor = Cast<AMyFinalStageActor>(OtherActor);
        if(MyFinalStageActor){
			MyInventoryHUD->ClearConfirmWidget();
            MyInventoryHUD->ClearFinalWidget();
			bIsCorrect = false;
			bActorIsDone = false;
			if(CurrInventoryType && MyFinalStageActor && bServerClient) {
				updateInventory(-1, FString(TEXT("Empty")));
				bServerClient = false;
			}
            // MyInventoryHUD->UpdateMaterialView(CurrInventory);
			
        }
        
    }
}


/////////////////////////////////////////////
//server-client
bool AThirdStationCharacter::UpdateMVRPC_Validate(const FString& Item, AMyFinalStageActor* MyFinalStageActor){
	return true;
}


void AThirdStationCharacter::UpdateMVRPC_Implementation(const FString& Item, AMyFinalStageActor* MyFinalStageActor){
	AMyInventoryHUD* MyInventoryHUD = getGameHUD();
	if(!MyInventoryHUD || !MyFinalStageActor) return;
	UE_LOG(LogTemp, Warning, TEXT("Item : %s"), *Item);
	MyFinalStageActor->IsCorrectItem(Item);
	MyInventoryHUD->SetIsDone(Item);
	UpdateMVClient(Item, MyFinalStageActor);
}
 
void AThirdStationCharacter::UpdateMVClient_Implementation(const FString& Item, AMyFinalStageActor* MyFinalStageActor){
	AMyInventoryHUD* MyInventoryHUD = getGameHUD();
	if(!MyInventoryHUD) return;
	UE_LOG(LogTemp, Warning, TEXT("Item : %s"), *Item);
	MyFinalStageActor->IsCorrectItem(Item);
	MyInventoryHUD->SetIsDone(Item);
}


void AThirdStationCharacter::ShowMatThu_Implementation(){
}
