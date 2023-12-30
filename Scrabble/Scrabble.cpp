#include <iostream>
#include <fstream>

void playGame(unsigned lettersCount, unsigned roundsCount)
{
	std::cout << 1;
}

void editSettings(unsigned& lettersCount, unsigned& roundsCount)
{
	const int MAX_LETTERS_COUNT = 100;
	const int MAX_ROUNDS_COUNT = 30;
	int option;
	unsigned changedLettersCount;
	unsigned changedRoundsCount;

	std::cout << "What do you want to change?" << std::endl;
	std::cout << "0. Change letters count" << std::endl;
	std::cout << "1. Change rounds count" << std::endl;
	std::cout << "2. Change both letters and rounds" << std::endl;
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

		default:
			return;
	}
}

void adToDictionary()
{
	const int MAX_WORD_SIZE = 10;

	std::fstream ofs;
	ofs.open("Dictionary.txt", std::ios::app);
	if (!ofs.is_open())
	{
		std::cout << "Fail to open file!" << std::endl;
		return;
	}

	char word[MAX_WORD_SIZE + 1] = "";
	std::cout << "Enter a word to insert: " << std::endl;
	std::cin >> word;
	if (word)
	{
		ofs << "\n" << word;
	}

	ofs.clear();
	ofs.close();
	return;
}

int main()
{
	bool readyToPlay = false;
	unsigned lettersCount = 10;
	unsigned roundsCount = 10;
	unsigned option;

	while (!readyToPlay)
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
				playGame(lettersCount, roundsCount);
				readyToPlay = true;
				break;
			case 2:
				editSettings(lettersCount, roundsCount);
				std::cout << "Letters: " << lettersCount << std::endl;
				std::cout << "Rounds: " << roundsCount << std::endl;
				break;
			case 3:
				adToDictionary();
				break;
			default:
				return -1;
		}
	}
}