#pragma once
#include "Player.h"

class RealPlayer : public Player
{
private:

public:
	RealPlayer(int color, bool *tempIsCheck, bool *tempCheckMat, bool *tempWillBeCheck);

	list<MyPoint> *PlayerSpeculation(MyPoint point, vector<vector<MyAllPawns*>> Board, Moves * allMoves, int playerColor);

	bool PlayerChoose(MyPoint point, vector<vector<MyAllPawns*>> *Board, Moves * allMoves, MyPoint tempPawnPosition, vector<MyAllPawns*> * ArrayOfDeathPawn);

	void moveThePawn(MyPoint point, vector<vector<MyAllPawns*>> *Board, Moves * allMoves, MyPoint tempPawnPosition, bool writeMoveToList, vector<MyAllPawns*> * ArrayOfDeathPawn);

	void undoMove(vector<vector<MyAllPawns*>> *Board, Moves * allMoves, vector<MyAllPawns*> * ArrayOfDeathPawn);

	void setBoardPointsForPawns();

	void setPointsForPawns();

	void ComputerMove(vector<vector<MyAllPawns*>> *Board, Moves * allMoves, int TreeDepth, int tempColor, vector<MyAllPawns*> * ArrayOfDeathPawn);

	void MiniMax( vector<vector<MyAllPawns*>> *Board, Moves * allMoves, int TreeDepth, int tempColor, int *BoardValue, int ComputerPlayerColor, vector<MyAllPawns*> * ArrayOfDeathPawn);

	int countBoardPoints(vector<vector<MyAllPawns*>> *Board, int color);
};