#pragma once

#include "CoreMinimal.h"
#include "Engine.h"

#include "ROSBridgeSrvServer.h"
#include "UpdateObjectsSrv.h"
#include "geometry_msgs/PoseStamped.h"

typedef TPair < FString, geometry_msgs::PoseStamped > TNamePosePair;

class FROSUpdateActorPositionServiceServer : public FROSBridgeSrvServer
{

public:
  bool Success;

  TQueue <TNamePosePair> MessageQueue;

  FROSUpdateActorPositionServiceServer(FString Name):
    FROSBridgeSrvServer(Name, TEXT("iai_robosherlock_msgs/UpdateObjects"))
  {

  }

  TSharedPtr<FROSBridgeSrv::SrvRequest> FromJson(TSharedPtr<FJsonObject> JsonObject) const override
  {
    TSharedPtr<FROSBridgeSrvUpdateObjects::Request> Request_ =
      MakeShareable(new FROSBridgeSrvUpdateObjects::Request());
    Request_->FromJson(JsonObject);
    return TSharedPtr<FROSBridgeSrv::SrvRequest>(Request_);
  }

  TSharedPtr<FROSBridgeSrv::SrvResponse> Callback(TSharedPtr<FROSBridgeSrv::SrvRequest> Request) override
  {
    TSharedPtr<FROSBridgeSrvUpdateObjects::Request> Request_ =
      StaticCastSharedPtr<FROSBridgeSrvUpdateObjects::Request>(Request);

    FString name = Request_->GetName().ToString();
    geometry_msgs::PoseStamped ps = Request_->GetPoseStamped();

    TNamePosePair posePair(name,ps);
    MessageQueue.Enqueue(posePair);
    bool ValidMarkers  = true;
    if(ValidMarkers)
      return MakeShareable<FROSBridgeSrv::SrvResponse>
             (new FROSBridgeSrvUpdateObjects::Response(true));
    else
      return MakeShareable<FROSBridgeSrv::SrvResponse>
             (new FROSBridgeSrvUpdateObjects::Response(false));
  }

  void setSucces(bool b)
  {
    Success = b;
  }
};
