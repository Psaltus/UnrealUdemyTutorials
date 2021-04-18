// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Press TAB to control the board."));
    SetupGame();     
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
    TArray<FString> WordList;
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(WordList, *WordListPath);

    WordList = GetValidWords(WordList);

    HiddenWord = *WordList[FMath::RandRange(0, WordList.Num() - 1)]; // Set Hidden Word

    Lives = HiddenWord.Len(); // Set Lives
    bGameOver = false;

    
    PrintLine(TEXT("Welcome!"));
    // PrintLine(TEXT("Total number of words: %i"), GetValidWords(WordList).Num());
    PrintLine(TEXT("Type a guess of the word"));
    PrintLine(TEXT("Guess the %i letter isogram word"), Lives);
    // PrintLine(TEXT("The hidden word is %s"), *HiddenWord); // Debug
}

void UBullCowCartridge::EndGame()
{
    ClearScreen();
    
    SetupGame();
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    FBullCowCount Count;
    
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
             // Show Bulls and Cows
            GetBullCows(Guess, Count.Bulls, Count.Cows);
            PrintLine(TEXT("Ouch. Minus 1"));
            PrintLine(TEXT("You have %i Bulls, and %i Cows!"), Count.Bulls, Count.Cows);
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

bool UBullCowCartridge::IsIsogram(const FString& Word) const
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

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& Words) const
{
    TArray<FString> ValidWordList;

    for (FString WordToTest : Words)
    {
        if ((WordToTest.Len() >= 4 && WordToTest.Len() <= 8) && IsIsogram(WordToTest))
        {
            ValidWordList.Emplace(WordToTest);
            // PrintLine(TEXT("Added word %s"), *WordList[i]);
        }
    }
    return ValidWordList;
}

void UBullCowCartridge::GetBullCows(const FString& Guess, int32& BullCount, int32& CowCount) const
{
    BullCount, CowCount = 0;
    TArray<int32> UsedIndex;

    // For every index Guess == index HiddenWord, Bull++
    // Check if it's a cow, Cow++

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        // Bulls
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            BullCount++;
            UsedIndex.Emplace(GuessIndex);
            continue;
        }

        // Cows
        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (UsedIndex.Contains(HiddenIndex))
            {
                continue;
            }
            else
            {
                if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
                {
                    CowCount++;
                    UsedIndex.Emplace(HiddenIndex); 
                    break;
                }
            }
                
        }   
    }
}