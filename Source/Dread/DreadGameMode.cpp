// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DreadGameMode.h"
#include "DreadHUD.h"
#include "DreadCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADreadGameMode::ADreadGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ADreadHUD::StaticClass();
}
