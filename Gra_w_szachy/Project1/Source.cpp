#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <string>
#include "WindowScreen.h"
#include "Pawn.h"
#include "MainBoard.h"
#include "Moves.h"

using namespace std;

void HideConsole()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}

// zwalnianie pamieci lisy ruchow

int main()
{
	int spowalniacz = 0;
	int jakaAkcja = true;

	MyPoint point;

	int gameMode = 0;
	bool continueGame = false;
	cout << "Chose game mode: " << endl << "\t1. Single Player" << endl << "\t2. Multi Player" << endl << "\t3. Continue last game" << endl;
	while (1)
	{
		cin >> gameMode;
		if(gameMode == 1 || gameMode == 2 || gameMode == 3)
		{
			if (gameMode == 3)
			{
				continueGame = true;
			}
			break;
		}
	}

	MyWindow ChessGameWindow;
	Board ChessMainBoard(continueGame, gameMode);

	if (continueGame)
	{
		ifstream a;
		a.open("tablica.txt");
		a >> &ChessMainBoard;
		a.close();
	}

	//HideConsole();
	if(ChessMainBoard.showGameMode() == 2)
	{
		ChessMainBoard.createPlayers();

		while (ChessGameWindow.window.isOpen())
		{
			while (ChessGameWindow.window.pollEvent(ChessGameWindow.event))
			{
				if (ChessGameWindow.event.type == sf::Event::Closed)
				{
					ChessMainBoard.saveToFile();
					ofstream a;
					a.open("tablica.txt");
					a << ChessMainBoard;
					a.close();
					ChessGameWindow.window.close();
				}
			}

			// wyczyszczenie ekranu
			ChessGameWindow.window.clear(sf::Color(85, 100, 250));

			// ustawienie szachownicy
			ChessGameWindow.setAndShowChessColorBoard();

			ChessGameWindow.showNumberForBoard();
			ChessGameWindow.showChessOnBoard(ChessMainBoard.ShowArrayOfSprite());

			point = ChessGameWindow.MouseOperations();

			if (jakaAkcja)
			{
				jakaAkcja = ChessMainBoard.playerXTurn(point);
			}
			else
			{
				jakaAkcja = ChessMainBoard.playerXChoice(point);
			}
			
			if (ChessMainBoard.showCheckMat())
			{
				ChessGameWindow.sendMessage(2);
			}
			else
			{
				if (ChessMainBoard.showWillBeCheck())
				{
					ChessGameWindow.sendMessage(3);
				}
				else
				{
					if (ChessMainBoard.showIsCheck())
					{
						ChessGameWindow.sendMessage(1);
					}
				}
			}
			ChessGameWindow.showPossibleMoves(ChessMainBoard.sendPossibleMoves());
			
			ChessGameWindow.window.display();
		}
		ChessMainBoard.showListOfMoves();
	}
	else
	{
		ChessMainBoard.createPlayerAndComputer();

		while (ChessGameWindow.window.isOpen())
		{
			while (ChessGameWindow.window.pollEvent(ChessGameWindow.event))
			{
				if (ChessGameWindow.event.type == sf::Event::Closed)
				{
					ChessMainBoard.saveToFile();
					ofstream a;
					a.open("tablica.txt");
					a << ChessMainBoard;
					a.close();
					ChessGameWindow.window.close();
				}
			}

			// wyczyszczenie ekranu
			ChessGameWindow.window.clear(sf::Color(85, 100, 250));

			// ustawienie szachownicy
			ChessGameWindow.setAndShowChessColorBoard();

			ChessGameWindow.showNumberForBoard();
			ChessGameWindow.showChessOnBoard(ChessMainBoard.ShowArrayOfSprite());

			point = ChessGameWindow.MouseOperations();

			if (jakaAkcja)
			{
				jakaAkcja = ChessMainBoard.playerXTurn(point);
			}
			else
			{
				jakaAkcja = ChessMainBoard.playerXChoice(point);
			}

			if (ChessMainBoard.showTurn() == false)
			{
				ChessMainBoard.doComputerMove();
			}

			if (ChessMainBoard.showCheckMat())
			{
				ChessGameWindow.sendMessage(2);
			}
			else
			{
				if (ChessMainBoard.showWillBeCheck())
				{
					ChessGameWindow.sendMessage(3);
				}
				else
				{
					if (ChessMainBoard.showIsCheck())
					{
						ChessGameWindow.sendMessage(1);
					}
				}
			}

			ChessGameWindow.showPossibleMoves(ChessMainBoard.sendPossibleMoves());

			ChessGameWindow.window.display();
		}


		ChessMainBoard.showListOfMoves();
	}
	return 0;
}