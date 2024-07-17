// Fill out your copyright notice in the Description page of Project Settings.


#include "TCPManager.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"

// Sets default values
ATCPManager::ATCPManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATCPManager::BeginPlay()
{
	Super::BeginPlay();
	ConnectToServer();
	SendMessageToServer(TEXT("TestMessage from Client!"),TEXT("t#"));
	ReceiveMessageFromServer();
}

// Called every frame
void ATCPManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATCPManager::ConnectToServer()
{
	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	TcpSocket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("default"), false);

	FIPv4Address Ip;
	FIPv4Address::Parse(TEXT("127.0.0.1"), Ip);

	TSharedRef<FInternetAddr> Addr = SocketSubsystem->CreateInternetAddr();
	Addr->SetIp(Ip.Value);
	Addr->SetPort(50052);

	bool bIsConnected = TcpSocket->Connect(*Addr);
	if (bIsConnected)
	{
		UE_LOG(LogTemp, Warning, TEXT("Connected to CoGo2 server!"));
	}
	else 
	{
		UE_LOG(LogTemp,Error,TEXT("Failed to connect to CoGo2 server!"))
	}
}

void ATCPManager::SendMessageToServer(const FString& Message, const FString& PacketType)
{
	if (!TcpSocket) return;
	FString PacketMessage = PacketType + Message;
	const TCHAR* SerializedChar = PacketMessage.GetCharArray().GetData();
	int32 Size = FCString::Strlen(SerializedChar);
	int32 Sent = 0;

	bool bIsSent = TcpSocket->Send((uint8*)TCHAR_TO_UTF8(SerializedChar), Size, Sent);
	if (bIsSent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Message sent: %s"), *Message);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to send message."));
	}
}

void ATCPManager::ReceiveMessageFromServer()
{
	if (!TcpSocket) return;
	TArray<uint8> ReceivedData;
	uint32 Size;
	while (TcpSocket->HasPendingData(Size))
	{
		ReceivedData.SetNumUninitialized(FMath::Min(Size, 65507u));
		int32 Read = 0;
		TcpSocket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);
	}
	if (ReceivedData.Num() <= 0)
	{
		return;
	}
	//Create a string from the received data
	FString ReceivedString = FString(ANSI_TO_TCHAR(reinterpret_cast<const char*>(ReceivedData.GetData())));
	UE_LOG(LogTemp, Warning, TEXT("Message received: %s"), *ReceivedString);
}

