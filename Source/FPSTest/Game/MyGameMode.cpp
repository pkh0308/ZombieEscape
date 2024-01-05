// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MyGameMode.h"

AMyGameMode::AMyGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PawnRef(TEXT("/Script/FPSTest.PlayerCharacter"));
	if (PawnRef.Class)
	{
		DefaultPawnClass = PawnRef.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> ControllerRef(TEXT("/Script/FPSTest.MyPlayerController"));
	if (ControllerRef.Class)
	{
		PlayerControllerClass = ControllerRef.Class;
	}
}
