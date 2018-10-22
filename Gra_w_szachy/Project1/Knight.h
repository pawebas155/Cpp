#pragma once
#include "AllPawns.h"
#include "myUsefulStruct.h"

class Knight : public MyAllPawns
{
public:
	Knight(string Name, MyPoint point, int color, int pos);
	void CheckPossibleMoves(MyPoint point, vector<vector<MyAllPawns*>> MainBoard, Moves *move, list<MyPoint> *listOfPossibleMoves);
	bool isCheck(vector<vector<MyAllPawns*>> MainBoard, MyPoint KingPosition, MyPoint reallyKingPosition);
	~Knight();
};