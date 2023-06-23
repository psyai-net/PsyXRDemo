// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "UObject/Object.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "DataTypes/A2FDataType.h"
#include "PsyAsyncA2FTask.generated.h"

/**
 * 
 */



DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FA2FResultDelegate, FA2FResult, Result, FString, Message);


UCLASS()
class XR_DEMO_API UPsyAsyncA2FTask : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FA2FResultDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FA2FResultDelegate OnFail;

	//获取Audio2Face的结果
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Async_A2FTask")
	static UPsyAsyncA2FTask* SendA2FRequestTask(FString InReqGuid, FString InAudioURL, FString InUid, FString InToken);

private:

	//A2F请求的URL
	FString A2FURL = "https://dev.api.psyai.net/v1/jobgate/a2f";

	void SendA2FRequest(const FString& InReqGuid, const FString& InAudioURL, const FString& InUid, const FString& InToken);

	void HandleA2FRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
};
