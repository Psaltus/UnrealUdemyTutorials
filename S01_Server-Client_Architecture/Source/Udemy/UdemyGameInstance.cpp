// Fill out your copyright notice in the Description page of Project Settings.


#include "UdemyGameInstance.h"

#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"


UUdemyGameInstance::UUdemyGameInstance(const FObjectInitializer & ObjectIniializer)
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Constructor"));
}

void UUdemyGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Init"));
}

void UUdemyGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, TEXT("Hosting Game"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UUdemyGameInstance::JoinGame(const FString& ipaddr)
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(-1, 2, FColor::Green, FString::Printf(TEXT("Joining %s"), *ipaddr));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(ipaddr, ETravelType::TRAVEL_Absolute);
}