#include "ROSMarkerArraySubscriber.h"


FROSMarkerArraySubscriber::FROSMarkerArraySubscriber(FString Topic_):
  FROSBridgeSubscriber(TEXT("visualization_msgs/MarkerArray"), Topic_)
{
  UE_LOG(LogTemp, Log, TEXT("Subscriber created"));
  nameMapping.Add(TEXT("cup_eco_orange"), TEXT("SM_CupEcoOrange_2"));
  nameMapping.Add(TEXT("edeka_red_bowl"), TEXT("SM_Bowl_8"));
  nameMapping.Add(TEXT("koelln_muesli_knusper_honig_nuss"), TEXT("SM_KoellnMuesliKnusperHonigNuss2_15"));
  nameMapping.Add(TEXT("spoon_blue_plastic"), TEXT("SM_Spoon_Dessert9_2"));
  nameMapping.Add(TEXT("weide_milch_small"), TEXT("SM_VollMilch_5"));
}

FROSMarkerArraySubscriber::~FROSMarkerArraySubscriber() {}


TSharedPtr<FROSBridgeMsg> FROSMarkerArraySubscriber::ParseMessage
(TSharedPtr<FJsonObject> JsonObject) const
{
  UE_LOG(LogTemp, Log, TEXT("In the ParseMessage"));
  TSharedPtr<FROSBridgeMsgVisualizationmsgsMarkerArray> VisArrayMessage =
    MakeShareable<FROSBridgeMsgVisualizationmsgsMarkerArray>(new FROSBridgeMsgVisualizationmsgsMarkerArray());
  VisArrayMessage->FromJson(JsonObject);

  UE_LOG(LogTemp, Log, TEXT("In the ParseMessage [%s]"), *VisArrayMessage->ToString());
  return StaticCastSharedPtr<FROSBridgeMsg>(VisArrayMessage);
}

void FROSMarkerArraySubscriber::CallBack(TSharedPtr<FROSBridgeMsg> msg)
{
  TSharedPtr<FROSBridgeMsgVisualizationmsgsMarkerArray> ArrayMessage = StaticCastSharedPtr<FROSBridgeMsgVisualizationmsgsMarkerArray>(msg);
  // downcast to subclass using StaticCastSharedPtr function
  TArray<FROSBridgeMsgVisualizationmsgsMarker> marker_array = ArrayMessage->GetMarkers();

  for(FROSBridgeMsgVisualizationmsgsMarker & marker : marker_array)
  {
    if(marker.GetMarkeType() == 10)//marker is a mesh resource
    {
      FString meshResource = marker.GetMeshResource();
      if(meshResource.EndsWith(FString(TEXT(".dae"))))
      {

        if(objects.Contains(marker.GetId()))
        {
           objects.Emplace(marker.GetId(), marker);
        }
        else
        {
          UE_LOG(LogTemp, Log, TEXT("New Marker id: %d"), marker.GetId());
          ObjectsToUpdate.Enqueue(marker);
        }
      }

    }
  }
  UE_LOG(LogTemp, Log, TEXT("Message received! Content: %d"), marker_array.Num());
  // do something with the message
  return;
}
