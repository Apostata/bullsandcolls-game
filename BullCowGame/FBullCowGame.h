/*
The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/
#pragma once
#include <string>

//to make sintax Unreal Friendly
using Fstring = std::string;
using int32 = int;

//two values initialisade to 0
struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

/*enum class EResetStatus {
	OK,
	No_Hidden_Word
};*/

class FBullCowGame {
	
public:
	FBullCowGame();//constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLenght() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(Fstring) const; 
	FBullCowCount SubmitValidGuess(Fstring);
	void SetMyHiddenWordLength(int32);
	void Reset();
		
private:
	int32 MyCurrentTry;
	Fstring MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(Fstring) const;
	bool IsLowerCase(Fstring) const;
};
