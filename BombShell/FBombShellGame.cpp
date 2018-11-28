#include "FBombShellGame.h"
#include <map>
#include <random>
#include <chrono> //required for seed for randomizer
#define TMap std::map

using FString = std::string;
using int32 = int;

FBombShellGame::FBombShellGame() { Reset(); } // default constructor




int32 FBombShellGame::GetCurrentTry() const{ return MyCurrentTry; }

int32 FBombShellGame::GetHiddenWordLenght() const { return MyHiddenWord.length(); }

bool FBombShellGame::IsGameWon() const { return bGameIsWon; }

int32 FBombShellGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordlenghtToMaxTrie{ {3,7}, {4,10}, {5,13}, {6,19}, {7,20} };
	
	return WordlenghtToMaxTrie[MyHiddenWord.length()]; 
}

void FBombShellGame::Reset()
{
	

	MyHiddenWord = CreateHiddenWord();
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}


EGuessStatus FBombShellGame::CheckGuessValidity(FString GuessedWord) const
{
	
	if (!IsIsogram(GuessedWord))  //if the guess isnt an isogram TODO write function
	{ 
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(GuessedWord))	//if the game isnt lowercase  TODO write function
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (GuessedWord.length() != GetHiddenWordLenght()) //if the guess lenght is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else 	//otherwise return okay
	{
		return EGuessStatus::OK;
	}

	





	return EGuessStatus::Not_Isogram;
}


//receives a valid guess, increments turn, and returns count
FBombShellCount FBombShellGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBombShellCount FBombShellCount;

	//loop through all letters in the >Hidden word 
	int32 WordLenght = MyHiddenWord.length(); //assuming same length as guess
	for (int32 HWChar = 0; HWChar < WordLenght ; HWChar++)
	{
		//compare letters against guess
		for (int32 GChar = 0; GChar < WordLenght; GChar++) 
		{
			//if they match then
			if (Guess[HWChar] == MyHiddenWord[GChar]) { //if they match then
				if (HWChar == GChar)	{ //if the two letters are in the same place increment bombs
					FBombShellCount.Bombs++;
				}
				else { //increment Shells if they are not
					FBombShellCount.Shell++;
				}
			}
		}
	}
		
	if(FBombShellCount.Bombs == GetHiddenWordLenght())
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}

	return FBombShellCount;
}

bool FBombShellGame::IsIsogram(FString GuessedWord) const
{
	//treat 0 and 1 letter words as isograms
	if (GuessedWord.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;//Setup our map
	for(auto Letter : GuessedWord)	//for all letters of the word
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) //if the letter is in the map
		{
			return false;	//we do NOT have an isogram
		}
		else
		{
			LetterSeen[Letter] = true; //add the letter to the map as seen
		}
			

	}

	return true; // for example in cases where /0 is entered
}

bool FBombShellGame::IsLowercase(FString GuessedWord) const
{

	for (auto Char : GuessedWord) 
	{
		if (!islower(Char)) //if not a lowercase letter
		{
			return false;
		}
		else //otherwise if it is a lowercase
		{
			return true;
		}

	}


	return false;
}

FString FBombShellGame::CreateHiddenWord()
{
	const int32 arrayLength = 31;
	FString isogramArray[arrayLength] = { "ant", "key", "one", "shoe", "claw", "star", "plant", "bread", "phone", "planet", "smoker", "chains", "gay","ape","donkey", "jackbox", "human", "dwarfs", "jumpy", "brick", "house", "jordans", "dumbing", "whoring", "overfly", "yes", "nope", "why", "think", "jump","tricks",  };

	// construct a time based seed
	int32 seed = std::chrono::system_clock::now().time_since_epoch().count();

	// pick a random string from the array
	std::default_random_engine generator(seed); // use the seed to avoid getting same result every time.
	std::uniform_int_distribution<int32> distribution(0, arrayLength - 1);
	int32 stringIndex = distribution(generator); // generates number in the distribution range
	FString isogram = isogramArray[stringIndex];
	return isogram;
}
