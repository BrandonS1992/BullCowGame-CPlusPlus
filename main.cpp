/* This is the console executable, that makes use of the BullCow class.
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// To make syntax Unreal Engine friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside class
void PrintIntro(); 
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //instantiate a new game, to re-use across plays

// Application entry point
int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);
	return 0; // Exit Application
}


void PrintIntro() 
{
	std::cout << "Welcome to Bulls and Cows.\n";
	std::cout << std::endl;
	std::cout << "                 |      |                " << std::endl;
	std::cout << "                ( ______ )      ______   " << std::endl;
	std::cout << "                 { >  > }      ( O  O )  " << std::endl;
	std::cout << "     /------------\\    /        \\    /-----------\\  " << std::endl;
	std::cout << "    /|             \\__/          \\__/    {}   {} |\\ " << std::endl;
	std::cout << "   / |                |          |   {}          | \\  " << std::endl;
	std::cout << "  *  |  __________    /          \\   __________{}|  * " << std::endl;
	std::cout << "     | / \\|        \\ |            | /     \\___/\\ | " << std::endl;
	std::cout << "    |__|           |__|          |__|          |__|    " << std::endl;

	std::cout << "\nHOW TO PLAY: The goal is to guess the right word.\n";
	std::cout << "Letters that are right are bulls. If a letter is right but in the wrong place it is a cow.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

// plays a single instance to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game isn't in Won status.
	// is not Won and there are still tries remaining.
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries){ // TODO change from FOR to WHILE
		FText Guess = GetValidGuess(); 

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

// loop until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {

		// Get guess from player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess please: ";
		std::getline(std::cin, Guess);

		// check and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_LowerCase:
			std::cout << "Please enter all the lowercase letters.\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n)?";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "CONGRATULATIONS! YOU WIN!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}
//leave blank space below. Compiler prefers it.
