// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UdemyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UDEMY_API UUdemyGameInstance : public UGameInstance
{
	GENERATED_BODY()


public:
	UUdemyGameInstance(const FObjectInitializer & ObjectIniializer);

	virtual void Init();

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void JoinGame(const FString& ipaddr);

	
};
