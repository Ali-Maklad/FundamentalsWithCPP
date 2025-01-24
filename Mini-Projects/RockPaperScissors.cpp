#include <iostream>
#include <cstdlib>

using namespace std;

enum EnPick
{
	Rock = 1,
	Paper,
	Scissors
};
enum EnWinner
{
	Player = 1,
	Computer,
	Draw
};

struct stRoundInfo
{
	short RoundOrder;
	EnPick PlayerPick;
	EnPick ComputerPick;
	EnWinner Winner;
	string RoundWinnerName;
};

struct stGameInfo
{
	short GameRounds;
	short PlayerWon;
	short ComputerWon;
	short Draws;
	EnWinner GameWinner;
	string GameWinnerName;
};

short ReadPositiveNumBetween(int From, int To)
{
	int Num;
	do
	{
		cin >> Num;
	} while (Num < From || Num > To);
	return Num;
}

short RandomNumBetween(int From, int To)
{
	int Rand = rand() % (To - From + 1) + From;
	return Rand;
}

short HowManyRounds()
{
	stGameInfo GameInfo;
	cout << "How Many rounds do you want to play ?\n";
	GameInfo.GameRounds = ReadPositiveNumBetween(1, 10);

	return GameInfo.GameRounds;
}

EnPick GetPlayerPick()
{
	short Choice;
	cout << "What do you want to pick ? [1]Rock  [2]Paper  [3]Scissors   ";
	Choice = ReadPositiveNumBetween(1, 3);
	return (EnPick)Choice;
}

EnPick MakeComputerPick()
{
	short Choice = RandomNumBetween(1, 3);
	return (EnPick)Choice;
}

EnWinner WhoWonRound(stRoundInfo RoundInfo)
{

	if (RoundInfo.ComputerPick == RoundInfo.PlayerPick)
	{
		return EnWinner::Draw;
	}
	else if ((RoundInfo.PlayerPick == Rock) && (RoundInfo.ComputerPick == Scissors))
	{
		return EnWinner::Player;
	}
	else if ((RoundInfo.PlayerPick == Paper) && (RoundInfo.ComputerPick == Rock))
	{
		return EnWinner::Player;
	}
	else if ((RoundInfo.PlayerPick == Scissors) && (RoundInfo.ComputerPick == Paper))
	{
		return EnWinner::Player;
	}
	return EnWinner::Computer;
}

string WinnerName(EnWinner AyanYakonB2a)
{

	string Arr[3] = {"Player", "Computer", "Draw"};
	return Arr[AyanYakonB2a - 1];
}

string ChoiceName(EnPick AyanYakonB2a)
{

	string Arr[3] = {"Rock", "Paper", "Scissors"};
	return Arr[AyanYakonB2a - 1];
}

void FillRoundInfo(stRoundInfo &RoundInfo)
{

	RoundInfo.PlayerPick = GetPlayerPick();
	RoundInfo.ComputerPick = MakeComputerPick();
	RoundInfo.Winner = WhoWonRound(RoundInfo);
	RoundInfo.RoundWinnerName = WinnerName(RoundInfo.Winner);
}

void ChangeScreenColor(EnWinner AyanYakonB2a)
{
	switch (AyanYakonB2a)
	{
	case Player:
		system("color 2f");
		break;
	case Computer:
		system("color 4f");
		break;
	case Draw:
		system("color 6f");
		break;
	}
}

void Round(stRoundInfo &RoundInfo)
{

	cout << "Round [" << RoundInfo.RoundOrder << "] begins:\n";
	FillRoundInfo(RoundInfo);
	cout << "__________________[[Round" << RoundInfo.RoundOrder << "]]__________________\n";
	cout << "Player choice: " << ChoiceName(RoundInfo.PlayerPick) << endl;
	cout << "Computer choice: " << ChoiceName(RoundInfo.ComputerPick) << endl;
	cout << "Round Winner : " << WinnerName(RoundInfo.Winner) << endl;
	cout << "_________________________________________\n\n\n";
	ChangeScreenColor(RoundInfo.Winner);
}

EnWinner WhoWonGame(short PlayerWon, short ComputerWon)
{
	if (PlayerWon > ComputerWon)
		return EnWinner::Player;
	else if (PlayerWon < ComputerWon)
		return EnWinner::Computer;
	else
		return EnWinner::Draw;
}

string Tabs(short num)
{
	string t = "";
	for (int i = 1; i <= num; i++)
	{
		t = t + "\t";
	}
	return t;
}

void PrintGameOver()
{
	cout << Tabs(2) << "___________________________________________________\n\n";
	cout << Tabs(4) << "***G A M E  O V E R***\n";
	cout << Tabs(2) << "___________________________________________________\n\n";
}

void Game(stGameInfo &GameInfo)
{
	stRoundInfo RoundInfo;

	GameInfo.GameRounds = HowManyRounds();
	GameInfo.ComputerWon = 0, GameInfo.PlayerWon = 0, GameInfo.Draws = 0;

	for (RoundInfo.RoundOrder = 1; RoundInfo.RoundOrder <= GameInfo.GameRounds; RoundInfo.RoundOrder++)
	{

		Round(RoundInfo);
		if (RoundInfo.Winner == Player)
			GameInfo.PlayerWon++;
		else if (RoundInfo.Winner == Computer)
			GameInfo.ComputerWon++;
		else
			GameInfo.Draws++;
	}
	GameInfo.GameWinner = WhoWonGame(GameInfo.PlayerWon, GameInfo.ComputerWon);
	PrintGameOver();
	cout << Tabs(2) << "__________________[Game Results]___________________\n";
	cout << Tabs(2) << "Game Rounds: \t" << GameInfo.GameRounds << "\n";
	cout << Tabs(2) << "Player won: \t" << GameInfo.PlayerWon << "\n";
	cout << Tabs(2) << "Computer won: \t" << GameInfo.ComputerWon << "\n";
	cout << Tabs(2) << "Draw Times: \t" << GameInfo.Draws << "\n";
	cout << Tabs(2) << "Final Winner: \t" << WinnerName(GameInfo.GameWinner) << "\n";
	cout << Tabs(2) << "_______________________________________________\n";
	ChangeScreenColor(GameInfo.GameWinner);
}

bool Replay()
{
	char YN;
	cout << Tabs(2) << "Do you want to play another game ? [y/n]\n";
	cin >> YN;
	if (YN == 'y' || YN == 'Y')
		return true;
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

int main()
{

	srand((unsigned)time(NULL));
	do
	{
		ResetScreen();
		stGameInfo GameInfo;
		Game(GameInfo);
	} while (Replay() == true);

	return 0;
}