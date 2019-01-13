#include "BullCowGame.h"
#include "BullCowUi.h"

using int32 = int;

// to make syntax Unreal friendly
using FText = std::string;
using FString = std::string;

static void PlayGame(FBullCowGame& Game, FBullCowUi& Ui);

int main()
{
	FBullCowGame Game;
	FBullCowUi Ui;
	
	do
	{
		Ui.PrintIntro();
		auto WordLength = Ui.PromptForWordLength();
		Game.StartNewGame(WordLength);
		Ui.PrintChallenge(WordLength);
		PlayGame(Game, Ui);
		Ui.PrintGameSummary(Game);
	} 
	while (Ui.PromptToPlayAgain());

	return 0;
}

static void PlayGame(FBullCowGame& Game, FBullCowUi& Ui)
{
	while (!Game.IsGameWon() && Game.GetCurrentTry() <= Game.GetMaxTries())
	{
		const auto Guess = Ui.GetValidGuess(Game);
		FBullCowCount BullCowCount = Game.SubmitValidGuess(Guess);
		Ui.PrintGuess(Guess);
		Ui.PrintBullCowCount(BullCowCount);
	}
}