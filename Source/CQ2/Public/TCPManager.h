// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TCPManager.generated.h"

UCLASS()
class CQ2_API ATCPManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATCPManager();
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FString NPCResponse;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Network")
	void SendMessageToServer(const FString& Message, const FString& PacketType);

private:
	void ConnectToServer();
	void ReceiveMessageFromServer();
	class FSocket* TcpSocket;
	FTimerHandle TimerHandle;
};
