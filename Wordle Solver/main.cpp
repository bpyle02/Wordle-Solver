//Wordle Bot Created by Brandon Pyle

#include "WordleSolver.h"

#include <iostream>
#include <vector>

using namespace std;

int main()
{
	WordleSolver wordleBot;

	wordleBot.setWordle();

	while (!wordleBot.getGameWon() && wordleBot.getGuessNum() < 6)
	{
		if (wordleBot.getGuessNum() == 0)
			wordleBot.makeGuess("slate");
		else
			wordleBot.makeGuess();

		wordleBot.eliminateWords();
		wordleBot.gameOver();
	}

	if (wordleBot.getGameWon())
		cout << "Congratulations, you guessed the wordle!" << endl << endl;
	else
	{
		cout << "Oops, better luck next time!" << endl << endl;
	}

	return 0;
}