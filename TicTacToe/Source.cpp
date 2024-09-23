#include <iostream>
#include <conio.h> 
#include <string>
#include <queue>

#include "Helper.h"

#define Player1 'X'
#define Player2 'O'

#define BoardSize 9

void printBoard(const char* board);
int playOneTurn(char* board, char& player);
bool isEmpty(const char* board, int index);
bool checkIfWin(const char* board, char player);

void restartGame(char* board, std::queue<int> &turns);

int main()
{
	char board[BoardSize] = {};
	char player = Player1;

	std::queue<int> turns;

	char playAgain = 'y';

	while (playAgain == 'y' || playAgain == 'Y')
	{
		restartGame(board, turns);

		printBoard(board);
		
		while (true)
		{
			turns.push(playOneTurn(board, player));

			while (turns.size() >= 6)
			{
				board[turns.front()] = turns.front() + '0' + 1;
				turns.pop();
			}

			printBoard(board);

			if (checkIfWin(board, player))
			{
				break;
			}
			player == Player1 ? player = Player2 : player = Player1;
		}

		// Green color ANSI code
		std::cout << "\033[32m";  // Set text color to green
		std::cout << player << " WON!!!!" << std::endl;
		std::cout << "\033[0m";   // Reset to default text color

		std::cout << "Play again?" << std::endl << "press y for yes and any key for no not: ";
		playAgain = _getch();
	}

	return 0;
}


/*
	This function print the game board
	Input: the board
	Output: NONE
*/
void printBoard(const char* board)
{
	system("cls");
	std::cout << " " << board[6] << " | " << board[7] << " | " << board[8] << std::endl;
	std::cout << "---+---+---" << std::endl;
	std::cout << " " << board[3] << " | " << board[4] << " | " << board[5] << std::endl;
	std::cout << "---+---+---" << std::endl;
	std::cout << " " << board[0] << " | " << board[1] << " | " << board[2] << std::endl;
}

/*
	This function let one player to play
	Input: the boars the the playing player symbol
	Output: the choosen place
*/
int playOneTurn(char* board, char& player)
{
	int playerTurn;

	std::cout << "Pleas enter " << player << " turn: ";

	Helper::getInt(playerTurn);
	playerTurn--; //bc c++ start count at 0 and ont 1
	while(!isEmpty(board, playerTurn))
	{ 
		std::cout << "The spot you entered is either out of range or full" << std::endl << "Pleas enter your turn: ";
		Helper::getInt(playerTurn);
		playerTurn--; //bc c++ start count at 0 and ont 1
	}
	
	
	board[playerTurn] = player;
	
	return playerTurn;
}

/*
	This function check if a given slut is empty or not
	Input: the game board and the index to check
	Output: true if empty, otherwise false
*/
bool isEmpty(const char* board, int index)
{
	if (index >= BoardSize)
	{
		return false;
	}

	if (board[index] == Player1 || board[index] == Player2)
	{
		return false;
	}

	return true;
}

/*
	This function check if the enter player won the game
	Input: the board and the player
	Output: true for won, else false
*/
bool checkIfWin(const char* board, char player)
{
	int i = 0;

	int upDownStep = 3;
	int leftRightStep = 1;

	/**check slant**/
	for (i = 0; i < 9; i += 4)
	{
		if (board[i] != player)
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
		if (board[i] != player)
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
		if (board[i] == player && board[i + upDownStep] == player && board[i + upDownStep + upDownStep] == player)
		{
			return true;
		}
	}

	/**check left-right lines**/
	for (i = 0; i < 9; i += 3)
	{
		if (board[i] == player && board[i + leftRightStep] == player && board[i + leftRightStep + leftRightStep] == player)
		{
			return true;
		}
	}

	return false;
}

/*
	This function restart the game board
	Input: the board
	Output: NONE
*/
void restartGame(char* board, std::queue<int> &turns)
{
	//restart board
	for (int i = 0; i < 9; i++)
	{
		board[i] = i + '0' + 1;
	}
	
	/*to be added need some changes in other functions as well
	for (int i = 0; i < 3; i++) {
		// Swap the top row with the bottom row
		char temp = board[i];
		board[i] = board[6 + i];
		board[6 + i] = temp;
	}*/

	while (turns.size() > 0)
	{
		turns.pop();
	}
}