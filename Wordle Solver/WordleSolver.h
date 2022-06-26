#pragma once

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <random>

using namespace std;

class WordleSolver
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	vector<string> possibleAnswers;
	vector<string> possibleGuesses;
	vector<string> remainingPossibleGuesses;

	vector<pair<string, int>> words;
	vector<vector<int>> charFreq;

	vector<char> grey;
	vector<pair<char, int>> yelloww;
	char yellowLetters[5];
	char green[5];

	string wordle;
	string guess;
	char guessResults[5];
	int guessNum = 0;
	bool isGameOver = false;
	bool gameWon = false;

	//Helper Functions
	string getRandomWordle();
	void resetVals();

public:
	//Constructor
	WordleSolver();

	//Initializers
	void getWordList();
	void initFrequency();
	void getWordScore();
	void getWordScore(string fileName);
	void setWordle(string w = "");

	//Game Mechanics
	string getBestGuess();
	void makeGuess(string guess = "");
	void getGuessResults();
	void eliminateWords();
	void updateFrequency();
	void gameOver();

	//Print Functions
	void printFrequency();
	void printWordsWithFreq();
	void printGuessResults();

	//Getters
	bool getGameWon();
	int getGuessNum();
};