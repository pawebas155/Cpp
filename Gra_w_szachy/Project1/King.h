#pragma once
#include "Pawn.h"

class King : public Pawn
{
public:
	King(string Name, MyPoint point, int color, int pos);
	void CheckPossibleMoves(MyPoint point, vector<vector<MyAllPawns*>> MainBoard, Moves *move, list<MyPoint> *listOfPossibleMoves);
	bool isCheck(vector<vector<MyAllPawns*>> MainBoard, MyPoint KingPosition, MyPoint reallyKingPosition);
	King::~King();
};