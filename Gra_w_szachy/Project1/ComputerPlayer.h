#pragma once
#include "Player.h"

class ComputerPlayer :	public Player
{
private:
	int color;
	int PawnPower;
	int RookPower;
	int KnightPower;
	int BishopPower;
	int QueenPower;
	int KingPower;
	int PawnPoints[8][8];
	int RookPoints[8][8];
	int KnightPoints[8][8];
	int BishopPoints[8][8];
	int QueenPoints[8][8];
	int KingPoints[8][8];
	int KingPointsEndGame[8][8];

public:
	ComputerPlayer(int color, bool *tempIsCheck, bool *tempCheckMat, bool *tempWillBeCheck);

	void setBoardPointsForPawns();

	void setPointsForPawns();

	void ComputerMove(vector<vector<MyAllPawns*>> *Board, Moves * allMoves, int TreeDepth, int tempColor, vector<MyAllPawns*> * ArrayOfDeathPawn);

	void MiniMax( vector<vector<MyAllPawns*>> *Board, Moves * allMoves, int TreeDepth, int tempColor, int *BoardValue, int ComputerPlayerColor, vector<MyAllPawns*> * ArrayOfDeathPawn);
	
	int countBoardPoints(vector<vector<MyAllPawns*>> *Board, int color);

	list<MyPoint> *PlayerSpeculation(MyPoint point, vector<vector<MyAllPawns*>> Board, Moves * allMoves, int playerColor);
	bool PlayerChoose(MyPoint point, vector<vector<MyAllPawns*>> *Board, Moves * allMoves, MyPoint tempPawnPosition, vector<MyAllPawns*> * ArrayOfDeathPawn);
	void moveThePawn(MyPoint point, vector<vector<MyAllPawns*>> *Board, Moves * allMoves, MyPoint tempPawnPosition, bool writeMoveToList, vector<MyAllPawns*> * ArrayOfDeathPawn);

	void undoMove(vector<vector<MyAllPawns*>> *Board, Moves * allMoves, vector<MyAllPawns*> * ArrayOfDeathPawn);
};