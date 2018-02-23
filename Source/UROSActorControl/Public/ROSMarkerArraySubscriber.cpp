#include "ROSMarkerArraySubscriber.h"


FROSMarkerArraySubscriber::FROSMarkerArraySubscriber(FString Topic_):
  FROSBridgeSubscriber(Topic_, TEXT("visualization_msgs/MarkerArray"))
{
  UE_LOG(LogTemp, Log, TEXT("Subscriber created"));

  //scenario1
  nameMapping.Add(TEXT("BluePlasticSpoon"), TEXT("SM_BluePlasticSpoon_41"));
  nameMapping.Add(TEXT("EdekaRedBowl"), TEXT("SM_EdekaRedBowl_50"));
  nameMapping.Add(TEXT("JeMilch"), TEXT("SM_JeMilch_30"));
  nameMapping.Add(TEXT("CupEcoOrange"), TEXT("SM_CupEcoOrange_2"));
  nameMapping.Add(TEXT("KelloggsCornFlakes"), TEXT("SM_KelloggsCornFlakes_60"));
  nameMapping.Add(TEXT("KelloggsToppasMini"), TEXT("SM_KelloggsToppasMini_101"));
  nameMapping.Add(TEXT("KnusperSchokoKeks"), TEXT("SM_KnusperSchokoKeks_63"));
  nameMapping.Add(TEXT("KoellnMuesliKnusperHonigNuss"), TEXT("SM_KoellnMuesliKnusperHonigNuss2_32	"));
  nameMapping.Add(TEXT("LargeGreySpoon"), TEXT("SM_LargeGreySpoon_38"));
  nameMapping.Add(TEXT("LionCerealBox"), TEXT("SM_LionCerealBox_92"));
  nameMapping.Add(TEXT("NesquikCereal"), TEXT("SM_NesquikCereal_7"));
  nameMapping.Add(TEXT("RedMetalBowlWhiteSpeckles"), TEXT("SM_RedMetalBowlWhiteSpeckles_68"));
  nameMapping.Add(TEXT("RedPlasticSpoon"), TEXT("SM_RedPlasticSpoon_44"));
  nameMapping.Add(TEXT("SojaMilch"), TEXT("SM_SojaMilch_27"));
  nameMapping.Add(TEXT("VollMilch"), TEXT("SM_VollMilch_21"));
  nameMapping.Add(TEXT("WeideMilchSmall"), TEXT("SM_WeideMilchSmall_57"));
  nameMapping.Add(TEXT("WhiteCeraicIkeaBowl"), TEXT("SM_WhiteCeramicIkeaBowl_47"));

  //scenario2
  nameMapping.Add(TEXT("AlbiHimbeerJuice"), TEXT("SM_AlbiHimbeerJuice_35"));
  nameMapping.Add(TEXT("BlueCeramicIkeaMug"), TEXT("SM_BlueCeramicIkeaMug_17"));
  nameMapping.Add(TEXT("BlueMetalPlateWhiteSpeckles"), TEXT("SM_BlueMetalPlateWhiteSpeckles_81"));
  nameMapping.Add(TEXT("BluePlasticKnife"), TEXT("SM_BluePlasticKnife_20"));
  nameMapping.Add(TEXT("CupEcoOrange"), TEXT("SM_CupEcoOrange_2"));
  nameMapping.Add(TEXT("JodSalz"), TEXT("SM_JodSalz_75"));
  nameMapping.Add(TEXT("LinuxCup"), TEXT("SM_LinuxCup_93"));
  nameMapping.Add(TEXT("MarkenSalz"), TEXT("SM_MarkenSalz_14"));
  nameMapping.Add(TEXT("MeerSalz"), TEXT("SM_JodSalz_72"));
  nameMapping.Add(TEXT("PfannerGruneIcetea"), TEXT("SM_PfannerGruneIcetea_69"));
  nameMapping.Add(TEXT("PfannerPfirsichIcetea"), TEXT("SM_PfannerPfirsichIcetea_24"));
  nameMapping.Add(TEXT("RedMetalCupWhiteSpeckles"), TEXT("SM_RedMetalCupWhiteSpeckles_96"));
  nameMapping.Add(TEXT("RedMetalPlateWhiteSpeckles"), TEXT("SM_RedMetalPlateWhiteSpeckles_87"));
  nameMapping.Add(TEXT("RedPlasticKnife"), TEXT("SM_RedPlasticKnife_23"));
  nameMapping.Add(TEXT("YellowCeramicPlate"), TEXT("SM_YellowCeramicPlate_90"));


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
