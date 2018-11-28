/*This is the Console Executable, that makes use
of the BombShell Class. This acts as the view in a MCV Pattern, 
and is responsible for all user interactions. for game logic see the FBombShellGame Class
*/

#include <iostream>
#include <string>
#include "FBombShellGame.h"

using FText = std::string;
using int32 = int;

void introduction();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBombShellGame BCGame; //Instantiate a new game

//Entry point 
int main()
{

	bool bPlayAgain = false;
	do
	{
		
		introduction();	
		PlayGame();
		bPlayAgain = AskToPlayAgain();

	} while (bPlayAgain);
	
	

	return 0; //exits application
}




void PlayGame()
{

	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//Loop asking for guesses while the game 
	//is NOT won and there are still tries remaining.
	while( !BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries ) 	//TODO change from for to while loop once we are vallidating tries
	{
		FText Guess = GetValidGuess(); 


		//Submit valid guess to the game
		FBombShellCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bombs = " << BullCowCount.Bombs;
		std::cout << "	Shells = " << BullCowCount.Shell << std::endl;
	}

	PrintGameSummary();
	return; 
}

//loop continually until the player gives a valid guess
FText GetValidGuess() 
{
	EGuessStatus status = EGuessStatus::Invalid;

	FText Guess = "";
	do
	{
		//get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "\nTry " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your Guess: ";
		std::getline(std::cin, Guess);



		status = BCGame.CheckGuessValidity(Guess);

		switch (status)
		{
		case Not_Isogram:
			std::cout << "Please Input a Isogram. An Isogram is a word with no repeating Letters. \n\n";
			break;
		case Not_Lowercase:
			std::cout << "Please enter all lowercase Letters. \n\n";
			break;
		case Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLenght() << " letter word. \n\n";
			break;
		default:
			//assume the guess is valid
			break;
		}
	} while (status != EGuessStatus::OK); //keep looping until we have no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "DO you want to play again with the same hidden word? y/n \n";
	FText response = "";
	std::getline(std::cin, response);

	return (response[0] == 'y' || response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) 
	{
		std::cout << "WELL DONE - YOU WIN! \n";

	}
	else
	{
		std::cout << "Better luck next time! \n";
	}

	return;
}



void introduction()
{
	std::cout << "     ,--.!,       _  __________=__"		<< std::endl;
	std::cout << "   _/   -*-        \\\\@([____]_____()    " << std::endl;
	std::cout << " ,d08b.  '|`      _/\\|-[____]    "		<< std::endl;
	std::cout << " 0088MM          /     /(( )      "		<< std::endl;
	std::cout << " `9MMP'         /____|'----'  "			<< std::endl;
	std::cout << "                \\____/        "			<< std::endl;
	std::cout << "Welcome to Bomb Shell, a fun and enfuriating word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLenght();
	std::cout << " letter Isogram I'm thinking of?\n\n\n";

	std::cout << "Bombs are correct Letters in the correct Position.\n";
	std::cout << "Shells are correct Letters in the wrong Position.\n";
	return;
}
