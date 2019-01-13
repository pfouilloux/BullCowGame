#pragma once

#include "Nullable.h"

#include <string>

class FBullCowGame;
enum class EGuessStatus;
enum class EWordLengthStatus;

using uint8 = unsigned char;
using uint32 = unsigned int;

using FText = std::string;
using FString = std::string;

class FBullCowUi
{
public:
	void PrintIntro() const;
	uint8 PromptForWordLength() const;
	void PrintChallenge(const uint32 WordLength) const;
	std::string GetValidGuess(const FBullCowGame& Game) const;
	void PrintGuess(const FText Guess) const;
	void PrintBullCowCount(const FBullCowCount& BullCowCount) const;
	void PrintGameSummary(const FBullCowGame& Game) const;	
	bool PromptToPlayAgain() const;

private:
	uint8 PromptForUInt8(const FText Prompt) const;
	std::string PromptForLine(const FText Prompt) const;
	EWordLengthStatus CheckWordLengthValidity(const uint8 WordLength) const;
	EGuessStatus CheckGuessValidity(const FBullCowGame& Game, const FString Guess) const;
	Nullable<bool> PromptYesNo(const FText Prompt) const;
	bool IsIsogram(const FText Word) const;
	bool IsLowercase(const FText Word) const;
	bool IsNumber(const FString Candidate) const;
};
