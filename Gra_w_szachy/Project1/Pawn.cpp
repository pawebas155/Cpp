#include <iostream>
#include "Pawn.h"
#include "AllPawns.h"

Pawn::Pawn(string Name, MyPoint point, int color, int pos) : MyAllPawns(Name, point, color, pos)
{}

void Pawn::CheckPossibleMoves(MyPoint point, vector<vector<MyAllPawns*>> MainBoard, Moves *move, list<MyPoint> *listOfPossibleMoves)
{
	(*listOfPossibleMoves).clear();
	// podstawowe ruchy
	// 0 - czarne, 1 - bia³e
	
		if (Pcolor == black)
		{
			if (point.y == 1 && MainBoard[point.y + 2][point.x] == nullptr && MainBoard[point.y + 1][point.x] == nullptr)
			{
				(*listOfPossibleMoves).push_back({ point.y + 2, point.x });
			}
			if (point.y < 7 && MainBoard[point.y + 1][point.x] == nullptr)
			{
				(*listOfPossibleMoves).push_back({ point.y + 1, point.x });
			}
			if (point.x > 0 && point.y < 7 && MainBoard[point.y + 1][point.x - 1] != nullptr && MainBoard[point.y + 1][point.x - 1]->showColor() == white)
			{
				(*listOfPossibleMoves).push_back({ point.y + 1, point.x - 1 });
			}
			if (point.x < 7 && point.y < 7 && MainBoard[point.y + 1][point.x + 1] != nullptr && MainBoard[point.y + 1][point.x + 1]->showColor() == white)
			{
				(*listOfPossibleMoves).push_back({ point.y + 1, point.x + 1 });
			}
		}
	
		if (Pcolor == white)
		{
			if (point.y == 6 && MainBoard[point.y - 2][point.x] == nullptr && MainBoard[point.y - 1][point.x] == nullptr)
			{
				(*listOfPossibleMoves).push_back({ point.y - 2, point.x });
			}
			if (point.y > 0 && MainBoard[point.y - 1][point.x] == nullptr)
			{
				(*listOfPossibleMoves).push_back({ point.y - 1, point.x });
			}
			if (point.x > 0 && point.y > 0 && MainBoard[point.y - 1][point.x - 1] != nullptr && MainBoard[point.y - 1][point.x - 1]->showColor() == black)
			{
				(*listOfPossibleMoves).push_back({ point.y - 1, point.x - 1 });
			}
			if (point.x < 7 && point.y > 0 && MainBoard[point.y - 1][point.x + 1] != nullptr && MainBoard[point.y - 1][point.x + 1]->showColor() == black)
			{
				(*listOfPossibleMoves).push_back({ point.y - 1, point.x + 1 });
			}
		}
}

bool Pawn::isCheck(vector<vector<MyAllPawns*>> MainBoard, MyPoint KingPosition, MyPoint reallyKingPosition)
{
	return false;
}

Pawn::~Pawn()
{}