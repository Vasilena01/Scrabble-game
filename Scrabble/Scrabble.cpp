#include <iostream>
#include <fstream>

const int MAX_LETTERS_COUNT = 100;
const int MAX_ROUNDS_COUNT = 30;

void printLetters(const char* letters, int lettersCount)
{
	for (int i = 0; i < lettersCount; i++)
	{
		std::cout << letters[i] << " ";
	}
	std::cout << std::endl;
}

int getWordLen(char* word)
{
	if (!word)
	{
		return -1;
	}

	int count = 0;

	while (*word)
	{
		count++;
		word++;
	}
	return count;
}

int stringCompare(const char* string1,const char* string2)
{
	if (!string1 || !string2)
	{
		return -1;
	}

	while (*string1 && ((*string1) == (*string2)))
	{
		string1++;
		string2++;
	}

	return (*string1 - *string2);
}

void fillWithZeros(bool*& arr, int len)
{
	if (!arr)
	{
		return;
	}

	for (int i = 0; i < len; i++)
	{
		arr[i] = 0;
	}
}

void generateRandomLetters(int count, char*& letters)
{
	char letter;
	int num;

	for (int i = 0; i < count; i++)
	{
		num = rand() % 26;   // generate a random number
		letter = 'a' + num;	// converts the random generated num to a character from a-z
		letters[i] = letter;
		std::cout << letter << " ";
	}
	std::cout << std::endl;
}

bool isLetterInGivenLetters(char letter, char* letters, bool*& letterOccurences, int lettersCount)
{
	for(int i = 0; i < lettersCount; i++)
	{
		// If we have two equal letters and the given letters contain min one time this letter, 
		// we want to check if there is a second occurence in the sequance of letters, because
		// when we use one letter, we can't use it anymore
 
		if (letter == letters[i] && letterOccurences[i] < 1)
		{
			letterOccurences[i]++;
			return true;
		}
	}
	return false;
}

bool isWordInDictionary(const char* word, int lettersCount)
{
	if (!word)
	{
		return false;
	}

	std::ifstream dictionaryFile("Dictionary.txt");

	if (!dictionaryFile.is_open())
	{
		std::cout << "Fail to open dictionary file!";
		return false;
	}

	char* dictionaryWord = new char[lettersCount + 1];
	dictionaryWord[lettersCount] = '\0';

	while (dictionaryFile >> dictionaryWord)
	{
		if (stringCompare(word, dictionaryWord) == 0)
		{
			dictionaryFile.close();
			return true;
		}
	}

	dictionaryFile.close();
	return false;
}

bool isWordValid(char* word, char* letters, int lettersCount)
{
	if (!word || !letters)
	{
		return false;
	}

	bool areValidLetters = false;
	bool isValidInDictionary = false;

	int wordLen = getWordLen(word);
	bool* letterOccurences = new bool[lettersCount];
	fillWithZeros(letterOccurences, lettersCount);

	// Check if the given letters contain all letters from our word 
	for (int i = 0; i < wordLen; i++)
	{
		areValidLetters = isLetterInGivenLetters(word[i], letters, letterOccurences, lettersCount);
		if (!areValidLetters)
		{
			break;
		}
	}

	// Check if the dictionary contains the word
	if (!areValidLetters)
	{
		std::cout << "Invalid word. Try again with: ";
		printLetters(letters, lettersCount);
		return false;
	}
	isValidInDictionary = isWordInDictionary(word, lettersCount);

	delete[] letterOccurences;

	// Check if both letters are from the given letters & word is in dictionary
	if (areValidLetters && isValidInDictionary)
	{
		return true;
	}
	else
	{
		std::cout << "Invalid word. Try again with: ";
		printLetters(letters, lettersCount);
		return false;
	}
}

void playGame(unsigned lettersCount, unsigned roundsCount)
{
	int currentRound = 1;
	int points = 0;

	while (currentRound <= roundsCount)
	{
		std::cout << "Round " << currentRound << ". Available letters: ";

		// Generating the letters
		char* letters = new char[lettersCount];
		generateRandomLetters(lettersCount, letters);
		
		// Check if the given word is valid
		char* word = new char[lettersCount + 1];
		word[lettersCount] = '\0';

		bool isValid = false;
		do {
			std::cout << "Enter a word: ";
			std::cin >> word;

			isValid = isWordValid(word, letters, lettersCount);
		} while (!isValid);

		// Calculating the points
		if (isValid)
		{
			points += getWordLen(word);
		}

		if (currentRound < roundsCount)
		{
			std::cout << "Your points so far are: " << points << std::endl;
		}

		currentRound++;

		delete[] letters;
		delete[] word;
	}

	std::cout << "Your total points are: " << points << std::endl;
	std::cout << "Returning to menu..." << std::endl;
}

void editSettings(unsigned& lettersCount, unsigned& roundsCount)
{
	int option;
	unsigned changedLettersCount;
	unsigned changedRoundsCount;

	std::cout << "What do you want to change?" << std::endl;
	std::cout << "0. Change letters count" << std::endl;
	std::cout << "1. Change rounds count" << std::endl;
	std::cout << "2. Change both letters and rounds" << std::endl;
	std::cout << "3. Exit" << std::endl;
	std::cin >> option;

	switch (option)
	{
		case 0:
			std::cout << "Enter the new letters count: " << std::endl;
			do
			{
				std::cout << "Enter a number between 0 - " << MAX_LETTERS_COUNT << std::endl;
				std::cin >> changedLettersCount;
			} while (changedLettersCount > MAX_LETTERS_COUNT);
			lettersCount = changedLettersCount;
			break;

		case 1:
			std::cout << "Enter the new rounds count: " << std::endl;
			do
			{
				std::cout << "Enter a number between 0 - " << MAX_ROUNDS_COUNT << std::endl;
				std::cin >> changedRoundsCount;
			} while (changedRoundsCount > MAX_ROUNDS_COUNT);

			roundsCount = changedRoundsCount;
			break;

		case 2:
			std::cout << "Enter the new letters & rounds count: " << std::endl;
			do
			{
				std::cout << "For the letters enter a number between 0 - " << MAX_LETTERS_COUNT << std::endl;
				std::cout << "For the rounds enter a number between 0 - " << MAX_ROUNDS_COUNT << std::endl;

				std::cin >> changedLettersCount >> changedRoundsCount;
			} while (changedLettersCount > MAX_LETTERS_COUNT || changedRoundsCount > MAX_ROUNDS_COUNT);

			lettersCount = changedLettersCount;
			roundsCount = changedRoundsCount;
			break;
		case 3:
			std::cout << "Returning to menu...";
			return;
			break;
		default:
			return;
	}
}

void addToDictionary(unsigned lettersCount)
{
	std::fstream ofs("Dictionary.txt", std::ios::app);

	if (!ofs.is_open())
	{
		std::cout << "Fail to open file!" << std::endl;
		return;
	}

	char* word = new char[lettersCount + 1];
	word[lettersCount] = '\0';

	do {
		std::cout << "Enter a valid word to insert: " << std::endl;
		std::cin >> word;
	} while (word && isWordInDictionary(word, lettersCount));
	
	ofs << "\n" << word;

	ofs.clear();
	ofs.close();
	delete[] word;
}

int main()
{
	bool readyToPlay = true;
	unsigned lettersCount = 10;
	unsigned roundsCount = 10;
	unsigned option;

	while (readyToPlay)
	{
		std::cout << "Select one from the options bellow (1, 2, 3, 4):" << std::endl;
		std::cout << "1. Start a new game" << std::endl;
		std::cout << "2. Settings (Edit the default letters or rounds count)" << std::endl;
		std::cout << "3. Insert a new word in the dictionary" << std::endl;
		std::cout << "4. Exit" << std::endl;
		std::cin >> option;

		switch (option)
		{
			case 1:
				srand(time(NULL)); // initialize the random number generator
				playGame(lettersCount, roundsCount);
				break;
			case 2:
				editSettings(lettersCount, roundsCount);
				std::cout << "Letters: " << lettersCount << std::endl;
				std::cout << "Rounds: " << roundsCount << std::endl;
				break;
			case 3:
				addToDictionary(lettersCount);
				break;
			default:
				readyToPlay = false;
				return -1;
		}
	}
}