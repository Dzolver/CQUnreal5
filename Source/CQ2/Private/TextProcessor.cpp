// Fill out your copyright notice in the Description page of Project Settings.


#include "TextProcessor.h"
#include "Misc/OutputDeviceDebug.h"
#include "Engine/Engine.h"

FString UTextProcessor::AnalyzeText(FString input)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *input);
	return FString(input);
}
