// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame(); // Set up game
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    
    // If game is over, ClearScreen() and SetupGame()
    // else Check PlayerGuess 
    ProcessGuess(Input);

}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("cakes"); // Set Hidden Word
    // const TCHAR HW[] = TEXT(FString::Printf("%s", *HiddenWord));
    // const TCHAR HW[] = FString::Printf(TEXT("%s", *HiddenWord));



    Lives = HiddenWord.Len(); // Set Lives
    bGameOver = false;

    
    PrintLine(TEXT("Welcome!"));
    PrintLine(TEXT("Type a guess of the word"));
    PrintLine(TEXT("Guess the %i letter word"), Lives);
}

void UBullCowCartridge::EndGame()
{
    ClearScreen();
    
    SetupGame();
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (bGameOver)
    {
        EndGame();
    }
    else
    {   
        // Check answer
        if (Guess == HiddenWord)
        {
            PrintLine(TEXT("Nice! You got it! The word was %s"), *HiddenWord);
            bGameOver = true;
        }
        else if (Guess.Len() != HiddenWord.Len())
        {
            PrintLine(TEXT("Make sure the word is %i characters long"), HiddenWord.Len());
        }
        else if (!IsIsogram(Guess)) // Check if isogram
        {
            PrintLine(TEXT("'%s' is not an isogram! Try again"), *HiddenWord);
        }
        else
        {
            // Check answer, mentioning the bulls and the cows
            PrintLine(TEXT("Ouch. Minus 1"));
            --Lives;
        }

        if (Lives <= 0)
        {
            PrintLine(TEXT("Sorry, game over! The word was %s"), *HiddenWord);
            bGameOver = true;
        }
        PrintLine(TEXT("Lives: %i"), Lives);
    }
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
    // Loop through array to check for repeats
    // If no repeats, return true
    // If repeats found, return false before loop ends

    return true;
}