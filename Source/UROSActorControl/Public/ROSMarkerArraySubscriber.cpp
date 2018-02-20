#include "ROSMarkerArraySubscriber.h"


FROSMarkerArraySubscriber::FROSMarkerArraySubscriber(FString Topic_):
  FROSBridgeSubscriber(Topic_, TEXT("visualization_msgs/MarkerArray"))
{
  UE_LOG(LogTemp, Log, TEXT("Subscriber created"));
  nameMapping.Add(TEXT("CupEcoOrange"), TEXT("SM_CupEcoOrange_2"));
  nameMapping.Add(TEXT("EdekaRedBowl"), TEXT("SM_Bowl_2"));
  nameMapping.Add(TEXT("KoellnMuesliKnusperHonigNuss"), TEXT("SM_KoellnMuesliKnusperHonigNussNew_12	"));
  nameMapping.Add(TEXT("SpoonBluePlastic"), TEXT("SM_Spoon_Dessert9_2"));
  nameMapping.Add(TEXT("WeideMilchSmall"), TEXT("SM_VollMilch_21"));
  nameMapping.Add(TEXT("LionCerealBox"), TEXT("SM_LionCereal_15"));
  nameMapping.Add(TEXT("VollMilch"), TEXT("SM_VollMilch_21"));
}

FROSMarkerArraySubscriber::~FROSMarkerArraySubscriber() {}


TSharedPtr<FROSBridgeMsg> FROSMarkerArraySubscriber::ParseMessage
(TSharedPtr<FJsonObject> JsonObject) const
{
  UE_LOG(LogTemp, Log, TEXT("In the ParseMessage"));
  TSharedPtr<visualization_msgs::MarkerArray> VisArrayMessage =
    MakeShareable<visualization_msgs::MarkerArray>(new visualization_msgs::MarkerArray());
  VisArrayMessage->FromJson(JsonObject);

  UE_LOG(LogTemp, Log, TEXT("In the ParseMessage [%s]"), *VisArrayMessage->ToString());
  return StaticCastSharedPtr<FROSBridgeMsg>(VisArrayMessage);
}

void FROSMarkerArraySubscriber::Callback(TSharedPtr<FROSBridgeMsg> msg)
{
  TSharedPtr<visualization_msgs::MarkerArray> ArrayMessage = StaticCastSharedPtr<visualization_msgs::MarkerArray>(msg);
  // downcast to subclass using StaticCastSharedPtr function
  TArray<visualization_msgs::Marker> marker_array = ArrayMessage->GetMarkers();

  for(visualization_msgs::Marker & marker : marker_array)
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
