#pragma once
#include "AllPawns.h"

class Rook :
	public virtual MyAllPawns
{
public:
	Rook(string Name, MyPoint point, int color, int pos);
	void CheckPossibleMoves(MyPoint point, vector<vector<MyAllPawns*>> MainBoard, Moves *move, list<MyPoint> *listOfPossibleMoves);
	bool isCheck(vector<vector<MyAllPawns*>> MainBoard, MyPoint KingPosition, MyPoint reallyKingPosition);
	Rook::~Rook();
};
