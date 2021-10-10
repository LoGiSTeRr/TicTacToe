//TicTacToe
#include <iostream>
#include <iomanip>  
#include <random>
#include <ctime>

std::default_random_engine engine(time(nullptr));
std::uniform_int_distribution<int> rng(1, 9);

// not all prototypes, cuz im lazy
bool EmptySpaces(char[][3]);
void PrintBoard(char[][3]);
bool CheckWin(int, int[], char[][3]);
int NextTurn(int, int[], char[][3]);
int NextBotTurn(int, int[], char[][3]);
void NewGame(int, int[], char[][3]);

bool EmptySpaces(char Board[][3])
{
	int spaces = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (Board[i][j] == ' ')
			{
				spaces++;
			}
		}
	}
	if (spaces == 0)
	{
		return false;
	}
	return true;
}
void PrintBoard(char arr[][3])
{
	int count = 1;
	std::cout << "\nYour Board:       Positions: \n";
	std::cout << "|---|---|---|     |---|---|---|\n";
	for (int i = 0; i < 3; i++)
	{
		std::cout << "|";
		for (int j = 0; j < 3; j++)
		{
			std::cout << " " << arr[i][j] << " |";
		}
		std::cout << "     |";
		for (int j = 0; j < 3; j++)
		{
			std::cout << " " << count++ << " |";
		}
		std::cout << "\n|---|---|---|     |---|---|---|\n";
	}
}
bool CheckWin(int CurrentPlayer, int players[], char Board[][3])
{
	for (int i = 0; i < 3; i++) // checks rows
	{
		for (int j = 0; j < 2; j++)
		{
			if (Board[i][0] == players[j] && Board[i][0] == Board[i][1] && Board[i][1] == Board[i][2])
			{
				return true;
			}
		}
	}
	for (int i = 0; i < 3; i++) // checks columns
	{
		for (int j = 0; j < 2; j++)
		{
			if (Board[0][i] == players[j] && Board[0][i] == Board[1][i] && Board[1][i] == Board[2][i])
			{
				return true;
			}
		}
	}
	// checks diagonal 1
	for (int j = 0; j < 2; j++)
	{
		if (Board[0][0] == Board[1][1] && Board[1][1] == Board[2][2] && Board[0][0] == players[j])
		{
			return true;
		}
	}

	// checks diagonal 2
	for (int j = 0; j < 2; j++)
	{
		if (Board[2][0] == players[j] && Board[2][0] == Board[1][1] && Board[1][1] == Board[0][2] )
		{
			return true;
		}
	}

	return false;
}
int NextTurn(int CurrentPlayer, int players[], char Board[][3])
{
	if (!EmptySpaces(Board))
	{
		bool playAgain;
		std::cout << "\nTie\n";
		std::cout << "Wanna play again? 1 - yes, 0 - no: "; std::cin >> playAgain;
		if (playAgain)
		{
			NewGame(CurrentPlayer, players, Board);
		}
		return 0;
	}
	int position;
	if (CurrentPlayer == players[0])
	{
		std::cout << "Player 1, choose position to set: "; std::cin >> position;
		while (Board[0][position - 1] != ' ')
		{
			std::cout << "You can't. Choose another position: "; std::cin >> position;
		}
		Board[0][position - 1] = players[0];
		if (CheckWin(CurrentPlayer, players, Board))
		{
			bool playAgain;
			PrintBoard(Board);
			std::cout << "\nPlayer 1, Won!";
			std::cout << "\nWanna play again? 1 - yes, 0 - no: "; std::cin >> playAgain;
			if (playAgain)
			{
				NewGame(CurrentPlayer, players, Board);
			}
			return 0;
		}
		CurrentPlayer = players[1];
	}
	else
	{
		std::cout << "Player 2, choose position to set: "; std::cin >> position;
		while (Board[0][position - 1] != ' ')
		{
			std::cout << "You can't. Choose another position: "; std::cin >> position;
		}
		Board[0][position - 1] = players[1];
		if (CheckWin(CurrentPlayer, players, Board))
		{
			bool playAgain;
			PrintBoard(Board);
			std::cout << "\nPlayer 2, Won!";
			std::cout << "\nWanna play again? 1 - yes, 0 - no: "; std::cin >> playAgain;
			if (playAgain)
			{
				NewGame(CurrentPlayer, players, Board);
			}
			return 0;
		}
		CurrentPlayer = players[0];
	}
	PrintBoard(Board);
	NextTurn(CurrentPlayer, players, Board);
	PrintBoard(Board);
}
int CheckWinPositionsOfBot(int CurrentPlayer, int players[], char Board[][3]) // For bot algorithm.
{
	for (int position = 1; position < 10; position++)
	{
		if (Board[0][position - 1] == ' ')
		{
			Board[0][position - 1] = players[0];
			if (CheckWin(CurrentPlayer, players, Board))
			{
				Board[0][position - 1] = ' ';
				return position;
			}
			Board[0][position - 1] = ' ';
		}
	}
	return 0;
}
int ForCommonMoveOfBot(int CurrentPlayer, int players[], char Board[][3]) // if there's no moves for win at a moment
{
	for (int firstPos = 1; firstPos < 10; firstPos++)
	{
		if (Board[0][firstPos - 1] == ' ')
		{
			Board[0][firstPos - 1] = players[0];
			for (int secondPos = 1; secondPos < 10; secondPos++)
			{
				if (Board[0][secondPos - 1] == ' ')
				{
					Board[0][secondPos - 1] = players[0];
					if (CheckWin(CurrentPlayer, players, Board))
					{
						Board[0][secondPos - 1] = ' ';
						Board[0][firstPos - 1] = ' ';
						return firstPos;
					}
					Board[0][secondPos - 1] = ' ';
				}
			}
			Board[0][firstPos - 1] = ' ';
		}

	}
	return 0;
}
int ForCommonMoveOfBotToInterceptPlayer(int CurrentPlayer, int players[], char Board[][3]) // For making Tie.
{
	for (int firstPos = 1; firstPos < 10; firstPos++)
	{
		if (Board[0][firstPos - 1] == ' ')
		{
			Board[0][firstPos - 1] = players[1];
			for (int secondPos = 1; secondPos < 10; secondPos++)
			{
				if (Board[0][secondPos - 1] == ' ')
				{
					Board[0][secondPos - 1] = players[1];
					if (CheckWin(CurrentPlayer, players, Board))
					{
						Board[0][secondPos - 1] = ' ';
						Board[0][firstPos - 1] = ' ';
						return firstPos;
					}
					Board[0][secondPos - 1] = ' ';
				}
			}
			Board[0][firstPos - 1] = ' ';
		}
		
	}
	return 0;
}
int RandomMoveOfBot(int CurrentPlayer, int players[], char Board[][3])
{
	int position = rng(engine);
	while (Board[0][position - 1] != ' ')
	{
		position = rng(engine);
	}
	return position;
}
int CheckWinPositionsOfPlayer(int CurrentPlayer, int players[], char Board[][3]) // For bot algorithm.
{
	for (int position = 1; position < 10; position++)
	{
		if (Board[0][position - 1] == ' ')
		{
			Board[0][position - 1] = players[1];
			if (CheckWin(CurrentPlayer, players, Board))
			{
				Board[0][position - 1] = ' ';
				return position;
			}
			Board[0][position - 1] = ' ';
		}
	}
	return 0;
}
int NextBotTurn(int CurrentPlayer, int players[], char Board[][3])
{

	if (!EmptySpaces(Board))
	{
		bool playAgain;
		std::cout << "\nTie\n";
		std::cout << "Wanna play again? 1 - yes, 0 - no: "; std::cin >> playAgain;
		if (playAgain)
		{
			NewGame(CurrentPlayer, players, Board);
		}
		return 0;
	}
	int position;
	if (CurrentPlayer == players[0]) // Bot's turn
	{
		if (CheckWinPositionsOfBot(CurrentPlayer, players, Board) != 0)
		{
			position = CheckWinPositionsOfBot(CurrentPlayer, players, Board);
			Board[0][position - 1] = players[0];
		}
		else if (CheckWinPositionsOfPlayer(CurrentPlayer, players, Board) != 0)
		{
			position = CheckWinPositionsOfPlayer(CurrentPlayer, players, Board);
			Board[0][position - 1] = players[0];
		}
		else if (ForCommonMoveOfBot(CurrentPlayer, players, Board) != 0)
		{
			position = ForCommonMoveOfBot(CurrentPlayer, players, Board);
			Board[0][position - 1] = players[0];
		}
		else if (ForCommonMoveOfBotToInterceptPlayer(CurrentPlayer, players, Board) != 0)
		{
			position = ForCommonMoveOfBotToInterceptPlayer(CurrentPlayer, players, Board);
			Board[0][position - 1] = players[0];
		}
		else
		{
			position = RandomMoveOfBot(CurrentPlayer, players, Board);
			Board[0][position - 1] = players[0];
		}
		if (CheckWin(CurrentPlayer, players, Board))
		{
			bool playAgain;
			PrintBoard(Board);
			std::cout << "Bot, Won!";
			std::cout << "\nWanna play again? 1 - yes, 0 - no: "; std::cin >> playAgain;
			if (playAgain)
			{
				NewGame(CurrentPlayer, players, Board);
			}
			return 0;
		}
		CurrentPlayer = players[1];
	}
	else //Player's turn
	{
		std::cout << "Player 2, choose position to set: "; std::cin >> position;
		while (Board[0][position - 1] != ' ')
		{
			std::cout << "You can't. Choose another position: "; std::cin >> position;
		}
		Board[0][position - 1] = players[1];
		if (CheckWin(CurrentPlayer, players, Board))
		{
			bool playAgain;
			PrintBoard(Board);
			std::cout << "\nPlayer 2, Won!";
			std::cout << "\nWanna play again? 1 - yes, 0 - no: "; std::cin >> playAgain;
			if (playAgain)
			{
				NewGame(CurrentPlayer, players, Board);
			}
			return 0;
		}
		CurrentPlayer = players[0];
	}
	PrintBoard(Board);
	NextBotTurn(CurrentPlayer, players, Board);
}
void NewGame(int CurrentPlayer, int players[], char Board[][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Board[i][j] = ' ';
		}
	}
	bool GameMode;
	std::cout << "Choose what u want to play (1 - player/player, 0 - bot/player): "; std::cin >> GameMode;
	std::cout << "\nPlayer's one char: " << (char)players[0] << '\n';
	std::cout << "Player's two char: " << (char)players[1] << '\n';
	CurrentPlayer = players[0];
	PrintBoard(Board);
	if (GameMode)
	{
		NextTurn(CurrentPlayer, players, Board);
	}
	else
	{
		int firstPos = rng(engine);
		while (firstPos != 1 && firstPos != 3 && firstPos != 5 && firstPos != 7 && firstPos != 9)
		{
			firstPos = rng(engine);
		}
		Board[0][firstPos - 1] = CurrentPlayer;
		CurrentPlayer = players[1];
		PrintBoard(Board);
		NextBotTurn(CurrentPlayer, players, Board);
	}
}
int main()
{
	std::cout << "Welcome to tic tac toe!\n";
	char Board[3][3];
	char Player1 = 'X';
	char Player2 = 'O';
	int players[2] = { Player1, Player2 };
	int CurrentPlayer = players[0];
	NewGame(CurrentPlayer, players, Board);
}





