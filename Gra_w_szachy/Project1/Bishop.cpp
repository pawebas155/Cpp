#include "Bishop.h"

Bishop::Bishop(string Name, MyPoint point, int color, int pos) : MyAllPawns(Name, point, color, pos)
{}

void Bishop::CheckPossibleMoves(MyPoint point, vector<vector<MyAllPawns*>> MainBoard, Moves *move, list<MyPoint> *listOfPossibleMoves)
{
	(*listOfPossibleMoves).clear();
	MyPoint temp;
	
		if (Pcolor == black)
		{
			//search cross up-right
			temp = point;
			while (temp.y > 0 && temp.x < 7)
			{
				if (MainBoard[temp.y - 1][temp.x + 1] && MainBoard[temp.y - 1][temp.x + 1]->showColor() == black)
				{
					break;
				}
				(*listOfPossibleMoves).push_back({ temp.y - 1, temp.x + 1 });

				if (MainBoard[temp.y - 1][temp.x + 1] && MainBoard[temp.y - 1][temp.x + 1]->showColor() == white)
				{
					break;
				}
				temp.y -= 1;
				temp.x += 1;
			}
			//search cross up-left
			temp = point;
			while (temp.y > 0 && temp.x > 0)
			{
				if (MainBoard[temp.y - 1][temp.x - 1] && MainBoard[temp.y - 1][temp.x - 1]->showColor() == black)
				{
					break;
				}
				(*listOfPossibleMoves).push_back({ temp.y - 1, temp.x - 1 });

				if (MainBoard[temp.y - 1][temp.x - 1] && MainBoard[temp.y - 1][temp.x - 1]->showColor() == white)
				{
					break;
				}
				temp.y -= 1;
				temp.x -= 1;
			}
			//search cross down-right
			temp = point;
			while (temp.y < 7 && temp.x < 7)
			{
				if (MainBoard[temp.y + 1][temp.x + 1] && MainBoard[temp.y + 1][temp.x + 1]->showColor() == black)
				{
					break;
				}
				(*listOfPossibleMoves).push_back({ temp.y + 1, temp.x + 1 });

				if (MainBoard[temp.y + 1][temp.x + 1] && MainBoard[temp.y + 1][temp.x + 1]->showColor() == white)
				{
					break;
				}
				temp.y += 1;
				temp.x += 1;
			}
			//search cross udown-left
			temp = point;
			while (temp.y < 7 && temp.x > 0)
			{
				if (MainBoard[temp.y + 1][temp.x - 1] && MainBoard[temp.y + 1][temp.x - 1]->showColor() == black)
				{
					break;
				}
				(*listOfPossibleMoves).push_back({ temp.y + 1, temp.x - 1 });

				if (MainBoard[temp.y + 1][temp.x - 1] && MainBoard[temp.y + 1][temp.x - 1]->showColor() == white)
				{
					break;
				}
				temp.y += 1;
				temp.x -= 1;
			}
		}
	
		if (Pcolor == white)
		{
			//search cross up-right
			temp = point;
			while (temp.y > 0 && temp.x < 7)
			{
				if (MainBoard[temp.y - 1][temp.x + 1] && MainBoard[temp.y - 1][temp.x + 1]->showColor() == white)
				{
					break;
				}
				(*listOfPossibleMoves).push_back({ temp.y - 1, temp.x + 1 });

				if (MainBoard[temp.y - 1][temp.x + 1] && MainBoard[temp.y - 1][temp.x + 1]->showColor() == black)
				{
					break;
				}
				temp.y -= 1;
				temp.x += 1;
			}
			//search cross up-left
			temp = point;
			while (temp.y > 0 && temp.x > 0)
			{
				if (MainBoard[temp.y - 1][temp.x - 1] && MainBoard[temp.y - 1][temp.x - 1]->showColor() == white)
				{
					break;
				}
				(*listOfPossibleMoves).push_back({ temp.y - 1, temp.x - 1 });

				if (MainBoard[temp.y - 1][temp.x - 1] && MainBoard[temp.y - 1][temp.x - 1]->showColor() == black)
				{
					break;
				}
				temp.y -= 1;
				temp.x -= 1;
			}
			//search cross down-right
			temp = point;
			while (temp.y < 7 && temp.x < 7)
			{
				if (MainBoard[temp.y + 1][temp.x + 1] && MainBoard[temp.y + 1][temp.x + 1]->showColor() == white)
				{
					break;
				}
				(*listOfPossibleMoves).push_back({ temp.y + 1, temp.x + 1 });

				if (MainBoard[temp.y + 1][temp.x + 1] && MainBoard[temp.y + 1][temp.x + 1]->showColor() == black)
				{
					break;
				}
				temp.y += 1;
				temp.x += 1;
			}
			//search cross udown-left
			temp = point;
			while (temp.y < 7 && temp.x > 0)
			{
				if (MainBoard[temp.y + 1][temp.x - 1] && MainBoard[temp.y + 1][temp.x - 1]->showColor() == white)
				{
					break;
				}
				(*listOfPossibleMoves).push_back({ temp.y + 1, temp.x - 1 });

				if (MainBoard[temp.y + 1][temp.x - 1] && MainBoard[temp.y + 1][temp.x - 1]->showColor() == black)
				{
					break;
				}
				temp.y += 1;
				temp.x -= 1;
			}
		}
}

bool Bishop::isCheck(vector<vector<MyAllPawns*>> MainBoard, MyPoint KingPosition, MyPoint reallyKingPosition)
{
	return false;
}

Bishop::~Bishop()
{}