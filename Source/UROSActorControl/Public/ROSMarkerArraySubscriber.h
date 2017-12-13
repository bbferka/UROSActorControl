
#pragma once

#include <ROSBridgeSubscriber.h>
#include <visualization_msgs/MarkerArray.h>

class FROSMarkerArraySubscriber : public FROSBridgeSubscriber {




public:
  TMap <int32,FROSBridgeMsgVisualizationmsgsMarker> objects;
  TQueue <FROSBridgeMsgVisualizationmsgsMarker> ObjectsToUpdate;
  TMap <FString,FString> nameMapping;

  FROSMarkerArraySubscriber(FString Topic_);

  ~FROSMarkerArraySubscriber() override;

  TSharedPtr<FROSBridgeMsg> ParseMessage(TSharedPtr<FJsonObject> JsonObject) const override;

  void CallBack(TSharedPtr<FROSBridgeMsg> msg) override;


};
