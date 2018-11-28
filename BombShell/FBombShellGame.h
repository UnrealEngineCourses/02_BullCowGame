#pragma once
#include <string>

using FString = std::string;
using int32 = int;

//all values initialised to zero
struct FBombShellCount
{
	int32 Bombs = 0;
	int32 Shell = 0;

};

enum  EGuessStatus
{
	Invalid,
	OK, 
	Not_Isogram,
	Not_Lowercase,
	Wrong_Length,

};

class FBombShellGame

{
public:
	FBombShellGame(); //Constructor
	
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLenght() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString GuessedWord) const; //TODO make a more rich return value

	void Reset();  //TODO make a more rich return value 
	FBombShellCount SubmitValidGuess(FString Guess);

private:
	bool IsIsogram(FString GuessedWord) const;
	bool IsLowercase(FString GuessedWord) const;
	FString CreateHiddenWord();

	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
};
