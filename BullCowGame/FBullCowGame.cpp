#pragma once
#include "FBullCowGame.h"
#include <map>

//to make Unreal friendly
#define TMap std::map 
using int32 = int;

FBullCowGame::FBullCowGame() {//constructor
	Reset();
}

int32 FBullCowGame::GetCurrentTry() const{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLenght() const {
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const{
	return bGameIsWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(Fstring Guess) const {
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess)) {
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLenght()) {
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::OK;
	}
}

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ {3, 6}, {4, 9}, {5, 12}, {6, 15}, {7, 19} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
	//return MyMaxTries;
}

void FBullCowGame::Reset() {

	
	const Fstring HIDDEN_WORD = "";

	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;

	bGameIsWon = false;
	return;
}

FBullCowCount FBullCowGame::SubmitValidGuess(Fstring Guess){
	
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	
	int32 WordLength = MyHiddenWord.length();//assuming same length as guess

	//loop through all letters in the hidden word 
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		//compare letters against the hidden words

		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {//if they match then
				
				if (MHWChar == GChar) { //if they're in the same place
					//increment bulls 
					BullCowCount.Bulls++;
				}
				else { //if not in same place
					//increment cow if not
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(Fstring Word) const {
	//treat 0 and 1 letters words as isograms
	if (Word.length() <= 1) {
		return true;
	}

	TMap<char, bool> LetterSeen;

	for (auto Letter : Word) {  //for all 
		Letter = tolower(Letter);

		if (LetterSeen[Letter]) {
			return false;//not Isogram
		}
		else {
			LetterSeen[Letter] = true;
		}
	}
			
	return true;
}

bool FBullCowGame::IsLowerCase(Fstring Word) const{
	TMap<char, bool> LetterSeen;

	for (auto Letter : Word) {
		if (islower(Letter)) {
			LetterSeen[Letter] = true;
		}
		else {
			return false;
		}
	}

	return true;
}

void FBullCowGame::SetMyHiddenWordLength(int32 UserWordLength){
	TMap<int32, Fstring> WichWordLength{ { 3, "opa" },{ 4, "pula" },{ 5, "chuta" },{ 6, "brincar" },{ 7, "escutar" } };
	MyHiddenWord = WichWordLength[UserWordLength];
}
