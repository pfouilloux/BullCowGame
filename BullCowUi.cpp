#include "BullCowUi.h"

#include <iostream>
#include <map>
#include <sstream>

#include "BullCowGame.h"
#include "Nullable.h"

// to make syntax Unreal friendly
#define TMap std::map

using int32 = int;

// to make syntax Unreal friendly
using FText = std::string;
using FString = std::string;

enum class EGuessStatus {
	InvalidStatus,
	Ok,
	NotIsogram,
	NotLowercase,
	WrongLength
};

enum class EWordLengthStatus {
	InvalidStatus,
	Ok,
	TooLow,
	TooHigh
};

void FBullCowUi::PrintIntro() const
{
	std::cout << std::endl << std::endl;
	std::cout << "*********************************************************" << std::endl;
	std::cout << "*                                                       *" << std::endl;
	std::cout << "*       ,/          \\,           /             \\        *" << std::endl;
	std::cout << "*      ((__,-ooo-,__))          ((__-^^-,-^^-__))       *" << std::endl;
	std::cout << "*       `--)~   ~(--`            `-_---' `---_-'        *" << std::endl;
	std::cout << "*      .-'(       )`-,            <__|o` 'o|__>         *" << std::endl;
	std::cout << "*      `~~`0|   |0`~~`               \\  `  /            *" << std::endl;
	std::cout << "*          |     |                    ): :(             *" << std::endl;
	std::cout << "*          (o___o)                    :o_o:             *" << std::endl;
	std::cout << "*           `---`                      '-'              *" << std::endl;
	std::cout << "*                    BULLS & COWS                       *" << std::endl;
	std::cout << "*                                                       *" << std::endl;
	std::cout << "*********************************************************" << std::endl;
	std::cout << std::endl;
	std::cout << "Welcome to Bulls & Cows!" << std::endl;
}

uint8 FBullCowUi::PromptForWordLength() const
{
	constexpr char *prompt = "Please select a word length between 3 and 7: ";

	uint8 WordLength;
	EWordLengthStatus Status;
	do
	{
		WordLength = PromptForUInt8(prompt);
		Status = CheckWordLengthValidity(WordLength);
		switch (Status)
		{
		case EWordLengthStatus::TooLow:
			std::cout << "Please enter a number higher or equal to 3." << std::endl << std::endl;
			break;
		case EWordLengthStatus::TooHigh:
			std::cout << "Please enter a number lower or equal to 7." << std::endl << std::endl;
			break;
		}
	} while (Status != EWordLengthStatus::Ok);

	return WordLength;
}

void FBullCowUi::PrintChallenge(const uint32 WordLength) const
{
	std::cout << "Can you guess the " << WordLength << " letter isogram I'm thinking of? " << std::endl << std::endl;
}

FString FBullCowUi::GetValidGuess(const FBullCowGame& Game) const
{
	constexpr char * prompt = "Enter your guess : ";
	auto CurrentTry = Game.GetCurrentTry();

	std::stringstream PromptMessage;
	PromptMessage << "Try " << CurrentTry << " of " << Game.GetMaxTries() << " - " << prompt;

	FString Guess;
	EGuessStatus Status = EGuessStatus::InvalidStatus;
	do
	{
		Guess = PromptForLine(PromptMessage.str().c_str());
		Status = CheckGuessValidity(Game, Guess);
		switch (Status)
		{
		case EGuessStatus::NotIsogram:
			std::cout << "Please enter an isogram." << std::endl << "Note: An Isogram is a word with no repeated letters." << std::endl << std::endl;
			break;
		case EGuessStatus::NotLowercase:
			std::cout << "Please enter lowercase characters only." << std::endl << std::endl;
			break;
		case EGuessStatus::WrongLength:
			std::cout << "Please enter a " << Game.GetHiddenWordLength() << " letter word." << std::endl << std::endl;
			break;
		}
	} while (Status != EGuessStatus::Ok);

	return Guess;
}

void FBullCowUi::PrintGuess(const FText guess) const
{
	std::cout << "You guessed : " << guess << std::endl;
}

void FBullCowUi::PrintBullCowCount(const FBullCowCount& BullCowCount) const
{
	std::cout << "Bulls = " << BullCowCount.Bulls << ". Cows = " << BullCowCount.Cows << std::endl << std::endl;
}

void FBullCowUi::PrintGameSummary(const FBullCowGame & Game) const
{
	if(Game.IsGameWon())
	{
		std::cout << "You won! Well done!" << std::endl;
	}
	else
	{
		std::cout << "You lost... Please try again." << std::endl;
	} 

	std::cout << std::endl;
}

bool FBullCowUi::PromptToPlayAgain() const
{
	constexpr auto QuestionPrompt = "Would you like to play again (y/n)? ";
	constexpr auto ErrorPrompt = "Invalid response. Please try again.";

	auto Result = PromptYesNo(QuestionPrompt);
	while (!Result.HasValue())
	{
		std::cout << ErrorPrompt << std::endl << std::endl;
		Result = PromptYesNo(QuestionPrompt);
	}

	std::cout << std::endl;
	return Result.Get();
}

uint8 FBullCowUi::PromptForUInt8(const FText Prompt) const
{
	FString Response;
	do  
	{
		Response = PromptForLine(Prompt);
	} while (!IsNumber(Response));

	return atoi(Response.c_str());
}

FString FBullCowUi::PromptForLine(const FText Prompt) const
{
	std::cout << Prompt;
	FString Response = "";
	getline(std::cin, Response);
	return Response;
}

EWordLengthStatus FBullCowUi::CheckWordLengthValidity(const uint8 WordLength) const
{
	const uint8 MinWordLen = 3;
	const uint8 MaxWordLen = 7;

	if (WordLength < MinWordLen) 
	{
		return EWordLengthStatus::TooLow;
	} 
	else if (WordLength > MaxWordLen)
	{
		return EWordLengthStatus::TooHigh;
	}
	else
	{
		return EWordLengthStatus::Ok;
	}
}

EGuessStatus FBullCowUi::CheckGuessValidity(const FBullCowGame& Game, const FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::NotIsogram;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::NotLowercase;
	}
	else if (Guess.length() != Game.GetHiddenWordLength())
	{
		return EGuessStatus::WrongLength;
	}
	else
	{
		return EGuessStatus::Ok;
	}
}

Nullable<bool> FBullCowUi::PromptYesNo(const FText Prompt) const
{
	Nullable<bool> Result;

	auto Input = PromptForLine(Prompt.c_str());
	if (Input[0] == 'y' || Input[0] == 'Y') 
	{ 
		Result = true; 
	}
	else if (Input[0] == 'n' || Input[0] == 'N') 
	{ 
		Result = false; 
	}

	return Result;
}

bool FBullCowUi::IsIsogram(const FText Word) const
{
	TMap<char, bool> LettersSeen;
	
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LettersSeen[Letter]) {
			return false;
		}

		LettersSeen[Letter] = true;
	}
		
	return true;
}

bool FBullCowUi::IsLowercase(const FText Word) const
{
	for (auto Letter : Word) 
	{
		if (!islower(Letter)) { return false; }
	}

	return true;
}

bool FBullCowUi::IsNumber(const FString Candidate) const
{
	for (auto Character : Candidate) {
		if (!isdigit(Character)) { return false; }
	}

	return true;
}
