#pragma once
#include "Rook.h"
#include "Bishop.h"

class Queen :
	public Rook, public Bishop
{
public:
	Queen(string Name, MyPoint point, int color, int pos);
	void CheckPossibleMoves(MyPoint point, vector<vector<MyAllPawns*>> MainBoard, Moves *move, list<MyPoint> *listOfPossibleMoves);
	bool isCheck(vector<vector<MyAllPawns*>> MainBoard, MyPoint KingPosition, MyPoint reallyKingPosition);
	Queen::~Queen();
};