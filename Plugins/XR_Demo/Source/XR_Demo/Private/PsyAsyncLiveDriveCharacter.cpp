// Fill out your copyright notice in the Description page of Project Settings.


#include "PsyAsyncLiveDriveCharacter.h"

#include "HttpModule.h"
#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"

UPsyAsyncLiveDriveCharacter* UPsyAsyncLiveDriveCharacter::SendLiveDriveRequest(const  FliveDriveRequest& Request)
{
	UPsyAsyncLiveDriveCharacter* LiveDriveRequest = NewObject<UPsyAsyncLiveDriveCharacter>();
	LiveDriveRequest->SendRequest(Request);
	return LiveDriveRequest;
}

void UPsyAsyncLiveDriveCharacter::SendRequest(const FliveDriveRequest& Request)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UPsyAsyncLiveDriveCharacter::OnResponseReceived);
	HttpRequest->SetHeader("Content-Type", "application/json;charset=UTF-8");
	HttpRequest->SetHeader("Accept", "application/json");
	HttpRequest->SetURL(LiveDriveURL);
	HttpRequest->SetVerb(TEXT("POST"));
	FliveDriveRequest LiveDriveRequest;
	FString RequestBodyStr;
	if (FJsonObjectConverter::UStructToJsonObjectString(LiveDriveRequest, RequestBodyStr))
	{
		HttpRequest->ProcessRequest();
	}
	else
	{
		//error code you can define yourself  
		OnFail.Broadcast(0, "FliveDriveRequest UStructToJsonObjectString failed");
	}
}

void UPsyAsyncLiveDriveCharacter::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (Response.IsValid())
		{
			const FString ResponseStr = Response->GetContentAsString();
			FliveDriveResponse_Demo LiveDriveResponse;
			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseStr, &LiveDriveResponse, 0, 0))
			{
				OnSuccess.Broadcast(LiveDriveResponse.code, LiveDriveResponse.msg);
			}
			else
			{
				OnFail.Broadcast(LiveDriveResponse.code, "JsonObjectStringToUStruct failed");
			}
		}
		else
		{
			//error code you can define yourself  
			OnFail.Broadcast(0, "Response is not valid");
		}
	}
	else
	{
		//error code you can define yourself  
		OnFail.Broadcast(1, "Request failed");
	}
}
