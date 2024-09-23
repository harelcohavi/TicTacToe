#include <iostream>
#include <conio.h> 

#include  "Helper.h"

#define PLAYER1 '|'
#define PLAYER2 '-'
#define TAKEN_PLACE '+'

#define BOARD_SIZE 9

void restartBoard(char* board);
void printBoard(const char* board);

void switchTurn(char& player);
int playOneTurn(char* board, char& player, int& lastPlayed);
bool isEmpty(const char* board, int index, const char player);

bool checkIfWin(const char* board);

int main()
{
	char board[BOARD_SIZE] = {};

	int lastPlayed = -1;

	char currPlayer = PLAYER2;
	char playAgain = 'y';
	restartBoard(board);

	while(playAgain == 'y' || playAgain == 'Y')
	{
		restartBoard(board);
		lastPlayed = -1;

		while (!checkIfWin(board))
		{
			printBoard(board);
			switchTurn(currPlayer);
			playOneTurn(board, currPlayer, lastPlayed);
		}

		printBoard(board);
		// Green color ANSI code
		std::cout << "\033[32m";  // Set text color to green
		std::cout << currPlayer << " WON!!!!" << std::endl;
		std::cout << "\033[0m";   // Reset to default text color

		std::cout << "Play again?" << std::endl << "press y for yes and any key for no not: ";
		playAgain = _getch();
	}
}

/*
	This function restart the board
	Input: the board to restart
	Output: NONE
*/
void restartBoard(char* board)
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		board[i] = i + 1 + '0';
	}
}

/*
	This function print the board
	Input: the board to print
	Output: NONE
*/
void printBoard(const char* board)
{
	system("cls");  // Clear the console (Windows-specific)
	// For Unix-like systems, use: system("clear");

	std::cout << "+---+---+---+" << std::endl;
	std::cout << "| " << board[6] << " | " << board[7] << " | " << board[8] << " |" << std::endl;
	std::cout << "+---+---+---+" << std::endl;
	std::cout << "| " << board[3] << " | " << board[4] << " | " << board[5] << " |" << std::endl;
	std::cout << "+---+---+---+" << std::endl;
	std::cout << "| " << board[0] << " | " << board[1] << " | " << board[2] << " |" << std::endl;
	std::cout << "+---+---+---+" << std::endl;
}

/*
	This function switch the player symbol to the other player symbol
	Input: current player symberl as refrence
	Output: NONE
*/
void switchTurn(char& player)
{
	player == PLAYER1 ? player = PLAYER2 : player = PLAYER1;
}

/*
	This function let one player to play
	Input: the boars the the playing player symbol and last player move
	Output: the choosen place
*/
int playOneTurn(char* board, char& player, int& lastPlayed)
{
	int playerTurn;

	std::cout << "Pleas enter " << player << " turn: ";

	Helper::getInt(playerTurn);
	playerTurn--; //bc c++ start count at 0 and ont 1
	while (!isEmpty(board, playerTurn, player) || playerTurn == lastPlayed)
	{
		std::cout << "The spot you entered is either out of range or full or played in the last turn" << std::endl << "Pleas enter your turn: ";
		Helper::getInt(playerTurn);
		playerTurn--; //bc c++ start count at 0 and ont 1
	}

	if (board[playerTurn] >= '1' && board[playerTurn] <= '9')
		{ 
			board[playerTurn] = player;
		}
	else
	{
		board[playerTurn] = TAKEN_PLACE;
	}

	lastPlayed = playerTurn;

	return playerTurn;
}

/*
	This function check if a given slut is empty or not
	Input: the game board and the index to check and the playing player symbal
	Output: true if empty, otherwise false
*/
bool isEmpty(const char* board, int index, const char player)
{
	if (index >= BOARD_SIZE)
	{
		return false;
	}

	if (board[index] == player || board[index] == TAKEN_PLACE)
	{
		return false;
	}

	return true;
}


/*
	This function check if the last player won the game
	Input: the board
	Output: true for won, else false
*/
bool checkIfWin(const char* board)
{
	int i = 0;

	int upDownStep = 3;
	int leftRightStep = 1;

	const char placed = '+';

	/**check slant**/
	for (i = 0; i < 9; i += 4)
	{
		if (board[i] != placed)
		{
			break;
		}
	}
	//check if it pass all three in the slant
	if (i > 8)
	{
		return true;
	}

	for (i = 2; i < 7; i += 2)
	{
		if (board[i] != placed)
		{
			break;
		}
	}
	//check if it pass all three in the slant
	if (i > 6)
	{
		return true;
	}

	/**check up-down lines**/
	for (i = 0; i < 3; i++)
	{
		if (board[i] == placed && board[i + upDownStep] == placed && board[i + upDownStep + upDownStep] == placed)
		{
			return true;
		}
	}

	/**check left-right lines**/
	for (i = 0; i < 9; i += 3)
	{
		if (board[i] == placed && board[i + leftRightStep] == placed && board[i + leftRightStep + leftRightStep] == placed)
		{
			return true;
		}
	}

	return false;
}