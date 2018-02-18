
#pragma once

#include <ROSBridgeSubscriber.h>
#include <visualization_msgs/MarkerArray.h>

class FROSMarkerArraySubscriber : public FROSBridgeSubscriber {

public:
  TMap <int32,visualization_msgs::Marker> objects;
  TQueue <visualization_msgs::Marker> ObjectsToUpdate;
  TMap <FString,FString> nameMapping;

  FROSMarkerArraySubscriber(FString Topic_);

  ~FROSMarkerArraySubscriber() override;

  TSharedPtr<FROSBridgeMsg> ParseMessage(TSharedPtr<FJsonObject> JsonObject) const override;

  void Callback(TSharedPtr<FROSBridgeMsg> msg) override;


};
