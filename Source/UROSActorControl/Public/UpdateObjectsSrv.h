#pragma once

#include "ROSBridgeSrv.h"
#include "std_msgs/String.h"
#include "geometry_msgs/PoseStamped.h"


class UROSBRIDGE_API FROSBridgeSrvUpdateObjects : public FROSBridgeSrv {

protected:
    FString Type;

public:
    FROSBridgeSrvUpdateObjects()
    {
        Type = TEXT("iai_robosherlock/UpdateObjects");
    }

    class Request : public SrvRequest {
    private:
        FROSBridgeMsgStdmsgsString name;
        FROSBridgeMsgGeometrymsgsPoseStamped poseStamped;

    public:
        Request(FROSBridgeMsgStdmsgsString name_,
                FROSBridgeMsgGeometrymsgsPoseStamped poseStamped_):name(name_),poseStamped(poseStamped_) { }
        Request() {}
        FROSBridgeMsgStdmsgsString GetName() const { return name; }
        void SetName(FROSBridgeMsgStdmsgsString name_) { name = name_; }
        FROSBridgeMsgGeometrymsgsPoseStamped GetPoseStamped() const { return poseStamped; }
        void setPoseStamped( FROSBridgeMsgGeometrymsgsPoseStamped poseStamped_) {poseStamped = poseStamped_;}

        virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
            name = JsonObject->GetStringField("name");
            poseStamped.FromJson(JsonObject->GetObjectField("pose_stamped"));
        }

        static Request GetFromJson(TSharedPtr<FJsonObject> JsonObject)
        {
            Request req;
            req.FromJson(JsonObject);
            return req;
        }

        virtual FString ToString() const override
        {
            return TEXT("UpdateObjects::Request { name = ") + name.ToString() +
                   TEXT("                         pose = ") + poseStamped.ToString();
        }

        virtual TSharedPtr<FJsonObject> ToJsonObject() const {
          TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
          Object->SetStringField(TEXT("name"),name.ToString());
          Object->SetObjectField(TEXT("pose_stamped"),poseStamped.ToJsonObject());
          return Object;
        }
    };

    class Response : public SrvResponse {
    private:
        bool success;

    public:
        Response() {}
        Response(bool success_) : success(success_) {}

        void SetSuccess(bool success_) { success = success_; }

        virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
            success = JsonObject->GetBoolField("success");
        }

        static Response GetFromJson(TSharedPtr<FJsonObject> JsonObject)
        {
            Response rep; rep.FromJson(JsonObject);
            return rep;
        }

        virtual FString ToString() const override
        {

          return success==true ? TEXT("UpdateObjects::Response { success } "): TEXT("UpdateObjects::Responsne { fail }");
        }

        virtual TSharedPtr<FJsonObject> ToJsonObject() const {
            TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
            Object->SetBoolField("success", success);
            return Object;
        }
    };

};
