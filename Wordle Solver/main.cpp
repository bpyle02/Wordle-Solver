//Wordle Bot Created by Brandon Pyle

#include "WordleSolver.h"

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main()
{
	WordleSolver wordleBot;
	int input = 0;

	while (input != 3)
	{
		cout << "Welcome to Wordle Solver! Enter your choice:" << endl;
		cout << "1. Play wordle yourself" << endl;
		cout << "2. Let the computer play" << endl;
		cout << "3. Exit" << endl;

		cin >> input;

		cout << endl;

		if (input == 1)
		{
			wordleBot.setWordle();

			while (!wordleBot.getGameWon() && wordleBot.getGuessNum() < 6)
			{
				string myGuess;

				cout << "Make a guess: ";
				cin >> myGuess;

				wordleBot.makeGuess(myGuess);
				wordleBot.gameOver();

			}

			if (wordleBot.getGameWon())
				cout << "Congratulations, you guessed the wordle!" << endl << endl;
			else
			{
				cout << "Oops, better luck next time! The wordle was " << wordleBot.getWordle() << endl << endl;
			}
		}
		else if (input == 2)
		{
			wordleBot.resetVals();

			int m_input = 0;
			string myWordle = "";

			cout << "Enter the number of your choice:" << endl;
			cout << "1. pick a wordle for the computer to guess" << endl;
			cout << "2. let the computer guess a random wordle" << endl;
			cout << "3. run a simulation of a certain number of wordle games" << endl;

			cin >> m_input;

			cout << endl;

			if (m_input == 1)
			{
				cout << "Enter your wordle for the computer to guess: ";

				cin >> myWordle;

				cout << endl;

				wordleBot.setWordle(myWordle);

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
					cout << "Oops, better luck next time! The wordle was " << wordleBot.getWordle() << endl << endl;
				}

			}
			else if (m_input == 2)
			{
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
					cout << "Oops, better luck next time! The wordle was " << wordleBot.getWordle() << endl << endl;
				}
			}
			else if (m_input == 3)
			{
				int numSimulations;
				int totalSimulations;
				double avg;
				int guessTotal = 0;
				int guesses[7]{ 0 };

				cout << "How many games would you like to simulate? ";
				cin >> numSimulations;
				totalSimulations = numSimulations;

				cout << endl << endl;

				while (numSimulations > 0)
				{
					wordleBot.setWordle();

					while (!wordleBot.getGameWon() && wordleBot.getGuessNum() < 6)
					{
						//if (wordleBot.getGuessNum() == 0)
						//	wordleBot.makeGuess("slate");
						//else
						wordleBot.makeGuess();

						wordleBot.eliminateWords();
						wordleBot.gameOver();
					}

					if (wordleBot.getGameWon())
					{
						cout << "Congratulations, you guessed the wordle!" << endl << endl;
						guesses[wordleBot.getGuessNum() - 1] += 1;
					}
					else
					{
						cout << "Oops, better luck next time! The wordle was " << wordleBot.getWordle() << endl << endl;
						guesses[6] += 1;
					}

					guessTotal += wordleBot.getGuessNum();

					wordleBot.resetVals();

					numSimulations--;
				}

				avg = ((1.0 * guesses[0]) + (2.0 * guesses[1]) + (3.0 * guesses[2]) + (4.0 * guesses[3]) + (5.0 * guesses[4]) + (6.0 * guesses[5])) / (totalSimulations - guesses[6]);

				cout << "Wordle Solver guessed the wordle in " << setprecision(2) << avg << " guesses on average (excluding failed attempts)" << endl << endl;
				cout << "Guess Spread:" << endl;
				cout << "1: " << guesses[0] << endl;
				cout << "2: " << guesses[1] << endl;
				cout << "3: " << guesses[2] << endl;
				cout << "4: " << guesses[3] << endl;
				cout << "5: " << guesses[4] << endl;
				cout << "6: " << guesses[5] << endl;
				cout << "X: " << guesses[6] << endl;
			} 
			else
			{
			cout << "Input error, program will now close." << endl;
			}

		}
		else if (input == 3)
		{
			cout << "Closing the program..." << endl;
		}
		else
		{
			cout << "Incorrect input, please restart the program." << endl;
		}
	}

	return 0;
}