// Fill out your copyright notice in the Description page of Project Settings.


#include "PsyAsyncA2FTask.h"

#include "HttpModule.h"
#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"


UPsyAsyncA2FTask* UPsyAsyncA2FTask::SendA2FRequestTask(FString InReqGuid, FString InAudioURL, FString InUid, FString InToken)
{
	UPsyAsyncA2FTask* Async_A2FTask = NewObject<UPsyAsyncA2FTask>();
	Async_A2FTask->SendA2FRequest(InReqGuid, InAudioURL, InUid, InToken);
	return Async_A2FTask;
}

void UPsyAsyncA2FTask::SendA2FRequest(const FString& InReqGuid, const FString& InAudioURL, const FString& InUid, const FString& InToken)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UPsyAsyncA2FTask::HandleA2FRequest);
	HttpRequest->SetHeader("Content-Type", "application/json;charset=UTF-8");
	HttpRequest->SetHeader("Accept", "application/json");
	HttpRequest->SetHeader("uid", InUid);
	HttpRequest->SetHeader("token", InToken);
	HttpRequest->SetURL(A2FURL);
	HttpRequest->SetVerb(TEXT("POST"));
	FA2FRequest A2FRequest;
	A2FRequest.req = InReqGuid;
	A2FRequest.url = InAudioURL;
	FString RequestBodyStr;
	if (FJsonObjectConverter::UStructToJsonObjectString(A2FRequest, RequestBodyStr))
	{
		HttpRequest->ProcessRequest();
	}
	else
	{
		OnFail.Broadcast(FA2FResult(), "UStructToJsonObjectString failed");
	}
}

void UPsyAsyncA2FTask::HandleA2FRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	if (bSucceeded)
	{
		if (HttpResponse.IsValid())
		{
			const FString ResponseStr = HttpResponse->GetContentAsString();
			FA2FResult A2FResult;
			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseStr, &A2FResult, 0, 0))
			{
				OnSuccess.Broadcast(A2FResult, "JsonObjectStringToUStruct success");
			}
			else
			{
				OnFail.Broadcast(FA2FResult(), "JsonObjectStringToUStruct failed");
			}
		}
		else
		{
			OnFail.Broadcast(FA2FResult(), "HttpResponse is invalid");
		}
	}
	else
	{
		OnFail.Broadcast(FA2FResult(), "HandleA2FRequest failed");
	}
}
