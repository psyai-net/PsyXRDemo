// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "DataTypes/A2FDataType.h"
#include "PsyAsyncLiveDriveCharacter.generated.h"

/**
 * 
 */


//live drive response
USTRUCT(BlueprintType)
struct FliveDriveResponse_Demo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 code;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString msg;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLiveDriveResultDelegate, int32, ErrorCode, FString, Message);

UCLASS()
class XR_DEMO_API UPsyAsyncLiveDriveCharacter : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	//
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UPsyAsyncLiveDriveCharacter* SendLiveDriveRequest(const FliveDriveRequest& Request);

public:
	UPROPERTY(BlueprintAssignable)
	FLiveDriveResultDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FLiveDriveResultDelegate OnFail;

	FString LiveDriveURL = "http://localhost:8080/livedrive";

private:
	//send request to drive live character
	void SendRequest(const FliveDriveRequest& Request);


	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
