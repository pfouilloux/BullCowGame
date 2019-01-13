#pragma once

#include <string>

using uint8 = unsigned char;
using uint32 = unsigned int;

using FText = std::string;
using FString = std::string;

struct FBullCowCount
{
	uint8 Bulls = 0;
	uint8 Cows = 0;
};

class FBullCowGame
{
public:			
	void StartNewGame(uint8 HiddenWordLength);
	FBullCowCount SubmitValidGuess(FString Guess);
	uint32 GetMaxTries() const;

	uint32 GetCurrentTry() const;
	uint32 GetHiddenWordLength() const;
	bool IsGameWon() const;
private:
	uint32 CurrentTry;
	FString HiddenWord;
	bool bGameIsWon;
};
