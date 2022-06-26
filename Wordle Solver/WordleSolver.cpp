#include "WordleSolver.h"

bool sortWords(const pair<string, int>& a, const pair<string, int>& b)
{
	return (a.second < b.second);
}

WordleSolver::WordleSolver() : charFreq(26)
{
	guess = "";

	for (int i = 0; i < 26; i++)
		charFreq[i] = { 0, 0, 0, 0, 0 };

	for (int i = 0; i < 5; i++)
	{
		green[i] = '0';
	}

	getWordList();
	getWordScore("possibleWordleGuessesWithFrequencies.txt");
}

void WordleSolver::getWordList()
{
	ifstream fin;
	string word;

	cout << "Loading word list..." << endl;

	fin.open("officialWords.txt");

	while (fin)
	{
		getline(fin, word);
		possibleAnswers.push_back(word);
		remainingPossibleGuesses.push_back(word);
	}

	fin.close();

	fin.open("allWords.txt");

	while (fin)
	{
		getline(fin, word);
		possibleGuesses.push_back(word);
	}

	fin.close();

	cout << "Word list successfully loaded!" << endl << endl;
}

void WordleSolver::initFrequency()
{
	cout << "Initializing letter frequency list..." << endl;

	//Initialize letterFreq map
	for (const auto &i : possibleAnswers) //Loop through every possible word
	{
		for (int j = 0; j < 5; j++) //Loop through every letter of every word
		{
			char c = i[j];
			int pos = c - 97;

			charFreq[pos][j] += 1;
		}
	}

	cout << "Letter frequency list successfully initiailized!" << endl << endl;
}

void WordleSolver::printFrequency()
{
	char letter = 'a';

	for (const auto &i : charFreq)
	{
		cout << letter << " frequency: [";

		for (int j = 0; j < 5; j++)
		{
			if (j < 4)
				cout << i[j] << ", ";
			else
				cout << i[j] << "]" << endl;
		}

		letter++;
	}

	cout << endl;
}

void WordleSolver::getWordScore()
{
	int maxFreq[5]{ 0 };

	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (maxFreq[j] < charFreq[i][j])
				maxFreq[j] = charFreq[i][j];
		}
	}

	for (const auto &i : remainingPossibleGuesses)
	{
		int score = 1;
		string word = i;

		for (int j = 0; j < 5; j++)
		{
			char c = word[j] - 97;
			
			//if (word == "slice" || word == "slate")
			//	cout << word << " score = " << score << " + " << maxFreq[j] << " - " << charFreq[c][j] << endl;
				//cout << word << " score = " << score << " * 1 + (" << maxFreq[j] << " - " << charFreq[c][j] << ")^2" << endl;

			score += maxFreq[j] - charFreq[c][j];
			//score += pow((maxFreq[j] - charFreq[c][j]), 2);
		}

		pair<string, int> wordWithFreq(word, score);

		words.push_back(wordWithFreq);
	}

	sort(words.begin(), words.end(), sortWords);
}

void WordleSolver::getWordScore(string filename)
{
	ifstream fin;

	cout << "Getting word scores..." << endl;

	fin.open(filename);

	while (fin)
	{
		string w;
		int f;

		fin >> w;
		fin >> f;

		if (w != "")
		{
			words.push_back({ w, f });
		}

	}

	fin.close();
}

void WordleSolver::printWordsWithFreq()
{
	for (const auto &i : words)
	{
		if (i.second < 50000)
			cout << i.first << ": " << i.second << endl;
	}

	cout << endl;
}

void WordleSolver::updateFrequency()
{
	int maxFreq[5]{ 0 };

	for (int i = 0; i < 26; i++)
		charFreq[i] = { 0, 0, 0, 0, 0 };

	for (const auto& i : words) //Loop through every remaining word
	{
		for (int j = 0; j < 5; j++) //Loop through every letter of every word
		{
			char c = i.first[j];
			int pos = c - 97;

			charFreq[pos][j] += 1;
		}
	}

	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (maxFreq[j] < charFreq[i][j])
				maxFreq[j] = charFreq[i][j];
		}
	}

	for (vector<pair<string, int>>::iterator i = words.begin(); i != words.end(); i++)
	{
		int score = 1;
		string word = i->first;
		int pos = i - words.begin();

		for (int j = 0; j < 5; j++)
		{
			char c = word[j] - 97;

			//if (word == "slice" || word == "slate")
			//	cout << word << " score = " << score << " + " << maxFreq[j] << " - " << charFreq[c][j] << endl;
				//cout << word << " score = " << score << " * 1 + (" << maxFreq[j] << " - " << charFreq[c][j] << ")^2" << endl;

			score += maxFreq[j] - charFreq[c][j];
			//score += pow((maxFreq[j] - charFreq[c][j]), 2);
		}


		pair<string, int> val(word, score);

		words[pos] = val;
	}

	sort(words.begin(), words.end(), sortWords);
}

void WordleSolver::setWordle(string w)
{
	if (w == "")
	{
		wordle = getRandomWordle();
	}
	else
		wordle = w;

	//cout << "Wordle: " << wordle << endl << endl;
}

string WordleSolver::getBestGuess()
{
	return words[0].first;
}

string WordleSolver::getRandomWordle()
{
	random_device rd;
	mt19937 mt(rd());
	uniform_real_distribution<double> dist(0, possibleAnswers.size());

	return possibleAnswers[dist(mt)];
}

void WordleSolver::makeGuess(string g)
{
	guessNum++;

	if (g == "")
		guess = getBestGuess();
	else
		guess = g;

		getGuessResults();
}

void WordleSolver::getGuessResults()
{
	for (int i = 0; i < 5; i++)
	{
		yellowLetters[i] = '0';
	}

	//Check for letters in correct position
	for (int i = 0; i < 5; i++)
	{
		if (guess[i] == wordle[i])
		{
			green[i] = '1';
		}
	}

	//Check for correct letters in wrong position
	for (int i = 0; i < 5; i++)
	{
		bool addYellowLetter = false;
		pair<char, int> val;

		for (int j = 0; j < 5; j++)
		{
			if (guess[i] == wordle[j] && i != j && green[i] != '1')
			{
				val = { guess[i], i };

				addYellowLetter = true;
			}
		}

		if (addYellowLetter)
		{
			yelloww.push_back(val);
			yellowLetters[val.second] = '1';
		}
	}

	for (int i = 0; i < 5; i++)
	{
		bool isYellowOrGreen = false;

		for (int j = 0; j < 5; j++)
		{
			if (guess[i] == green[j])
				isYellowOrGreen = true;
		}

		for (int j = 0; j < yelloww.size(); j++)
		{
			if (guess[i] == yelloww[j].first)
				isYellowOrGreen = true;
		}

		if (!isYellowOrGreen && guess[i] != wordle[i])
			grey.push_back(guess[i]);
	}

	printGuessResults();
}

void WordleSolver::printGuessResults()
{
	string letter;

	cout << "Guess " << guessNum << ": ";

	for (int i = 0; i < 5; i++)
	{
		letter = guess[i];

		if (green[i] == '1')
		{
			SetConsoleTextAttribute(hConsole, 10);
			cout << letter;
			SetConsoleTextAttribute(hConsole, 7);
		}
		else if (yellowLetters[i] == '1')
		{
			SetConsoleTextAttribute(hConsole, 14);
			cout << letter;
			SetConsoleTextAttribute(hConsole, 7);
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 7);
			cout << letter;
		}
	}

	SetConsoleTextAttribute(hConsole, 7);

	cout << endl;
}

void WordleSolver::eliminateWords()
{
	int numWordsRemoved = 0;

	auto i = words.begin();

	while (i != words.end())
	{
		int pos = i - words.begin();
		string word = i->first;
		bool wordRemoved = false;

		if (!wordRemoved)
		{
			//Eliminate word if greens aren't in it
			for (int j = 0; j < 5; j++)
			{
					if (green[j] == '1' && word[j] != wordle[j])
					{
						wordRemoved = true;
					}
			}

			//Eliminate word if yellows aren't in it
			for (int j = 0; j < 5; j++)
			{
				for (int t = 0; t < yelloww.size(); t++)
				{
					if (word[j] == yelloww[t].first && j == yelloww[t].second)
					{
						wordRemoved = true;
					}
				}
			}

			for (int j = 0; j < yelloww.size(); j++)
			{
				bool letterIncluded = false;

				for (int t = 0; t < 5; t++)
				{

					if (yelloww[j].first == word[t])
					{
						letterIncluded = true;
					}
				}

				if (!letterIncluded)
					wordRemoved = true;
			}

			//Eliminate word if it has one of the greys
			for (int j = 0; j < grey.size(); j++)
			{
				bool greyLetterIncluded = false;

				for (int t = 0; t < 5; t++)
				{
					if (grey[j] == word[t])
					{
						greyLetterIncluded = true;
					}
				}

				if (greyLetterIncluded)
					wordRemoved = true;
			}
		}

		if (wordRemoved)
		{
			i = words.erase(i);
			numWordsRemoved++;
		}
		else
			++i;
	}

	cout << "Eliminated " << numWordsRemoved << " words" << endl;
	cout << "Number of remaining possible guesses: " << words.size() << endl << endl;
}

void WordleSolver::gameOver()
{
	if (guess != "")
	{
		bool isCorrectGuess = true;

		for (int i = 0; i < 5; i++)
		{
			if (guess[i] != wordle[i])
				isCorrectGuess = false;
		}

		if (isCorrectGuess)
		{
			gameWon = true;
		}
	}

	if (gameWon)
		isGameOver = true;
}

void WordleSolver::resetVals()
{
	words.clear();
	guessNum = 0;
	grey.clear();
	yelloww.clear();
	isGameOver = false;
	gameWon = false;

	getWordScore("possibleWordleGuessesWithFrequencies.txt");
	
	for (int i = 0; i < 5; i++)
		green[i] = '0';
}

bool WordleSolver::getGameWon()
{
	return gameWon;
}

int WordleSolver::getGuessNum()
{
	return guessNum;
}

string WordleSolver::getWordle()
{
	return wordle;
}