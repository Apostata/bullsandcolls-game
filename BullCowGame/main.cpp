/*
	This is the console executable, that makes use of the BullCow Class.
	This acts as the view in a MVC pattern, and is reponsible for all user interaction.
	For game logic see the FBullCowGame Class
*/

#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include "FBullCowGame.h"

//to make sintax Unreal Friendly
using Ftext = std::string;
using int32 = int;

//Function prototypes = Interface. Function prototypes as outside class, wich we re-use across plays
void PrintIntro();
void PlayGame();
void PrintGameSummary();
Ftext GetValidGuess();
bool AksToPlayAgain();
FBullCowGame BCGame; //instantiate a new game

//the entry point for our applications
int main(){
	
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
	} while (AksToPlayAgain());

	return 0; //exit the application
}

//introcude the game
void PrintIntro() {
	std::cout << "Welcome to Bulls and Cows, a fun word game\n";
	std::cout << "              ######                   #####                                                        " << std::endl;
	std::cout << "  ####;       #######-              -/######.                                                 ##M#@ " << std::endl;
	std::cout << "##########    #########.           #########                                               #########" << std::endl;
	std::cout << "//   #######  /## ############M /#######.##                           #########         /######/   #" << std::endl;
	std::cout << "        /#####.### ###################  ###                         #############     $#####.       " << std::endl;
	std::cout << "           ############     .#####     ###                        ,#####     =##### M#####          " << std::endl;
	std::cout << "             ########          ####   #########      =#######M   M####          #######M            " << std::endl;
	std::cout << " ###########, ##                    #= ######   #####  .###### #M                    #+ ############" << std::endl;
	std::cout << " ##   ########                        #####      ###      ####,                        ########   ##" << std::endl;
	std::cout << " ##    X#######   :###                ####     ######/     ###.                ###   .#######    /##" << std::endl;
	std::cout << " ;#####   ####### #####,            ############    :###########.            ######/######/  ,##### " << std::endl;
	std::cout << "   #############  ######            ##########=       @##########            ###### -#############  " << std::endl;
	std::cout << "     #######;     ######           X####X/.               -##/###            #####.     @######;    " << std::endl;
	std::cout << "                #                  ##                          ,#                  ##               " << std::endl;
	std::cout << "                ##               ,#####                       #####               X#;               " << std::endl;
	std::cout << "                -##         ############                     ############         ##                " << std::endl;
	std::cout << "                 ###.      #### .#  ####                     #### -#  ###       =##                 " << std::endl;
	std::cout << "                  ######/#    ## .# -#/##                     ####  #  ##   M# #####.               " << std::endl;
	std::cout << "                 :## #####    ######  ###                     ### ,######    ##### ##               " << std::endl;
	std::cout << "                M#      ##########//###.                       ;###-#%#########     X#              " << std::endl;
	std::cout << "                ##      ##############.                         ##############,      ##             \n" << std::endl;
	
	
	
	return;
}

//plays a single game to completion
void PlayGame() {
	BCGame.Reset();
	std::cout << "Chose the Length of the hidden word (3, 4, 5, 7 or 7): \n";
	Fstring StringUserWordLength = "";
	std::getline(std::cin, StringUserWordLength);
	int32 UserWordLength = 0;
	std::stringstream(StringUserWordLength) >> UserWordLength;

	BCGame.SetMyHiddenWordLength(UserWordLength);

	std::cout << "Can you guess the " << BCGame.GetHiddenWordLenght() << " letter isogram I'm thinking of?\n";
	int32 MaxTries = BCGame.GetMaxTries();
	//std::cout << MaxTries << std::endl;

	//LOOP  AKING FOR GUESSES while game is NOT won
	// and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries){
		Ftext Guess = GetValidGuess();
		
		// submit a valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << std::endl;
		std::cout << std::endl;
	}
	PrintGameSummary();
	return;
}

//loop continually into user enter a valid guess
Ftext GetValidGuess() { 
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	Ftext Guess = "";
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLenght() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			//asssume the guess is valid;
			break;
		}
		//std::cout << std::endl;
	} while (Status != EGuessStatus::OK); //keep looping until get no errors
	return Guess;
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "CONGRATULATIONS! YOU WIN!\n";
	}
	else {
		std::cout << "SORRY! BETTER LUCK NEXT TIME.\n";
	}
}

bool AksToPlayAgain() {
	std::cout << "Do you want to play again (y/n)?";
	Ftext Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;

	return bool(Response[0] == 'y') || (Response[0] == 'Y');
}
