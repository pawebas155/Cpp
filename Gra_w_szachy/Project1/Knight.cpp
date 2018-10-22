#include "Knight.h"

Knight::Knight(string Name, MyPoint point, int color, int pos) : MyAllPawns(Name, point, color, pos)
{}

void Knight::CheckPossibleMoves(MyPoint point, vector<vector<MyAllPawns*>> MainBoard, Moves *move, list<MyPoint> *listOfPossibleMoves)
{
	(*listOfPossibleMoves).clear();

		if (Pcolor == black)
		{
			//search cross up-right
			if (point.y > 1 && point.x < 7)
			{
				if ((MainBoard[point.y - 2][point.x + 1] && MainBoard[point.y - 2][point.x + 1]->showColor() == white) || MainBoard[point.y - 2][point.x + 1] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y - 2, point.x + 1 });
				}
			}
			if (point.y > 0 && point.x < 6)
			{
				if ((MainBoard[point.y - 1][point.x + 2] && MainBoard[point.y - 1][point.x + 2]->showColor() == white) || MainBoard[point.y - 1][point.x + 2] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y - 1, point.x + 2 });
				}
			}

			//search cross up-left
			if (point.y > 1 && point.x > 0)
			{
				if ((MainBoard[point.y - 2][point.x - 1] && MainBoard[point.y - 2][point.x - 1]->showColor() == white) || MainBoard[point.y - 2][point.x - 1] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y - 2, point.x - 1 });
				}
			}
			if (point.y > 0 && point.x > 1)
			{
				if ((MainBoard[point.y - 1][point.x - 2] && MainBoard[point.y - 1][point.x - 2]->showColor() == white) || MainBoard[point.y - 1][point.x - 2] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y - 1, point.x - 2 });
				}
			}

			//search cross down-right
			if (point.y < 6 && point.x < 7)
			{
				if ((MainBoard[point.y + 2][point.x + 1] && MainBoard[point.y + 2][point.x + 1]->showColor() == white) || MainBoard[point.y + 2][point.x + 1] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y + 2, point.x + 1 });
				}
			}
			if (point.y < 7 && point.x < 6)
			{
				if ((MainBoard[point.y + 1][point.x + 2] && MainBoard[point.y + 1][point.x + 2]->showColor() == white) || MainBoard[point.y + 1][point.x + 2] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y + 1, point.x + 2 });
				}
			}

			//search cross udown-left
			if (point.y < 6 && point.x > 0)
			{
				if ((MainBoard[point.y + 2][point.x - 1] && MainBoard[point.y + 2][point.x - 1]->showColor() == white) || MainBoard[point.y + 2][point.x - 1] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y + 2, point.x - 1 });
				}
			}
			if (point.y < 7 && point.x > 1)
			{
				if ((MainBoard[point.y + 1][point.x - 2] && MainBoard[point.y + 1][point.x - 2]->showColor() == white) || MainBoard[point.y + 1][point.x - 2] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y + 1, point.x - 2 });
				}
			}

		}
	
		if (Pcolor == white)
		{
			//search cross up-right
			if (point.y > 1 && point.x < 7)
			{
				if ((MainBoard[point.y - 2][point.x + 1] && MainBoard[point.y - 2][point.x + 1]->showColor() == black) || MainBoard[point.y - 2][point.x + 1] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y - 2, point.x + 1 });
				}
			}
			if (point.y > 0 && point.x < 6)
			{
				if ((MainBoard[point.y - 1][point.x + 2] && MainBoard[point.y - 1][point.x + 2]->showColor() == black) || MainBoard[point.y - 1][point.x + 2] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y - 1, point.x + 2 });
				}
			}

			//search cross up-left
			if (point.y > 1 && point.x > 0)
			{
				if ((MainBoard[point.y - 2][point.x - 1] && MainBoard[point.y - 2][point.x - 1]->showColor() == black) || MainBoard[point.y - 2][point.x - 1] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y - 2, point.x - 1 });
				}
			}
			if (point.y > 0 && point.x > 1)
			{
				if ((MainBoard[point.y - 1][point.x - 2] && MainBoard[point.y - 1][point.x - 2]->showColor() == black) || MainBoard[point.y - 1][point.x - 2] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y - 1, point.x - 2 });
				}
			}

			//search cross down-right
			if (point.y < 6 && point.x < 7)
			{
				if ((MainBoard[point.y + 2][point.x + 1] && MainBoard[point.y + 2][point.x + 1]->showColor() == black) || MainBoard[point.y + 2][point.x + 1] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y + 2, point.x + 1 });
				}
			}
			if (point.y < 7 && point.x < 6)
			{
				if ((MainBoard[point.y + 1][point.x + 2] && MainBoard[point.y + 1][point.x + 2]->showColor() == black) || MainBoard[point.y + 1][point.x + 2] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y + 1, point.x + 2 });
				}
			}

			//search cross udown-left
			if (point.y < 6 && point.x > 0)
			{
				if ((MainBoard[point.y + 2][point.x - 1] && MainBoard[point.y + 2][point.x - 1]->showColor() == black) || MainBoard[point.y + 2][point.x - 1] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y + 2, point.x - 1 });
				}
			}
			if (point.y < 7 && point.x > 1)
			{
				if ((MainBoard[point.y + 1][point.x - 2] && MainBoard[point.y + 1][point.x - 2]->showColor() == black) || MainBoard[point.y + 1][point.x - 2] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y + 1, point.x - 2 });
				}
			}

		}
}

bool Knight::isCheck(vector<vector<MyAllPawns*>> MainBoard, MyPoint KingPosition, MyPoint reallyKingPosition)
{
	return false;
}

Knight::~Knight()
{}