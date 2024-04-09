// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <nholmann/json.hpp>
#include "NetworkManager.generated.h"

using namespace nlohmann;

UCLASS()
class CQ2_API ANetworkManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANetworkManager();

	UFUNCTION(BlueprintCallable, category = "NetworkManager")
	void SendLoginRequestV2(FString par1, FString par2, FString request_ID);
	UFUNCTION(BlueprintCallable, category = "NetworkManager")
	void SendRegistrationRequestV2(FString par1, FString par2, FString request_ID);
	UFUNCTION(BlueprintCallable, category = "NetworkManager")
	void SendTestMessageV2(FString par1);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FString Message = FString(TEXT("Attempting to connect to server"));

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	void StartAsyncTask();
	void StartAsyncTask_UsingAsyncTask();
	void SendDataToServer(std::string request, std::string packetType);
};

class FNetworkAsyncTask : public FNonAbandonableTask
{
public:
	FNetworkAsyncTask(int32 InLoopCount) : LoopCount(InLoopCount) {}
	FORCEINLINE TStatId GetStatId() const {
		RETURN_QUICK_DECLARE_CYCLE_STAT(FMyAsyncTask, STATGROUP_ThreadPoolAsyncTasks);
	}
	void DoWork();
private:
	int32 LoopCount;
	void ProcessIncomingData(FString incomingData);
	std::string StringToRawStringLiteral(const std::string& input);
	bool replace(std::string& str, const std::string& from, const std::string& to);
	std::vector<std::string> SplitString(const std::string& input, const std::string& separator);
	std::vector<std::string> SplitStringByChar(const std::string& input, const char& separator);
	json toJson(std::string jsonString);
};

