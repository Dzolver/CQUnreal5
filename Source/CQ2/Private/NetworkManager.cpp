// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "NetworkManager.h"
#include "GameDataManipulation.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <thread>
#include <winsock2.h>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <nholmann/json.hpp>

#define PORT 20001
#define HOST "127.0.0.1"
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "20001"
#define LOGIN "L0#"
#define REGISTER "R0#"
#define TEST "TT#"
#define PACKET_SIZE 20000

using json = nlohmann::json;
// Sets default values
//
SOCKET ClientSocket;

nlohmann::json FNetworkAsyncTask::toJson(std::string jsonString)
{
    return nlohmann::json::parse(jsonString);
}

std::vector<std::string> FNetworkAsyncTask::SplitString(const std::string& input, const std::string& separator)
{
    std::vector<std::string> result;
    size_t pos = 0;
    size_t found;

    while ((found = input.find(separator, pos)) != std::string::npos) {
        result.push_back(input.substr(pos, found - pos));
        pos = found + separator.length();
    }

    result.push_back(input.substr(pos));
    return result;
}

std::vector<std::string> FNetworkAsyncTask::SplitStringByChar(const std::string& input, const char& separator)
{
    std::vector<std::string> result;
    std::istringstream stream(input);
    std::string token;
    while (getline(stream, token, separator)) {
        result.push_back(token);
    }
    return result;
}

void ANetworkManager::SendDataToServer(std::string request, std::string packetType) {
    const char* sendData = request.c_str();
    if (send(ClientSocket, sendData, strlen(sendData), 0) == SOCKET_ERROR)
    {
        // Handle error
        GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Yellow, FString::Printf(TEXT("Sending Data to the Server Failed!")));
        closesocket(ClientSocket);
        WSACleanup();
        return;
    }
    else {
        FString requestStr(request.c_str());
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *requestStr));
    }
}

ANetworkManager::ANetworkManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ANetworkManager::SendLoginRequestV2(FString usernameInput,FString passwordInput,FString request_ID)
{
    //create GUID 
    std::string const username = TCHAR_TO_UTF8(*usernameInput);
    std::string const password = TCHAR_TO_UTF8(*passwordInput);
    std::string const requestId = TCHAR_TO_UTF8(*request_ID);
    std::string request = LOGIN + requestId + "?"+LOGIN + username + "?"+LOGIN + password + "\n";
    SendDataToServer(request, "Login");
}

void ANetworkManager::SendRegistrationRequestV2(FString usernameInput, FString passwordInput,FString request_ID)
{
    //create GUID 
    std::string const username = TCHAR_TO_UTF8(*usernameInput);
    std::string const password = TCHAR_TO_UTF8(*passwordInput);
    std::string const requestId = TCHAR_TO_UTF8(*request_ID);
    std::string request = REGISTER+ requestId +"?"+REGISTER + username + "?"+REGISTER + password + "\n";
    SendDataToServer(request, "Register");
}

void ANetworkManager::SendTestMessageV2(FString par1)
{
    std::string const messageToServer = TCHAR_TO_UTF8(*par1);
    std::string request = TEST + messageToServer +"\n";
    SendDataToServer(request, "TEST");
}

std::string FNetworkAsyncTask::StringToRawStringLiteral(const std::string& input)
{
    return "R\"" + input + R"(")";
}

bool FNetworkAsyncTask::replace(std::string& str, const std::string& from, const std::string& to)
{
    size_t start_pos = str.find(from);
    if (start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

void FNetworkAsyncTask::ProcessIncomingData(FString incomingData) {
    //Process data here according to packet header type
    //convert to std::string
    std::string data = std::string(TCHAR_TO_UTF8(*incomingData));
    std::vector<std::string> serverData = SplitString(data, "#?");
    FString headerStr = (serverData[0].c_str());
    //Get the packetCode
    std::string packetCode = serverData[0].substr(0, 2);
    //handle the packet based on the packet code
    std::string packetType = "";
    FString contentStr;
    //--------------------------------------------REMOVE SUBSTRINGS AND OTHER UNWANTED STRING LITERALS FROM JSON STRING --------------------------------------------
    if (serverData.size() >= 2) {
        //substrings
        const std::string substrings[] = {"\"@\"" }; //include any more substrings you want to clean from the JSON string here.
        //remove substrings
        for (const auto& substring : substrings) {
            size_t found = serverData[1].find(substring);
            while (found != std::string::npos) {
                serverData[1].erase(found, substring.length());
                found = serverData[1].find(substring);
            }
        }
        //replace(serverData[1], "}\"}", "}}");
        contentStr = serverData[1].c_str();
    }
    else {
        contentStr = serverData[0].c_str();
    }
    //---------------------------------------------------------------------------------------------------------------------------------------------------------------
    UE_LOG(LogTemp,Warning, TEXT("%c"), packetCode[0]);
    UE_LOG(LogTemp,Warning, TEXT("%c"), packetCode[1]);
    UE_LOG(LogTemp, Warning, TEXT("%s"), *contentStr);
    //-----------------------------------CONVERT PACKET CONTENT TO RAW STRING LITERAL-----------------------------------------------------
    std::string packetContentSTR = "R\"" + serverData[1] + R"(")";
    //FString packetContent = FString(packetContentSTR.c_str());
    switch (packetCode[0])
    {
        //login related
        case 'L':
            GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Green, FString::Printf(TEXT("Login related Packet")));
            switch (packetCode[1]) 
            {
                //login success
                case 'S':
                    packetType = "Login Success Packet received!";
                    //let's create the user object as a test to see if json -> struct works
                    //first create the json object
                    //nlohmann::json jsonObj = nlohmann::json::parse(serverData[1]);
                    std::stringstream input;
                    input << R"({"name":"Gilbert", "wins":"11"})";
                    json parsedJsonTest = json::parse(input);
                    FString jsonString = FString(parsedJsonTest.dump().c_str());
                    UE_LOG(LogTemp, Warning, TEXT("Parsed JSONTEST: %s"), *jsonString);
                    //lets try printing the parsed packet content

                    FCQ_User testObject;
                    break;
            }
            break;
        default:
            packetType = "Unknown Packet Type";
    }
    FString packetTypeDebug(packetType.c_str());
    GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Green, FString::Printf(TEXT("%s"),*packetTypeDebug));
}

//// Called when the game starts or when spawned
void ANetworkManager::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Yellow, FString::Printf(TEXT("%s"), *Message));
	}
	//StartAsyncTask();
	StartAsyncTask_UsingAsyncTask();
}
//
// Called every frame
void ANetworkManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANetworkManager::StartAsyncTask()
{
    (new FAutoDeleteAsyncTask<FNetworkAsyncTask>(10))->StartBackgroundTask();
}

void ANetworkManager::StartAsyncTask_UsingAsyncTask()
{
    AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, []()
        {
            auto MyTask = new FAsyncTask<FNetworkAsyncTask>(10);
            MyTask->StartBackgroundTask();
            MyTask->EnsureCompletion();
            delete MyTask;
        });
}

void FNetworkAsyncTask::DoWork() {
    // Initialize Winsock
    WSADATA WsaData;
    if (WSAStartup(MAKEWORD(2, 2), &WsaData) != 0)
    {
        // Handle error
        return;
    }

    // Create socket
    ClientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (ClientSocket == INVALID_SOCKET)
    {
        // Handle error
        WSACleanup();
        return;
    }

    // Set up server address
    sockaddr_in ServerAddress;
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_port = htons(20001);
    ServerAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    // Connect to server
    if (connect(ClientSocket, (sockaddr*)&ServerAddress, sizeof(ServerAddress)) == SOCKET_ERROR)
    {
        // Handle error
        GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Yellow, FString::Printf(TEXT("Connecting Failed")));
        closesocket(ClientSocket);
        WSACleanup();
        return;
    }
    else {
        // Connection successful, you can now use 'ClientSocket' for communication
        GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Green, FString::Printf(TEXT("Connecting Succeeded!")));
        // Send data to the server
        const char* sendData = "XX#HelloServerfromClient\n";
        if (send(ClientSocket, sendData, strlen(sendData), 0) == SOCKET_ERROR)
        {
            // Handle error
            GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Yellow, FString::Printf(TEXT("Sending Data to the Server Failed!")));
            closesocket(ClientSocket);
            WSACleanup();
            return;
        }
        else {
            GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Green, FString::Printf(TEXT("Sending data Succeeded!")));
        }
        while (true) {
            std::vector<char> buf(PACKET_SIZE);
            int bytesReceived = recv(ClientSocket, buf.data(), PACKET_SIZE, 0);
            if (bytesReceived > 0)
            {
                // Handle received data
                buf[bytesReceived] = '\0'; // Null-terminate the received data
                std::string packetBytes(buf.begin(), buf.end());
                FString packetBytesStr = FString(packetBytes.c_str());
                UE_LOG(LogTemp, Warning, TEXT("PACKET BYTES: %s"), *packetBytesStr);
                
                // 1. replace "\\\"" with "\""
                //replace(packetBytes, "\\\"", "\"");
                // 2. replace "\\\"" with "\"" again
                //replace(packetBytes, "\\\"", "\"");
                // 3. replace "\\\"" with "\"" again
                //replace(packetBytes, "\\\"", "\"");

                replace(packetBytes, "\\\\", "\\");
                
                // remove all existing backslashes
                packetBytes.erase(std::remove(packetBytes.begin(), packetBytes.end(), '\\'), packetBytes.end());
                
                //4. replace "\"{\"" with "{\""
                //replace(packetBytes, "\"{\"", "{\"");
                
                //5. remove all newline characters
                packetBytes.erase(std::remove(packetBytes.begin(), packetBytes.end(), '\n'), packetBytes.end());
                //5. remove all newline characters
                packetBytes.erase(std::remove(packetBytes.begin(), packetBytes.end(), '\r'), packetBytes.end());
                //6 replace "}\"}" with "}}"
                

                FString serverData = (packetBytes.c_str());
                //GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Blue, FString::Printf(TEXT("Received data from server: %s"), *serverData));
                //UE_LOG(LogTemp, Warning, TEXT("%s"), *serverData);
                ProcessIncomingData(serverData);
            }
            else if (bytesReceived == 0)
            {
                // Connection closed by the server
                // Handle accordingly
            }
            else
            {
                // Handle error
            }
        }
    }
    // Data sent successfully
    // Don't forget to close the socket and clean up when done
    GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, FString::Printf(TEXT("Socket is Closing!")));
    closesocket(ClientSocket);
    WSACleanup();
}


