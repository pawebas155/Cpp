#pragma once
#include "myUsefulStruct.h"
#include <list>
#include "AllPawns.h"
#include "Moves.h"
#include <string.h>
#include "Queen.h"
#include "King.h"
#include "Knight.h"


using namespace std;

class Player
{
protected:
	int playerColor;
	list<MyPoint> PossibleMoves;
	bool *isCheck;
	bool *checkMat;
	bool *willBeCheck;

public:
	Player(int color, bool *tempIsCheck, bool *tempCheckMat, bool *tempWillBeCheck);
	
	virtual list<MyPoint> *PlayerSpeculation(MyPoint point, vector<vector<MyAllPawns*>> Board, Moves * allMoves, int playerColor) = 0;
	
	virtual bool PlayerChoose(MyPoint point, vector<vector<MyAllPawns*>> *Board, Moves * allMoves, MyPoint tempPawnPosition, vector<MyAllPawns*> * ArrayOfDeathPawn) = 0;
	
	virtual void moveThePawn(MyPoint point, vector<vector<MyAllPawns*>> *Board, Moves * allMoves, MyPoint tempPawnPosition, bool writeMoveToList, vector<MyAllPawns*> * ArrayOfDeathPawn) = 0;
	
	virtual void undoMove(vector<vector<MyAllPawns*>> *Board, Moves * allMoves, vector<MyAllPawns*> * ArrayOfDeathPawn) = 0;

	void deleteFirstPossibleMove();

	virtual void setBoardPointsForPawns() = 0;

	virtual void setPointsForPawns() = 0;

	virtual void MiniMax( vector<vector<MyAllPawns*>> *Board, Moves * allMoves, int TreeDepth, int tempColor, int *BoardValue, int ComputerPlayerColor, vector<MyAllPawns*> * ArrayOfDeathPawn) = 0;

	virtual void ComputerMove(vector<vector<MyAllPawns*>> *Board, Moves * allMoves, int TreeDepth, int tempColor, vector<MyAllPawns*> * ArrayOfDeathPawn) = 0;

	virtual int countBoardPoints(vector<vector<MyAllPawns*>> *Board, int color) = 0;

	virtual ~Player();
};