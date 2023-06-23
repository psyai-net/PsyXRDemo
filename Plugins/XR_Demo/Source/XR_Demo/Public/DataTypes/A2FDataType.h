// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "A2FDataType.generated.h"

/**
 * 
 */



//bs 数组结构体
USTRUCT(BlueprintType)
struct FBSData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float timestamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> data;
};

//A2FData
USTRUCT(BlueprintType)
struct FA2FData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString req;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString msg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBSData bs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString hash;
};


//A2F返回结果
USTRUCT(BlueprintType)
struct FA2FResult
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString code;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FA2FData data;
};

//A2F的请求
USTRUCT(BlueprintType)
struct FA2FRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString req;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString url;

};



//liveDrive Request
USTRUCT(BlueprintType)
struct FliveDriveRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString req;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBSData bs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString audioUrl;
};



UCLASS()
class XR_DEMO_API UA2FDataType : public UObject
{
	GENERATED_BODY()
};
