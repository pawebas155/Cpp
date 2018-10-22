#include "Rook.h"

Rook::Rook(string Name, MyPoint point, int color, int pos) : MyAllPawns(Name, point, color, pos)
{}

void Rook::CheckPossibleMoves(MyPoint point, vector<vector<MyAllPawns*>> MainBoard, Moves *move, list<MyPoint> *listOfPossibleMoves)
{
	(*listOfPossibleMoves).clear();
	MyPoint temp;

		if (Pcolor == black)
		{
			//search up
			temp = point;
			while (temp.y > 0)
			{
				if (MainBoard[temp.y - 1][temp.x] && MainBoard[temp.y - 1][temp.x]->showColor() == black)
				{
					break;
				}

				(*listOfPossibleMoves).push_back({ temp.y - 1, temp.x });

				if (MainBoard[temp.y - 1][temp.x] && MainBoard[temp.y - 1][temp.x]->showColor() == white)
				{
					break;
				}

				temp.y -= 1;
			}
			//search down
			temp = point;
			while (temp.y < 7)
			{
				if (MainBoard[temp.y + 1][temp.x] && MainBoard[temp.y + 1][temp.x]->showColor() == black)
				{
					break;
				}

				(*listOfPossibleMoves).push_back({ temp.y + 1, temp.x });

				if (MainBoard[temp.y + 1][temp.x] && MainBoard[temp.y + 1][temp.x]->showColor() == white)
				{
					break;
				}

				temp.y += 1;
			}
			//search right
			temp = point;
			while (temp.x < 7)
			{
				if (MainBoard[temp.y][temp.x + 1] && MainBoard[temp.y][temp.x + 1]->showColor() == black)
				{
					break;
				}

				(*listOfPossibleMoves).push_back({ temp.y, temp.x + 1 });

				if (MainBoard[temp.y][temp.x + 1] && MainBoard[temp.y][temp.x + 1]->showColor() == white)
				{
					break;
				}

				temp.x += 1;
			}
			//search left
			temp = point;
			while (temp.x > 0)
			{
				if (MainBoard[temp.y][temp.x - 1] && MainBoard[temp.y][temp.x - 1]->showColor() == black)
				{
					break;
				}

				(*listOfPossibleMoves).push_back({ temp.y, temp.x - 1 });

				if (MainBoard[temp.y][temp.x - 1] && MainBoard[temp.y][temp.x - 1]->showColor() == white)
				{
					break;
				}

				temp.x -= 1;
			}
		}
	
	
		if (Pcolor == white)
		{
			//search up
			temp = point;
			while (temp.y > 0)
			{
				if (MainBoard[temp.y - 1][temp.x] && MainBoard[temp.y - 1][temp.x]->showColor() == white)
				{
					break;
				}

				(*listOfPossibleMoves).push_back({ temp.y - 1, temp.x });

				if (MainBoard[temp.y - 1][temp.x] && MainBoard[temp.y - 1][temp.x]->showColor() == black)
				{
					break;
				}

				temp.y -= 1;
			}
			//search down
			temp = point;
			while (temp.y < 7)
			{
				if (MainBoard[temp.y + 1][temp.x] && MainBoard[temp.y + 1][temp.x]->showColor() == white)
				{
					break;
				}

				(*listOfPossibleMoves).push_back({ temp.y + 1, temp.x });

				if (MainBoard[temp.y + 1][temp.x] && MainBoard[temp.y + 1][temp.x]->showColor() == black)
				{
					break;
				}

				temp.y += 1;
			}
			//search right
			temp = point;
			while (temp.x < 7)
			{
				if (MainBoard[temp.y][temp.x + 1] && MainBoard[temp.y][temp.x + 1]->showColor() == white)
				{
					break;
				}

				(*listOfPossibleMoves).push_back({ temp.y, temp.x + 1 });

				if (MainBoard[temp.y][temp.x + 1] && MainBoard[temp.y][temp.x + 1]->showColor() == black)
				{
					break;
				}

				temp.x += 1;
			}
			//search left
			temp = point;
			while (temp.x > 0)
			{
				if (MainBoard[temp.y][temp.x - 1] && MainBoard[temp.y][temp.x - 1]->showColor() == white)
				{
					break;
				}

				(*listOfPossibleMoves).push_back({ temp.y, temp.x - 1 });

				if (MainBoard[temp.y][temp.x - 1] && MainBoard[temp.y][temp.x - 1]->showColor() == black)
				{
					break;
				}

				temp.x -= 1;
			}
		}
}

bool Rook::isCheck(vector<vector<MyAllPawns*>> MainBoard, MyPoint KingPosition, MyPoint reallyKingPosition)
{
	return false;
}

Rook::~Rook()
{}