#pragma once
#include <iostream>
#include <list>
#include "myUsefulStruct.h"
#include "AllPawns.h"

using namespace std;

class Pawn : public MyAllPawns
{
public:
	Pawn(string Name, MyPoint point, int color, int pos);
	void CheckPossibleMoves(MyPoint point, vector<vector<MyAllPawns*>> MainBoard, Moves *move, list<MyPoint> *listOfPossibleMoves);
	bool isCheck(vector<vector<MyAllPawns*>> MainBoard, MyPoint KingPosition, MyPoint reallyKingPosition);
	Pawn::~Pawn();
};