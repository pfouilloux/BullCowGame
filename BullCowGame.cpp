#include "BullCowGame.h"

#include <map>

// to make syntax Unreal friendly
#define TMap std::map

void FBullCowGame::StartNewGame(uint8 HiddenWordLength)
{
	TMap<uint8, std::string> WordsByLength{ {3, "ant"}, {4, "four"}, {5, "alive"}, {6, "planet"}, {7, "planter"} };

	HiddenWord = WordsByLength[HiddenWordLength];
	CurrentTry = 1;
	bGameIsWon = false;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	CurrentTry++;
	FBullCowCount BullCowCount;
	const auto WordLength = HiddenWord.length(); // we assume that guess has same length

	for(uint32 GCharPos = 0; GCharPos < WordLength; GCharPos++)
	{
		auto Matched = false;
		for(uint32 HWCharPos = 0; HWCharPos < WordLength && !Matched; HWCharPos++)
		{
			Matched = Guess[GCharPos] == HiddenWord[HWCharPos];

			if(Matched && GCharPos == HWCharPos)
			{
				BullCowCount.Bulls++;
			}
			else if(Matched)
			{
				BullCowCount.Cows++;
			}
		}
	}
	
	bGameIsWon = BullCowCount.Bulls == WordLength;
	return BullCowCount;
}

uint32 FBullCowGame::GetMaxTries() const
{
	TMap<uint8, uint32> WordLengthToTries{ {3,6}, {4,8}, {5, 10}, {6,12}, {7,14} };
	return WordLengthToTries[GetHiddenWordLength()];
}

uint32 FBullCowGame::GetCurrentTry() const { return CurrentTry; }
uint32 FBullCowGame::GetHiddenWordLength() const { return HiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }
