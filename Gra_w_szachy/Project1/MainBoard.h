#pragma once
#include "myUsefulStruct.h"
#include "vector"
#include "Queen.h"
#include "King.h"
#include "Knight.h"
#include "Moves.h"
#include "ComputerPlayer.h"
#include "RealPlayer.h"
#include "WindowScreen.h"
#include <fstream>

class Board
{
private:
	vector<vector<MyAllPawns*>> MainBoard;
	list<MyPoint> *tempPossibleMoves;
	vector<MyAllPawns*> BoardOfDeathPawns;
	Moves AllMoves;
	Player *player[2];
	bool turn;
	MyPoint tempPawnPosition;
	bool isCheck;
	bool checkMat;
	bool willBeCheck;
	int gameModeToSave;

public:

	Board(bool isGameContinue, int gMode);

	void RestoreBoard(int posI, int posJ, int tempColor, string tempName);

	void setBoard();

	const vector<vector<sf::Sprite*>> ShowArrayOfSprite();

	void createPlayers();

	void createPlayerAndComputer();

	bool playerXTurn(MyPoint point);
	
	bool playerXChoice(MyPoint point);

	MyPoint findKingOnBoardOfColorX(int color);

	list<MyPoint> *sendPossibleMoves();

	// operator <<
	friend ofstream & operator << (ofstream & file, Board & temp);

	// operator >>
	friend ifstream & operator >> (ifstream &file, Board * temp);

	int showGameMode();

	void showListOfMoves();

	bool showIsCheck();

	void setIsCheck(bool x);

	bool showCheckMat();

	bool showTurn();

	void doComputerMove();

	void doUndoMove();

	void saveToFile();

	bool showWillBeCheck();

	void setWillBeCheck(bool x);

	void deleteMyBoard();

	~Board();
};
