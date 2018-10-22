#include <iostream>
#include <vector>
#include <list>
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include <string>
#include <fstream>

/*
[Ctrl] + [m], [l]	Zwiñ/rozwiñ regiony, bloki kodu

[Ctrl] + [k], [c]	Zakomentuj zaznaczone
[Ctrl] + [k], [u]	Odkomentuj zaznaczone
*/

using namespace std;

class ConsoleManager
{
private:
	HANDLE StdHandle;
public:
	ConsoleManager()
	{
		StdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	void HideCursor()
	{
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO info;
		info.dwSize = 100;
		info.bVisible = FALSE;
		SetConsoleCursorInfo(consoleHandle, &info);
	}

	void SetPos(COORD pos)
	{
		SetConsoleCursorPosition(StdHandle, pos);
	}

	COORD GetPos()
	{
		_CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(StdHandle, &info);
		return info.dwCursorPosition;
	}

	void TypeChar(COORD pos, char arr[])
	{
		COORD temp = GetPos();
		SetPos(pos);
		for (int i = 0; arr[i] != 0; i++)
		{
			cout << arr[i];
		}
		SetPos(temp);
	}

	void TypeChar(COORD pos, string arr)	// jakbym chcia³ jakis napis umiescic - np.: wynik
	{
		COORD temp = GetPos();
		SetPos(pos);
		for (int i = 0; i < arr.length(); i++)
		{
			cout << arr[i];
		}
		SetPos(temp);
	}

	void TypeChar(COORD pos, string arr[], int height)	// jakbym chcia³ jakis napis umiescic - np.: wynik
	{
		COORD temp = GetPos();
		//SetPos(pos);
		for (int i = 0; i < height; i++)
		{
			SetPos({pos.X, (short)(pos.Y + i)});
			cout << arr[i] << endl;
		}
		SetPos(temp);
	}

	void TypeChar(COORD pos, char sign, WORD col = 7)
	{
		SetColourRed(col);
		COORD temp = GetPos();
		SetPos(pos);
		cout << sign;
		SetPos(temp);
		TurnOffColour();
	}

	void SetColourRed(WORD MyColour = 7)
	{
		SetConsoleTextAttribute(StdHandle, MyColour);
	}

	void TurnOffColour()
	{
		SetConsoleTextAttribute(StdHandle, 7);
	}
};

class ScoreFile
{
private:
	struct Result
	{
		COORD pos;
		char P_sign;
	};
	ofstream file;
	list<Result> Results;

public:
	void SaveToFile(bool winner, bool freeplace)
	{
		file.open("Game_Results.txt", ios::out | ios::app);

		if (file.is_open())
		{
			list<Result>::iterator it = Results.begin();
			list<Result>::iterator itend = Results.end();
			itend--;

			file << "Game Table:\n\n";

			for (it; it != itend; it++)
			{
				file << "Position: (" << (it->pos.X) / 2 << ", " << (it->pos.Y) / 2 << ") - Player: " << it->P_sign << endl;
			}
			file << "Position: (" << (it->pos.X) / 2 << ", " << (it->pos.Y) / 2 << ") - Player: " << it->P_sign << endl;

			if (winner)
			{
				file << "Win player: " << it->P_sign << endl << endl;
			}
			if (!freeplace)
			{
				file << "It's a draw!\n" << endl;
			}
			Results.clear();
			file.close();

		}
	}

	void SaveToList(COORD position, const char sign, bool winner, bool freeplace)
	{
		Results.push_back({ position, sign });

		if (winner || !freeplace)
		{
			SaveToFile(winner, freeplace);
		}
	}
};

class Board
{
private:
	friend class Player;
	friend class Opponent;
	ConsoleManager *ConsoleHandle;
	vector<vector<char>> MainBoard;
	ScoreFile SaveScove;
	COORD Side;
	bool whoseTurn = true; // true - player, false - opponent
	bool Winner = false;
	bool JumpToMenu = false;
	bool FreePlace = true;

public:
	Board() {}
	Board(ConsoleManager &mgr) 
	{ 
		ConsoleHandle = &mgr;
	}

	void GetSide()
	{
		string instr;
		int side;
		cout << "Give a side between 10 and 20: ";
		while (1)
		{
			cin >> instr;
			side = strtol(instr.c_str(), NULL, 10);

			if (side > 9 && side < 21) {
				break;
			}
		};
		Side = { (short)side, (short)side };
		system("cls");
	}

	std::vector<std::vector<char>> &ShowWhatInBoard()
	{
		return MainBoard;
	}

	bool ShowWhoseTurn()
	{
		return whoseTurn;
	}

	void ChangeWhoseTurn(bool turn)
	{
		whoseTurn = turn;
	}

	void SetMainBoard()
	{
		MainBoard.resize(2 * Side.Y - 1);
		for (int i = 0; i < (2 * Side.Y - 1); i++)
		{
			MainBoard[i].resize(2 * Side.X - 1);
		}

		for (int i = 0; i < (2 * Side.Y - 1); i++)
		{
			for (int j = 0; j < (2 * Side.X - 1); j += 2)
			{
				if (i % 2 == 0) 
				{
					MainBoard[i][j] = ' ';
					if (j != (2 * Side.X - 2)) {	MainBoard[i][j + 1] = '|';	}
				}
				else 
				{
					MainBoard[i][j] = '-';
					if (j != (2 * Side.X - 2)) {	MainBoard[i][j + 1] = '+';	}
				}
			}
		}
	}

	void ShowBoard()
	{
		ConsoleHandle->SetPos({ 0,0 });
		for (int i = 0; i < (2 * Side.Y - 1); i++)
		{
			for (int j = 0; j < (2 * Side.X - 1); j++)
			{
				cout << MainBoard[i][j];
			}
			cout << "\n";
		}
	}

	void PutSignToArr(COORD pos, char sign)		// false - 'O' turn, true - 'X' turn
	{
		string WriteOnScreen[2];
		WriteOnScreen[0] = "        It's a draw!         ";
		WriteOnScreen[1] = "Press button for back to menu";

		if (MainBoard[pos.Y][pos.X] == ' ')
		{
			MainBoard[pos.Y][pos.X] = sign;
			if (Correction(pos, sign)) // if true
			{
				Winner = true;
			}
			else
			{			// funkcja sprawdzajaca czy s¹ jeszcze wolne miejsca w tablicy
				if (FindFreePlace() == false)
				{
					FreePlace = false;
					ConsoleHandle->TypeChar({ 2 * Side.X + 5, (short)7 }, WriteOnScreen, 2);
				}		// funkcja sprawdzajaca czy s¹ jeszcze wolne miejsca w tablicy
			}
			
			// miejsce na funkcje, ktora wczyta ruch do pliku - place for function which write move to the file
			SaveScove.SaveToList({ pos.X, pos.Y }, sign, Winner, FreePlace);
			// miejsce na funkcje, ktora wczyta ruch do pliku - place for function which write move to the file

			if (sign == 'X')
				whoseTurn = false;
			else
				whoseTurn = true;
		}
		else
		{
			if (sign == 'X') {
				whoseTurn = true;
			}
			else
			{
				whoseTurn = false;
			}
		}
	}

	bool Correction(COORD pos, char sign)
	{
		const short point_to_win = 5;
		int count = 0;
		COORD tmppos = pos;
		string WriteOnScreen[2];
		WriteOnScreen[0] = "Win Player: ";
		WriteOnScreen[0] += sign;
		WriteOnScreen[1] = "Press button for back to menu";
		
		//----------------------------------------------------------------  up and down
		for (int i = 1; i <= 6; i++)
		{
			if (tmppos.Y >= 0 && tmppos.Y <=(2 * Side.Y - 2))
			{
				if (MainBoard[tmppos.Y][tmppos.X] == sign)
				{
					tmppos.Y = pos.Y - i * 2;
					count++;
				}
			}
			else {
				break;
			}
			if (count == point_to_win)
			{
				ConsoleHandle->TypeChar({ 2 * Side.X + 5, (short)7 }, WriteOnScreen, 2);
				return true;
			}
		}
		tmppos = pos;
		count--;
		for (int i = 1; i <= 6; i++)
		{
			if (tmppos.Y >= 0 && tmppos.Y <= (2 * Side.Y - 2))
			{
				if (MainBoard[tmppos.Y][tmppos.X] == sign)
				{
					tmppos.Y = pos.Y + i * 2;
					count++;
				}
			}
			else {
				break;
			}
			if (count == point_to_win)
			{
				ConsoleHandle->TypeChar({ 2 * Side.X + 5, (short)7 }, WriteOnScreen, 2);
				return true;
			}
		}
		//----------------------------------------------------------------  up and down
		count = 0; 
		tmppos = pos;
		//----------------------------------------------------------------  left and right
		for (int i = 1; i <= 6; i++)
		{
			if (tmppos.X >= 0 && tmppos.X <= (2 * Side.X - 2))
			{
				if (MainBoard[tmppos.Y][tmppos.X] == sign)
				{
					tmppos.X = pos.X - i * 2;
					count++;
				}
			}
			else {
				break;
			}
			if (count == point_to_win)
			{
				ConsoleHandle->TypeChar({ 2 * Side.X + 5, (short)7 }, WriteOnScreen, 2);
				return true;
			}
		}
		tmppos = pos;
		count--;
		for (int i = 1; i <= 6; i++)
		{
			if (tmppos.X >= 0 && tmppos.X <= (2 * Side.X - 2))
			{
				if (MainBoard[tmppos.Y][tmppos.X] == sign)
				{
					tmppos.X = pos.X + i * 2;
					count++;
				}
			}
			else {
				break;
			}
			if (count == point_to_win)
			{
				ConsoleHandle->TypeChar({ 2 * Side.X + 5, (short)7 }, WriteOnScreen, 2);
				return true;
			}
		}
		//----------------------------------------------------------------  left and right
		count = 0;
		tmppos = pos;
		//----------------------------------------------------------------  cross left-up and right-down
		for (int i = 1; i <= 6; i++)
		{
			if ( (tmppos.X >= 0 && tmppos.X <= (2 * Side.X - 2)) && (tmppos.Y >= 0 && tmppos.Y <= (2 * Side.Y - 2)) )
			{
				if (MainBoard[tmppos.Y][tmppos.X] == sign)
				{
					tmppos.X = pos.X - i * 2;
					tmppos.Y = pos.Y - i * 2;
					count++;
				}
			}
			else {
				break;
			}
			if (count == point_to_win)
			{
				ConsoleHandle->TypeChar({ 2 * Side.X + 5, (short)7 }, WriteOnScreen, 2);
				return true;
			}
		}
		tmppos = pos;
		count--;
		for (int i = 1; i <= 6; i++)
		{
			if ((tmppos.X >= 0 && tmppos.X <= (2 * Side.X - 2)) && (tmppos.Y >= 0 && tmppos.Y <= (2 * Side.Y - 2)))
			{
				if (MainBoard[tmppos.Y][tmppos.X] == sign)
				{
					tmppos.X = pos.X + i * 2;
					tmppos.Y = pos.Y + i * 2;
					count++;
				}
			}
			else {
				break;
			}
			if (count == point_to_win)
			{
				ConsoleHandle->TypeChar({ 2 * Side.X + 5, (short)7 }, WriteOnScreen, 2);
				return true;
			}
		}
		//----------------------------------------------------------------  cross left-up and right-down
		count = 0;
		tmppos = pos;
		//----------------------------------------------------------------  cross left-down and right-up
		for (int i = 1; i <= 6; i++)
		{
			if ((tmppos.X >= 0 && tmppos.X <= (2 * Side.X - 2)) && (tmppos.Y >= 0 && tmppos.Y <= (2 * Side.Y - 2)))
			{
				if (MainBoard[tmppos.Y][tmppos.X] == sign)
				{
					tmppos.X = pos.X - i * 2;
					tmppos.Y = pos.Y + i * 2;
					count++;
				}
			}
			else {
				break;
			}
			if (count == point_to_win)
			{
				ConsoleHandle->TypeChar({ 2 * Side.X + 5, (short)7 }, WriteOnScreen, 2);
				return true;
			}
		}
		tmppos = pos;
		count--;
		for (int i = 1; i <= 6; i++)
		{
			if ((tmppos.X >= 0 && tmppos.X <= (2 * Side.X - 2)) && (tmppos.Y >= 0 && tmppos.Y <= (2 * Side.Y - 2)))
			{
				if (MainBoard[tmppos.Y][tmppos.X] == sign)
				{
					tmppos.X = pos.X + i * 2;
					tmppos.Y = pos.Y - i * 2;
					count++;
				}
			}
			else {
				break;
			}
			if (count == point_to_win)
			{
				ConsoleHandle->TypeChar({ 2 * Side.X + 5, (short)7 }, WriteOnScreen, 2);
				return true;
			}
		}
		//----------------------------------------------------------------  cross left-down and right-up
		return false;
	}

	void ShowControlSystem()
	{
		string tab[5];
		tab[0] = "         Control       ";
		tab[1] = "   w                   ";
		tab[2] = "a     d           Enter";
		tab[3] = "   s                   ";
		tab[4] = "m - back to menu       ";

		ConsoleHandle->TypeChar({ (short)(2 * Side.X + 5), (short)1 }, tab, 5);
	}

	bool FindFreePlace()
	{
		for (int i = 0; i < (2 * Side.Y - 1); i++)
		{
			for (int j = 0; j < (2 * Side.X - 1); j++)
			{
				if (MainBoard[i][j] == ' ') {
					return true;
				}
			}
		}
		return false;
	}

	bool ShowIsWinner()
	{
		return Winner;
	}
	void ChangeIsWinner(bool Winr)
	{
		Winner = Winr;
	}
	bool ShowJumpToMenu()
	{
		return JumpToMenu;
	}
	void ChangeJumpToMenu(bool Jump)
	{
		JumpToMenu = Jump;
	}
	bool ShowIsFreePlace()
	{
		return FreePlace;
	}
	void ChangeIsFreePlace(bool FreePlc)
	{
		FreePlace = FreePlc;
	}
};

class Menu
{
private:
	struct MenuList
	{
		int number;
		vector<string> MenuHeads;
	};
	list<MenuList> MyMenu;
	int WhatToDo;

public:
	void MakeMenu()
	{
		MyMenu.push_back({ 0,{ "1. New Game", "2. Option", "3. Exit" } });
		MyMenu.push_back({ 1,{ "1. Single Player", "2. Multi-Player", "3. Back" } }); // New Game
		MyMenu.push_back({ 2,{ "1. Back" } }); // Option
	}

	void WriteMenu(int nb = 0)		// this function return: 0 - Exit the program, 1 - start the game
	{
		//system("cls");
		int choice;
		list<MenuList>::iterator IT = MyMenu.begin();
		for (int i = 0; i < nb; i++)
			IT++;

		cout << "Press to choose" << endl;
		for (vector<string>::iterator it = IT->MenuHeads.begin(); it != IT->MenuHeads.end(); it++)
		{
			cout << *it << endl;
		}
		switch (nb)
		{
		case 0:
			do { choice = _getch(); } while (choice != '1' && choice != '2' && choice != '3');
			break;
		case 1:
			do { choice = _getch(); } while (choice != '1' && choice != '2' && choice != '3');
			break;
		case 2:
			do { choice = _getch(); } while (choice != '1');
			break;
		default:
			WriteMenu(0);
		}
		choice -= 48;

		system("cls");
		
		if (nb == 0)
		{
			if (choice == 1)
				WriteMenu(1);
			if (choice == 2)
				WriteMenu(2);
			if (choice == 3) {
				WhatToDo = 0;
				// Exit program
			}
		}
		if (nb == 1)
		{
			if (choice == 1)
				WhatToDo = 1;	// Start game
			if (choice == 2)
				WhatToDo = 2;	// Start game 
			if (choice == 3)
				WriteMenu(0);
		}
		if (nb == 2)
		{
			if (choice == 1)
				WriteMenu(0);
		}
	}	 

	int ShowWhatToDo()
	{
		return WhatToDo;
	}
};

class Player 
{
private:
	ConsoleManager *ConsoleHandle;
	Board *MyBoard;
	COORD Position;
	char Sign;

public:
	Player(ConsoleManager &mgr, Board &board, COORD pos, char sign)
	{
		ConsoleHandle = &mgr;
		MyBoard = &board;
		Position = pos;
		Sign = sign;
	}
	
	bool InputStage()
	{
		if (_kbhit())
		{
			int key = _getch();
			COORD move = { 0, 0 };
			switch (key)
			{
			case('a'):
				if (Position.X > 0) { move.X -= 2; }
				break;
			case('d'):
				if (Position.X < (2 * MyBoard->Side.X - 2)) { move.X += 2; }
				break;
			case('w'):
				if (Position.Y > 0) { move.Y -= 2; }
				break;
			case('s'):
				if (Position.Y < (2 * MyBoard->Side.X - 2)) { move.Y += 2; }
				break;
			case('m'):
				MyBoard->JumpToMenu = true;
				break;
			case(13):
				MyBoard->PutSignToArr(Position, Sign);
			default:
				break;
			}
			Position = { Position.X + move.X, Position.Y + move.Y };
			return 1;
		}
		else 
		{
			return 0;
		}
	}
	void DrawPlayer() {
		ConsoleHandle->TypeChar(Position, Sign, 12);
	}
};

class Opponent
{
private:
	ConsoleManager *ConsoleHandle;
	Board *MyBoard;
	char Sign;
	struct MyCOORD
	{
		short X;
		short Y;
		short maximum;
	};

public:
	Opponent(ConsoleManager &mgr, Board &board, char sign)
	{
		ConsoleHandle = &mgr;
		MyBoard = &board;
		Sign = sign;
	}
	
	MyCOORD Find_danger() 
	{
		int count = 0;
		MyCOORD x_place;
		x_place.X = 0;
		x_place.Y = 0;
		x_place.maximum = 0;
		const vector<vector<char>> ConstArray = MyBoard->ShowWhatInBoard();

		for (int i = 0; i < (2 * MyBoard->Side.Y - 1); i += 2)
		{
			for (int j = 0; j < (2 * MyBoard->Side.X - 1); j += 2)
			{
				if (ConstArray[i][j] == ' ')
				{
					// left-up and right-down ------------------------------------------------------------------------------------------------
					for (int k = i - 2, l = j - 2; ; k -= 2, l -= 2)
					{
						if ((k >= 0 && k <= (2 * MyBoard->Side.Y - 2)) && (l >= 0 && l <= (2 * MyBoard->Side.X - 2)))
						{
							if (ConstArray[k][l] == ' ' || ConstArray[k][l] == 'O')
							{
								break;
							}
							if (ConstArray[k][l] == 'X')
							{
								count++;
								if (count > x_place.maximum) {
									x_place.maximum = count;
									x_place.X = j;
									x_place.Y = i;
								}
								if (x_place.maximum == 4) {
									//cout << "1. Najwiecej X-ow : ( " << x_place.X << ", " << x_place.Y << " ) ilosc wystapien: " << x_place.maximum << endl;
									return x_place;
								}
							}
						}
						else
						{
							break;
						}
					}
					for (int k = i + 2, l = j + 2; ; k += 2, l += 2)
					{
						if ((k >= 0 && k <= (2 * MyBoard->Side.Y - 2)) && (l >= 0 && l <= (2 * MyBoard->Side.X - 2)))
						{
							if (ConstArray[k][l] == ' ' || ConstArray[k][l] == 'O')
							{
								break;
							}
							if (ConstArray[k][l] == 'X')
							{
								count++;
								if (count > x_place.maximum) {
									x_place.maximum = count;
									x_place.X = j;
									x_place.Y = i;
								}
								if (x_place.maximum == 4) {
									//cout << "1. Najwiecej X-ow : ( " << x_place.X << ", " << x_place.Y << " ) ilosc wystapien: " << x_place.maximum << endl;
									return x_place;
								}
							}
						}
						else
						{
							break;
						}
						
					}
					// left-up and right-down ------------------------------------------------------------------------------------------------
					count = 0;	
					// up and down -----------------------------------------------------------------------------------------------------------
					for (int k = i - 2, l = j; ; k -= 2)
					{
						if ((k >= 0 && k <= (2 * MyBoard->Side.Y - 2)) && (l >= 0 && l <= (2 * MyBoard->Side.X - 2)))
						{
							if (ConstArray[k][l] == ' ' || ConstArray[k][l] == 'O')
							{
								break;
							}
							if (ConstArray[k][l] == 'X')
							{
								count++;
								if (count > x_place.maximum) {
									x_place.maximum = count;
									x_place.X = j;
									x_place.Y = i;
								}
								if (x_place.maximum == 4) {
									//cout << "2. Najwiecej X-ow : ( " << x_place.X << ", " << x_place.Y << " ) ilosc wystapien: " << x_place.maximum << endl;
									return x_place;
								}
							}
						}
						else
						{
							break;
						}
					}
					for (int k = i + 2, l = j; ; k += 2)
					{
						if ((k >= 0 && k <= (2 * MyBoard->Side.Y - 2)) && (l >= 0 && l <= (2 * MyBoard->Side.X - 2)))
						{
							if (ConstArray[k][l] == ' ' || ConstArray[k][l] == 'O')
							{
								break;
							}
							if (ConstArray[k][l] == 'X')
							{
								count++;
								if (count > x_place.maximum) {
									x_place.maximum = count;
									x_place.X = j;
									x_place.Y = i;
								}
								if (x_place.maximum == 4) {
									//cout << "2. Najwiecej X-ow : ( " << x_place.X << ", " << x_place.Y << " ) ilosc wystapien: " << x_place.maximum << endl;
									return x_place;
								}
							}
						}
						else
						{
							break;
						}

					}
					// up and down -----------------------------------------------------------------------------------------------------------
					count = 0;
					// right-up and left-down ------------------------------------------------------------------------------------------------
					for (int k = i - 2, l = j + 2; ; k -= 2, l += 2)
					{
						if ((k >= 0 && k <= (2 * MyBoard->Side.Y - 2)) && (l >= 0 && l <= (2 * MyBoard->Side.X - 2)))
						{
							if (ConstArray[k][l] == ' ' || ConstArray[k][l] == 'O')
							{
								break;
							}
							if (ConstArray[k][l] == 'X')
							{
								count++;
								if (count > x_place.maximum) {
									x_place.maximum = count;
									x_place.X = j;
									x_place.Y = i;
								}
								if (x_place.maximum == 4) {
									//cout << "3. Najwiecej X-ow : ( " << x_place.X << ", " << x_place.Y << " ) ilosc wystapien: " << x_place.maximum << endl;
									return x_place;
								}
							}
						}
						else
						{
							break;
						}
					}
					for (int k = i + 2, l = j - 2; ; k += 2, l -= 2)
					{
						if ((k >= 0 && k <= (2 * MyBoard->Side.Y - 2)) && (l >= 0 && l <= (2 * MyBoard->Side.X - 2)))
						{
							if (ConstArray[k][l] == ' ' || ConstArray[k][l] == 'O')
							{
								break;
							}
							if (ConstArray[k][l] == 'X')
							{
								count++;
								if (count > x_place.maximum) {
									x_place.maximum = count;
									x_place.X = j;
									x_place.Y = i;
								}
								if (x_place.maximum == 4) {
									//cout << "3. Najwiecej X-ow : ( " << x_place.X << ", " << x_place.Y << " ) ilosc wystapien: " << x_place.maximum << endl;
									return x_place;
								}
							}
						}
						else
						{
							break;
						}

					}
					// right-up and left-down ------------------------------------------------------------------------------------------------
					count = 0;
					// left and right --------------------------------------------------------------------------------------------------------
					for (int k = i, l = j - 2; ; l -= 2)
					{
						if ((k >= 0 && k <= (2 * MyBoard->Side.Y - 2)) && (l >= 0 && l <= (2 * MyBoard->Side.X - 2)))
						{
							if (ConstArray[k][l] == ' ' || ConstArray[k][l] == 'O')
							{
								break;
							}
							if (ConstArray[k][l] == 'X')
							{
								count++;
								if (count > x_place.maximum) {
									x_place.maximum = count;
									x_place.X = j;
									x_place.Y = i;
								}
								if (x_place.maximum == 4) {
									//cout << "4. Najwiecej X-ow : ( " << x_place.X << ", " << x_place.Y << " ) ilosc wystapien: " << x_place.maximum << endl;
									return x_place;
								}
							}
						}
						else
						{
							break;
						}
					}
					for (int k = i, l = j + 2; ; l += 2)
					{
						if ((k >= 0 && k <= (2 * MyBoard->Side.Y - 2)) && (l >= 0 && l <= (2 * MyBoard->Side.X - 2)))
						{
							if (ConstArray[k][l] == ' ' || ConstArray[k][l] == 'O')
							{
								break;
							}
							if (ConstArray[k][l] == 'X')
							{
								count++;
								if (count > x_place.maximum) {
									x_place.maximum = count;
									x_place.X = j;
									x_place.Y = i;
								}
								if (x_place.maximum == 4) {
									//cout << "4. Najwiecej X-ow : ( " << x_place.X << ", " << x_place.Y << " ) ilosc wystapien: " << x_place.maximum << endl;
									return x_place;
								}
							}
						}
						else
						{
							break;
						}

					}
					// left and right --------------------------------------------------------------------------------------------------------
					count = 0;
					if (x_place.maximum == 0)
					{
						x_place.X = j;
						x_place.Y = i;
					}
				}
			}
		}
		//cout << "Najwiecej X-ow : ( " << x_place.X << ", " << x_place.Y << " ) ilosc wystapien: " << x_place.maximum << endl;
		return x_place;
	}

	MyCOORD Find_occasion()
	{
		int count = 0;
		MyCOORD attack;
		attack.X = 0;
		attack.Y = 0;
		attack.maximum = 0;
		const vector<vector<char>> ConstArray = MyBoard->ShowWhatInBoard();

		for (int i = 0; i < (2 * MyBoard->Side.Y - 1); i += 2)
		{
			for (int j = 0; j < (2 * MyBoard->Side.X - 1); j += 2)
			{
				if (ConstArray[i][j] == ' ')
				{
					// left-up and right-down ------------------------------------------------------------------------------------------------
					for (int k = i - 2, l = j - 2; ; k -= 2, l -= 2)
					{
						if ((k >= 0 && k <= (2 * MyBoard->Side.Y - 2)) && (l >= 0 && l <= (2 * MyBoard->Side.X - 2)))
						{
							if (ConstArray[k][l] == ' ' || ConstArray[k][l] == 'X')
							{
								break;
							}
							if (ConstArray[k][l] == 'O')
							{
								count++;
								if (count > attack.maximum) {
									attack.maximum = count;
									attack.X = j;
									attack.Y = i;
								}
								if (attack.maximum == 4) {
									//cout << "1. Najwiecej O-ow : ( " << attack.X << ", " << attack.Y << " ) ilosc wystapien: " << attack.maximum << endl;
									return attack;
								}
							}
						}
						else
						{
							break;
						}
					}
					for (int k = i + 2, l = j + 2; ; k += 2, l += 2)
					{
						if ((k >= 0 && k <= (2 * MyBoard->Side.Y - 2)) && (l >= 0 && l <= (2 * MyBoard->Side.X - 2)))
						{
							if (ConstArray[k][l] == ' ' || ConstArray[k][l] == 'X')
							{
								break;
							}
							if (ConstArray[k][l] == 'O')
							{
								count++;
								if (count > attack.maximum) {
									attack.maximum = count;
									attack.X = j;
									attack.Y = i;
								}
								if (attack.maximum == 4) {
									//cout << "1. Najwiecej O-ow : ( " << attack.X << ", " << attack.Y << " ) ilosc wystapien: " << attack.maximum << endl;
									return attack;
								}
							}
						}
						else
						{
							break;
						}

					}
					// left-up and right-down ------------------------------------------------------------------------------------------------
					count = 0;
					// up and down -----------------------------------------------------------------------------------------------------------
					for (int k = i - 2, l = j; ; k -= 2)
					{
						if ((k >= 0 && k <= (2 * MyBoard->Side.Y - 2)) && (l >= 0 && l <= (2 * MyBoard->Side.X - 2)))
						{
							if (ConstArray[k][l] == ' ' || ConstArray[k][l] == 'X')
							{
								break;
							}
							if (ConstArray[k][l] == 'O')
							{
								count++;
								if (count > attack.maximum) {
									attack.maximum = count;
									attack.X = j;
									attack.Y = i;
								}
								if (attack.maximum == 4) {
									//cout << "2. Najwiecej O-ow : ( " << attack.X << ", " << attack.Y << " ) ilosc wystapien: " << attack.maximum << endl;
									return attack;
								}
							}
						}
						else
						{
							break;
						}
					}
					for (int k = i + 2, l = j; ; k += 2)
					{
						if ((k >= 0 && k <= (2 * MyBoard->Side.Y - 2)) && (l >= 0 && l <= (2 * MyBoard->Side.X - 2)))
						{
							if (ConstArray[k][l] == ' ' || ConstArray[k][l] == 'X')
							{
								break;
							}
							if (ConstArray[k][l] == 'O')
							{
								count++;
								if (count > attack.maximum) {
									attack.maximum = count;
									attack.X = j;
									attack.Y = i;
								}
								if (attack.maximum == 4) {
									//cout << "2. Najwiecej O-ow : ( " << attack.X << ", " << attack.Y << " ) ilosc wystapien: " << attack.maximum << endl;
									return attack;
								}
							}
						}
						else
						{
							break;
						}

					}
					// up and down -----------------------------------------------------------------------------------------------------------
					count = 0;
					// right-up and left-down ------------------------------------------------------------------------------------------------
					for (int k = i - 2, l = j + 2; ; k -= 2, l += 2)
					{
						if ((k >= 0 && k <= (2 * MyBoard->Side.Y - 2)) && (l >= 0 && l <= (2 * MyBoard->Side.X - 2)))
						{
							if (ConstArray[k][l] == ' ' || ConstArray[k][l] == 'X')
							{
								break;
							}
							if (ConstArray[k][l] == 'O')
							{
								count++;
								if (count > attack.maximum) {
									attack.maximum = count;
									attack.X = j;
									attack.Y = i;
								}
								if (attack.maximum == 4) {
									//cout << "3. Najwiecej O-ow : ( " << attack.X << ", " << attack.Y << " ) ilosc wystapien: " << attack.maximum << endl;
									return attack;
								}
							}
						}
						else
						{
							break;
						}
					}
					for (int k = i + 2, l = j - 2; ; k += 2, l -= 2)
					{
						if ((k >= 0 && k <= (2 * MyBoard->Side.Y - 2)) && (l >= 0 && l <= (2 * MyBoard->Side.X - 2)))
						{
							if (ConstArray[k][l] == ' ' || ConstArray[k][l] == 'X')
							{
								break;
							}
							if (ConstArray[k][l] == 'O')
							{
								count++;
								if (count > attack.maximum) {
									attack.maximum = count;
									attack.X = j;
									attack.Y = i;
								}
								if (attack.maximum == 4) {
									//cout << "3. Najwiecej X-ow : ( " << attack.X << ", " << attack.Y << " ) ilosc wystapien: " << attack.maximum << endl;
									return attack;
								}
							}
						}
						else
						{
							break;
						}

					}
					// right-up and left-down ------------------------------------------------------------------------------------------------
					count = 0;
					// left and right --------------------------------------------------------------------------------------------------------
					for (int k = i, l = j - 2; ; l -= 2)
					{
						if ((k >= 0 && k <= (2 * MyBoard->Side.Y - 2)) && (l >= 0 && l <= (2 * MyBoard->Side.X - 2)))
						{
							if (ConstArray[k][l] == ' ' || ConstArray[k][l] == 'X')
							{
								break;
							}
							if (ConstArray[k][l] == 'O')
							{
								count++;
								if (count > attack.maximum) {
									attack.maximum = count;
									attack.X = j;
									attack.Y = i;
								}
								if (attack.maximum == 4) {
									//cout << "4. Najwiecej O-ow : ( " << attack.X << ", " << attack.Y << " ) ilosc wystapien: " << attack.maximum << endl;
									return attack;
								}
							}
						}
						else
						{
							break;
						}
					}
					for (int k = i, l = j + 2; ; l += 2)
					{
						if ((k >= 0 && k <= (2 * MyBoard->Side.Y - 2)) && (l >= 0 && l <= (2 * MyBoard->Side.X - 2)))
						{
							if (ConstArray[k][l] == ' ' || ConstArray[k][l] == 'X')
							{
								break;
							}
							if (ConstArray[k][l] == 'O')
							{
								count++;
								if (count > attack.maximum) {
									attack.maximum = count;
									attack.X = j;
									attack.Y = i;
								}
								if (attack.maximum == 4) {
									//cout << "4. Najwiecej O-ow : ( " << attack.X << ", " << attack.Y << " ) ilosc wystapien: " << attack.maximum << endl;
									return attack;
								}
							}
						}
						else
						{
							break;
						}

					}
					// left and right --------------------------------------------------------------------------------------------------------
					count = 0;
					if (attack.maximum == 0)
					{
						attack.X = j;
						attack.Y = i;
					}
				}
			}
		}
		//cout << "Najwiecej O-ow : ( " << attack.X << ", " << attack.Y << " ) ilosc wystapien: " << attack.maximum << endl;
		return attack;
	}

	void PutSignSomewhere()
	{
		const vector<vector<char>> ConstArray = MyBoard->ShowWhatInBoard();
		MyCOORD danger_pos, occasion_pos;
		
		danger_pos = Find_danger();
		occasion_pos = Find_occasion();

		if (occasion_pos.maximum == 4)
		{
			MyBoard->PutSignToArr({ occasion_pos.X, occasion_pos.Y }, Sign);
			return;
		}
		if (danger_pos.maximum < 3)
		{
			if (occasion_pos.maximum > 2)
			{
				MyBoard->PutSignToArr({ occasion_pos.X, occasion_pos.Y }, Sign);
			}
			else
			{
				MyBoard->PutSignToArr({ danger_pos.X, danger_pos.Y }, Sign);
			}
		}
		else
		{
			MyBoard->PutSignToArr({ danger_pos.X, danger_pos.Y }, Sign);
		}
	}
};

int main()
{
	ConsoleManager Console;
	Console.HideCursor();
	Menu GameMenu;
	GameMenu.MakeMenu();
	Board GameBoard(Console);
	
	while (1)
	{
		GameMenu.WriteMenu(0);

		if (GameMenu.ShowWhatToDo() == 1)
		{
			GameBoard.GetSide();

			Player PlayerControll(Console, GameBoard, { 0, 0 }, 'X');
			Opponent OpponentControll(Console, GameBoard, 'O');

			GameBoard.SetMainBoard();
			GameBoard.ShowBoard();
			PlayerControll.DrawPlayer();

			GameBoard.ShowControlSystem();

			while (1)
			{
				if (GameBoard.ShowWhoseTurn())
				{
					if (PlayerControll.InputStage())
					{
						GameBoard.ShowBoard();
						PlayerControll.DrawPlayer();
					}
				}
				else
				{
					OpponentControll.PutSignSomewhere();
					GameBoard.ShowBoard();
				}
				if (GameBoard.ShowIsWinner())
				{
					GameBoard.ChangeIsWinner(false);
					GameBoard.ChangeWhoseTurn(true);
					if (_getch()) {
						system("cls");
						break;
					}
				}
				if (GameBoard.ShowJumpToMenu())
				{
					GameBoard.ChangeJumpToMenu(false);
					system("cls");
					break;
				}
				if (!GameBoard.ShowIsFreePlace())
				{
					GameBoard.ChangeIsFreePlace(true);
					if (_getch()) {
						system("cls");
						break;
					}
				}
			}
		}

		if (GameMenu.ShowWhatToDo() == 2)
		{
			GameBoard.GetSide();

			Player PlayerControll_1(Console, GameBoard, { 0, 0 }, 'X');
			Player PlayerControll_2(Console, GameBoard, { 0, 0 }, 'O');

			GameBoard.SetMainBoard();
			GameBoard.ShowBoard();
			GameBoard.ShowControlSystem();

			while (1)
			{
				if (GameBoard.ShowWhoseTurn())
				{
					PlayerControll_1.DrawPlayer();
					if (PlayerControll_1.InputStage())
					{
						GameBoard.ShowBoard();
					}
				}
				else
				{
					PlayerControll_2.DrawPlayer();
					if (PlayerControll_2.InputStage())
					{
						GameBoard.ShowBoard();
					}
				}
				if (GameBoard.ShowIsWinner())
				{
					GameBoard.ChangeIsWinner(false);
					if (_getch()) {
						system("cls");
						break;
					}
				}
				if (GameBoard.ShowJumpToMenu())
				{
					GameBoard.ChangeJumpToMenu(false);
					system("cls");
					break;
				}
				if (!GameBoard.ShowIsFreePlace())
				{
					GameBoard.ChangeIsFreePlace(true);
					if (_getch()) {
						system("cls");
						break;
					}
				}
			}
		}

		if (GameMenu.ShowWhatToDo() == 0)
		{
			return 0;
		}
	}

	return 0;
}
/*char **array;
array = new char*[(2*bok-1)];

for (int i = 0; i < (2 * bok - 1); i++) {
array[i] = new char[(2 * bok - 1)];
}

for (int i = 0; i < (2 * bok - 1); i++) {
for (int j = 0; j < (2 * bok - 1); j+=2) {
if (i%2 == 0) {
array[i][j] = ' ';
if (array[i][j + 1]) {
array[i][j + 1] = '|';
}
}
else {
array[i][j] = '-';
if (array[i][j + 1]) {
array[i][j + 1] = '+';
}
}
}
}

for (int i = 0; i < (2 * bok - 1); i++) {
for (int j = 0; j < (2 * bok - 1); j++) {
cout << array[i][j];
}
cout << endl;
}
*/