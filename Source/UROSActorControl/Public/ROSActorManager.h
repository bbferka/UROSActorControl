// Copyright 2017, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "GameFramework/Actor.h"
#include "Engine.h"
//#include "EditorEngine.h"
#include "CoreMinimal.h"
#include "ROSBridgeHandler.h"
#include "ROSBridgeSubscriber.h"
//#include "visualization_msgs/MarkerArray.h"

#include "UpdateObjectsSrv.h"
//#include "ROSMarkerArraySubscriber.h"
#include "UpdateActorPositionServiceServer.h"
#include "ROSActorManager.generated.h"



UCLASS()
class UROSACTORCONTROL_API AROSActorManager : public AActor
{
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  AROSActorManager();

  TSharedPtr<FROSBridgeHandler> Handler;

//  TSharedPtr<FROSMarkerArraySubscriber> Subscriber;
  TSharedPtr<FROSUpdateActorPositionServiceServer> AddNewObjectServiceServer;

  UPROPERTY(EditAnywhere, Category = "ROS Settings")
  FString ROSBridgeServerIPAddr;

  UPROPERTY(EditAnywhere, Category = "ROS Settings")
  uint32 ROSBridgeServerPort;

  UPROPERTY(EditAnywhere, Category = "ROS Settings")
  FString MarkerTopicName;


  UPROPERTY(EditAnywhere, Category = "Offset (cm) to World")
  FVector WorldOffset;



protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;
  // Called when the game ends
  virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

};
