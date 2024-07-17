// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TextProcessor.generated.h"

/**
 * 
 */
UCLASS()
class CQ2_API UTextProcessor : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable,Category="TextProcessing")
	static FString AnalyzeText(FString input);
};
