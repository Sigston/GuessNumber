// TODO:
//		- Implement a wider range of numbers for different difficulty levels.
//		- Fix the scoreboard feature (store the scoreboard in memory as a data structure
//			at the beginning of the program and have a function for writing this
//			structure to file - makes changing the structure much easier)
//		- Implement a settings option from the menu

#include <string>
#include <time.h>
#include <algorithm>
#include <ctype.h>
#include "InputValidate.h"	
#include "Drawer.h"
#include "FileReader.h"

void PlayGame(int SecretNumber, Drawer &drawer);
int GetDifficultyLevel(Drawer &drawer);
int SetNumberOfGuesses(int DifficultyLevel);
bool Menu(Drawer &drawer);
void Introduction(Drawer &drawer);
void PrintRules(Drawer &drawer);
void PrintLeaderBoard(Drawer &drawer);
void ValidInputChar(char &OutputChar, std::string ErrorMessage);
void ValidInputInt(int &OutputInt, std::string ErrorMessage);
void PrintLeaderBoard(Drawer &drawer);
void UpdateLeaderBoard(int DifficultyLevel, int Guesses, std::string Name);
bool IsHighScore(int DifficultyLevel, int Guesses);

const unsigned int SCREEN_SPACE = 70;
const unsigned int PADDING = 3;
const char SCREEN_CHARACTER = '|';
const std::string USER_PROMPT = "|   : ";

int main()
{
	// Seed the random number generator with the current time.
	srand((unsigned int)time(NULL));
	Drawer drawer(SCREEN_SPACE, PADDING, SCREEN_CHARACTER, USER_PROMPT);

	// Welcome to player
	Introduction(drawer);

	// Begin the main game loop.
	bool Playing = Menu(drawer);
	while (Playing)
	{
		// Generate a new random number and plug it into the game.
		int SecretNumber = rand() % 10 + 1;
		PlayGame(SecretNumber, drawer);
		Playing = Menu(drawer);
	}
	return(0);
}

// Contains the main game logic.
void PlayGame(int SecretNumber, Drawer &drawer)
{
	// Get a difficulty level and set the number of allowed guesses.
	int DifficultyLevel = GetDifficultyLevel(drawer);
	int GuessesAllowed = SetNumberOfGuesses(DifficultyLevel);

	// Takes guesses from the player until they run out of guesses or get the secret number
	int NumberOfGuesses = 0;
	int Guess = 0;
	while (GuessesAllowed != 0)
	{
		Guess = 0;
		while(Guess < 1 || Guess > 10)
		{
			drawer.DrawBlankLine();
			drawer.DrawSeperator();
			drawer.DrawBlankLine();
			drawer.DrawText("You have " + std::to_string(GuessesAllowed) + " guesses remaining.");
			drawer.DrawUserPrompt();
			ValidInputInt(Guess, USER_PROMPT);
		}
		--GuessesAllowed;
		++NumberOfGuesses;

		if (Guess > SecretNumber)
		{
			drawer.DrawBlankLine();
			drawer.DrawText("Your guess was too high.");
		}
		else if (Guess < SecretNumber)
		{
			drawer.DrawBlankLine();
			drawer.DrawText("Your guess was too low.");
		}
		else if (Guess == SecretNumber)
			break;
	}

	// Check for victory or failure, update Leaderboard if necessary.
	if (Guess == SecretNumber)
	{
		drawer.DrawSeperator();
		drawer.DrawBlankLine();
		drawer.DrawText("Congratulations! I was thinking of the number " + std::to_string(SecretNumber) + ".");
		drawer.DrawBlankLine();
		if (IsHighScore(DifficultyLevel, NumberOfGuesses))
		{
			std::string Name;
			drawer.DrawText("You have made it on to the Leaderboard! Please enter your three-character initials.");
			while (Name.length() != 3)
			{
				drawer.DrawUserPrompt();
				ValidInputStr(Name, USER_PROMPT);
			}
			std::transform(Name.begin(), Name.end(), Name.begin(), ::toupper);
			UpdateLeaderBoard(DifficultyLevel, NumberOfGuesses, Name);
			drawer.DrawBlankLine();
		}
	}
	else
	{
		drawer.DrawSeperator();
		drawer.DrawBlankLine();
		drawer.DrawText("You ran out of guesses! Better luck next time!");
		drawer.DrawBlankLine();
	}
	if (NumberOfGuesses == 1)
		drawer.DrawText("You took " + std::to_string(NumberOfGuesses) + " guess!");
	else
		drawer.DrawText("You took " + std::to_string(NumberOfGuesses) + " guesses!");
	drawer.DrawBlankLine();
	drawer.DrawSeperator();
}

// Returns the desired difficulty level from the player.
int GetDifficultyLevel(Drawer &drawer)
{
	drawer.DrawBlankLine();
	drawer.DrawSeperator();
	drawer.DrawBlankLine();
	drawer.DrawText("Please choose a difficulty: (1) Easy, (2) Medium, (3) Hard.");
	int DifficultyLevel = 0;
	while (DifficultyLevel < 1 || DifficultyLevel > 3)
	{
		drawer.DrawUserPrompt();
		ValidInputInt(DifficultyLevel, USER_PROMPT);
	}
	return(DifficultyLevel);
}
// Returns the number of guesses allowed for that difficulty level.
int SetNumberOfGuesses(int DifficultyLevel)
{
	int NumberOfGuesses;
	switch (DifficultyLevel)
	{
	case 1:
		NumberOfGuesses = 6;
		break;
	case 2:
		NumberOfGuesses = 4;
		break;
	case 3:
		NumberOfGuesses = 3;
		break;
	default:
		NumberOfGuesses = 6;
		break;
	}
	return(NumberOfGuesses);
}

// Runs the menu; returns true if the player wants to play and false if they want to exit the application. 
// Calls PrintRules() and PrintLeaderBoard()
bool Menu(Drawer &drawer)
{	
	int Decision = 0;
	bool PlayGame;

	while (true)
	{
		drawer.DrawBlankLine();
		drawer.DrawText("Would you like to (1) play a game, (2) see the rules, (3) see the leaderboard, or "
			"(4) quit the game?");

		// Get a valid decision
		while (Decision < 1 || Decision > 4)
		{
			drawer.DrawUserPrompt();
			ValidInputInt(Decision, USER_PROMPT);
		}

		// Do the right thing
		switch (Decision)
		{
		case 4:
			PlayGame = false;
			break;
		case 3:
			PrintLeaderBoard(drawer);
			break;
		case 2:
			PrintRules(drawer);
			break;
		case 1:
			PlayGame = true;
			break;
		}
		if (Decision == 1 || Decision == 4)
			break;
		Decision = 0;
	}
	return(PlayGame);
}

/*
	PRINTING FUNCTIONS
*/
// Prints the introduction.
void Introduction(Drawer &drawer)
{
	drawer.DrawSeperator();
	drawer.DrawBlankLine();
	drawer.DrawCentralLine("GUESS THE NUMBER");
	drawer.DrawBlankLine();
	drawer.DrawSeperator();
	drawer.DrawBlankLine();
	drawer.DrawCentralLine("Welcome to Guess The Number!!!");
	drawer.DrawBlankLine();
	drawer.DrawBlankLine();
	drawer.DrawCentralLine("A Game By Alex Sigston");
	drawer.DrawBlankLine();
	drawer.DrawSeperator();
}
// Prints the rules
void PrintRules(Drawer &drawer)
{
	drawer.DrawSeperator();
	drawer.DrawBlankLine();
	drawer.DrawText("I am thinking of a number between 1 and 10. Can you guess what it is? " 
		"I will tell you whether your guess is too high or too low. The difficulty level " 
		"sets how many guesses you have. Easy (1) is 6 guesses, Medium (2) is 4 guesses " 
		"and Hard (3) is 3 guesses. If you guess the number with a low number of guesses, " 
		"you might make it on to the leaderboard!");
	drawer.DrawBlankLine();
	drawer.DrawCentralLine("HAVE FUN!!!");
	drawer.DrawBlankLine();
	drawer.DrawSeperator();
}
// Prints the Leader Board
void PrintLeaderBoard(Drawer &drawer)
{
	std::string Text = GetFileText("Scoreboard.txt");
	std::string Output;
	for (auto it = Text.begin(); it != Text.end(); ++it)
	{
		if (*it == '@')
		{
			Output.append(":\n      ");
		}
		else if (*it == ',')
		{
			Output.append("\n      ");
		}
		else
		{
			Output.append(1, *it);
		}
	}
	drawer.DrawSeperator();
	drawer.DrawBlankLine();
	drawer.DrawMultiLineText(Output);
	drawer.DrawBlankLine();
	drawer.DrawSeperator();
}

/*
	LEADERBOARD FUNCTIONS
*/
// Given the difficulty level, number of guesses taken and a name, updates the Leader Board.
void UpdateLeaderBoard(int DifficultyLevel, int Guesses, std::string Name)
{
	// Get the LeaderBoard data from file.
	std::string File = GetFileText("Scoreboard.txt");
	std::string DifficultyName;
	if (DifficultyLevel == 1)
		DifficultyName = "Easy";
	if (DifficultyLevel == 2)
		DifficultyName = "Medium";
	if (DifficultyLevel == 3)
		DifficultyName = "Hard";
	std::size_t DifficultyPos = File.find(DifficultyName);

	std::string::iterator it = File.begin() + DifficultyPos;
	for (; *it != '\n'; ++it)
	{
		if (isdigit(*it))
		{
			if (*it > Guesses)
			{
				std::string GuessesStr = std::to_string(Guesses);
				*it = GuessesStr[0];
				File.replace(it - 4, it - 1, Name.begin(), Name.end());
				break;
			}
		}
	}

	// Put this new file back into the file
	UpdateFile("Scoreboard.txt", File);
}
// Checks if the given DifficultyLevel and Guess number is a highscore.
bool IsHighScore(int DifficultyLevel, int Guesses)
{
	// Get the LeaderBoard data from file.
	std::string File = GetFileText("Scoreboard.txt");
	std::string DifficultyName;
	if (DifficultyLevel == 1)
		DifficultyName = "Easy";
	if (DifficultyLevel == 2)
		DifficultyName = "Medium";
	if (DifficultyLevel == 3)
		DifficultyName = "Hard";
	std::size_t DifficultyPos = File.find(DifficultyName);

	std::string::iterator it = File.begin() + DifficultyPos;
	for (; *it != '\n'; ++it)
	{
		if (isdigit(*it))
		{
			if (*it > Guesses)
				return true;
		}
	}

	// Nothing has been found, guesses is not a High Score.
	return false;
}
