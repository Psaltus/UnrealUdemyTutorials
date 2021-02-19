// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(WordList, *WordListPath);
    // TODO: Go through list once to confirm no HiddenWords have isograms

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
    HiddenWord = WordList[1]; // Set Hidden Word
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
            PrintLine(TEXT("'%s' is not an isogram! Try again"), *Guess);
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

    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            // PrintLine(TEXT("%c ? %c"), Word[Index], Word[Comparison]);
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
            
        }

        // PrintLine(TEXT("%c"), Word[i]);
    }
    

    return true;
}