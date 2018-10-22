#include "King.h"

King::King(string Name, MyPoint point, int color, int pos) : Pawn(Name, point, color, pos)
{}

void King::CheckPossibleMoves(MyPoint point, vector<vector<MyAllPawns*>> MainBoard, Moves *move, list<MyPoint> *listOfPossibleMoves)
{
	(*listOfPossibleMoves).clear();
	// podstawowe ruchy
	// 0 - czarne, 1 - bia³e

	if (Pcolor == black)
	{
		// roszada
		if (MainBoard[0][1] == nullptr && MainBoard[0][2] == nullptr && MainBoard[0][3] == nullptr
			&& !move->doResearchForCastling({ 0,0 }, black) && !move->doResearchForCastling({ 4,0 }, black)
			&& MainBoard[0][4] && !MainBoard[0][4]->isCheck(MainBoard, { 4,0 }, { 4,0 })
			&& !MainBoard[0][4]->isCheck(MainBoard, { 2,0 }, { 4,0 }) && !MainBoard[0][4]->isCheck(MainBoard, { 3,0 }, { 4,0 }))
		{
			(*listOfPossibleMoves).push_back({ 0, 0 });	
		}

		if (MainBoard[0][5] == nullptr && MainBoard[0][6] == nullptr 
			&& !move->doResearchForCastling({ 7,0 }, black) && !move->doResearchForCastling({ 4,0 }, black) 
			&& MainBoard[0][4] && !MainBoard[0][4]->isCheck(MainBoard, { 4,0 }, { 4,0 })
			&& !MainBoard[0][4]->isCheck(MainBoard, { 5,0 }, { 4,0 }) && !MainBoard[0][4]->isCheck(MainBoard, { 6,0 }, { 4,0 }))
		{
			(*listOfPossibleMoves).push_back({ 0, 7 });
		}
		// roszada

		//search up
		if (point.y > 0)
		{
			if ((MainBoard[point.y - 1][point.x] && MainBoard[point.y - 1][point.x]->showColor() == white) || MainBoard[point.y - 1][point.x] == nullptr)
			{
				(*listOfPossibleMoves).push_back({ point.y - 1, point.x });
			}
		}
			//search down
			if (point.y < 7)
			{
				if ((MainBoard[point.y + 1][point.x] && MainBoard[point.y + 1][point.x]->showColor() == white) || MainBoard[point.y + 1][point.x] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y + 1, point.x });
				}
			}
			//search right
			if (point.x < 7)
			{
				if ((MainBoard[point.y][point.x + 1] && MainBoard[point.y][point.x + 1]->showColor() == white) || MainBoard[point.y][point.x + 1] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y, point.x + 1 });
				}
			}
			//search left
			if (point.x > 0)
			{
				if ((MainBoard[point.y][point.x - 1] && MainBoard[point.y][point.x - 1]->showColor() == white) || MainBoard[point.y][point.x - 1] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y, point.x - 1 });
				}
			}
			//search cross up-right
			if (point.y > 0 && point.x < 7)
			{
				if ((MainBoard[point.y - 1][point.x + 1] && MainBoard[point.y - 1][point.x + 1]->showColor() == white) || MainBoard[point.y - 1][point.x + 1] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y - 1, point.x + 1 });
				}
			}
			//search cross up-left
			if (point.y > 0 && point.x > 0)
			{
				if ((MainBoard[point.y - 1][point.x - 1] && MainBoard[point.y - 1][point.x - 1]->showColor() == white) || MainBoard[point.y - 1][point.x - 1] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y - 1, point.x - 1 });
				}
			}
			//search cross down-right
			if (point.y < 7 && point.x < 7)
			{
				if ((MainBoard[point.y + 1][point.x + 1] && MainBoard[point.y + 1][point.x + 1]->showColor() == white) || MainBoard[point.y + 1][point.x + 1] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y + 1, point.x + 1 });
				}
			}
			//search cross udown-left
			if (point.y < 7 && point.x > 0)
			{
				if ((MainBoard[point.y + 1][point.x - 1] && MainBoard[point.y + 1][point.x - 1]->showColor() == white) || MainBoard[point.y + 1][point.x - 1] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y + 1, point.x - 1 });
				}
			}
		}
	
	if (Pcolor == white)
		{
		// roszada
		if (MainBoard[7][1] == nullptr && MainBoard[7][2] == nullptr && MainBoard[7][3] == nullptr
			&& !move->doResearchForCastling({ 0,7 }, white) && !move->doResearchForCastling({ 4,7 }, white)
			&& MainBoard[7][4] && !MainBoard[0][4]->isCheck(MainBoard, { 4,7 }, { 4,7 })
			&& !MainBoard[7][4]->isCheck(MainBoard, { 2,7 }, { 4,7 }) && !MainBoard[7][4]->isCheck(MainBoard, { 3,7 }, { 4,7 }))
		{
			(*listOfPossibleMoves).push_back({ 7, 0 });
		}

		if (MainBoard[7][5] == nullptr && MainBoard[7][6] == nullptr 
			&& !move->doResearchForCastling({ 7,7 }, white)	&& !move->doResearchForCastling({ 7, 4 }, white) 
			&& MainBoard[7][4] && !MainBoard[0][4]->isCheck(MainBoard, { 4,7 }, { 4,7 })
			&& !MainBoard[7][4]->isCheck(MainBoard, { 5,7 }, { 4,7 }) && !MainBoard[7][4]->isCheck(MainBoard, { 6,7 }, { 4,7 }))
		{
			(*listOfPossibleMoves).push_back({ 7, 7 });
		}
		// roszada

			//search up
			if (point.y > 0)
			{
				if ((MainBoard[point.y - 1][point.x] && MainBoard[point.y - 1][point.x]->showColor() == black) || MainBoard[point.y - 1][point.x] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y - 1, point.x });
				}
			}
			//search down
			if (point.y < 7)
			{
				if ((MainBoard[point.y + 1][point.x] && MainBoard[point.y + 1][point.x]->showColor() == black) || MainBoard[point.y + 1][point.x] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y + 1, point.x });
				}
			}
			//search right
			if (point.x < 7)
			{
				if ((MainBoard[point.y][point.x + 1] && MainBoard[point.y][point.x + 1]->showColor() == black) || MainBoard[point.y][point.x + 1] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y, point.x + 1 });
				}
			}
			//search left
			if (point.x > 0)
			{
				if ((MainBoard[point.y][point.x - 1] && MainBoard[point.y][point.x - 1]->showColor() == black) || MainBoard[point.y][point.x - 1] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y, point.x - 1 });
				}
			}
			//search cross up-right
			if (point.y > 0 && point.x < 7)
			{
				if ((MainBoard[point.y - 1][point.x + 1] && MainBoard[point.y - 1][point.x + 1]->showColor() == black) || MainBoard[point.y - 1][point.x + 1] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y - 1, point.x + 1 });
				}
			}
			//search cross up-left
			if (point.y > 0 && point.x > 0)
			{
				if ((MainBoard[point.y - 1][point.x - 1] && MainBoard[point.y - 1][point.x - 1]->showColor() == black) || MainBoard[point.y - 1][point.x - 1] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y - 1, point.x - 1 });
				}
			}
			//search cross down-right
			if (point.y < 7 && point.x < 7)
			{
				if ((MainBoard[point.y + 1][point.x + 1] && MainBoard[point.y + 1][point.x + 1]->showColor() == black) || MainBoard[point.y + 1][point.x + 1] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y + 1, point.x + 1 });
				}
			}
			//search cross udown-left
			if (point.y < 7 && point.x > 0)
			{
				if ((MainBoard[point.y + 1][point.x - 1] && MainBoard[point.y + 1][point.x - 1]->showColor() == black) || MainBoard[point.y + 1][point.x - 1] == nullptr)
				{
					(*listOfPossibleMoves).push_back({ point.y + 1, point.x - 1 });
				}
			}
		}
	
}

// jezeli jest szach to zwraca true
bool King::isCheck(vector<vector<MyAllPawns*>> MainBoard, MyPoint KingPosition, MyPoint reallyKingPosition)
{
	bool isCheck = false;
	
	if (KingPosition.x > 7 || KingPosition.y < 0 || reallyKingPosition.x > 7 || reallyKingPosition.y < 0 || MainBoard[reallyKingPosition.y][reallyKingPosition.x] == nullptr)
	{
		return false;
	}

	if (MainBoard[reallyKingPosition.y][reallyKingPosition.x]->showColor() == black)
	{
		// for opponent's king
		// up
		if (KingPosition.y - 1 >= 0 && MainBoard[KingPosition.y - 1][KingPosition.x] && MainBoard[KingPosition.y - 1][KingPosition.x]->showColor() == white && MainBoard[KingPosition.y - 1][KingPosition.x]->getName() == "King")
		{
			return true;
		}
		// down
		if (KingPosition.y + 1 < 8 && MainBoard[KingPosition.y + 1][KingPosition.x] && MainBoard[KingPosition.y + 1][KingPosition.x]->showColor() == white && MainBoard[KingPosition.y + 1][KingPosition.x]->getName() == "King")
		{
			return true;
		}
		// right
		if (KingPosition.x + 1 < 8 && MainBoard[KingPosition.y][KingPosition.x + 1] && MainBoard[KingPosition.y][KingPosition.x + 1]->showColor() == white && MainBoard[KingPosition.y][KingPosition.x + 1]->getName() == "King")
		{
			return true;
		}
		// left
		if (KingPosition.x - 1 >= 0 && MainBoard[KingPosition.y][KingPosition.x - 1] && MainBoard[KingPosition.y][KingPosition.x - 1]->showColor() == white && MainBoard[KingPosition.y][KingPosition.x - 1]->getName() == "King")
		{
			return true;
		}
		// up and right
		if (KingPosition.y - 1 >= 0 && KingPosition.x + 1 < 8 && MainBoard[KingPosition.y - 1][KingPosition.x + 1] && MainBoard[KingPosition.y - 1][KingPosition.x + 1]->showColor() == white && MainBoard[KingPosition.y - 1][KingPosition.x + 1]->getName() == "King")
		{
			return true;
		}
		// up and left
		if (KingPosition.y - 1 >= 0 && KingPosition.x - 1 >= 0 && MainBoard[KingPosition.y - 1][KingPosition.x - 1] && MainBoard[KingPosition.y - 1][KingPosition.x - 1]->showColor() == white && MainBoard[KingPosition.y - 1][KingPosition.x - 1]->getName() == "King")
		{
			return true;
		}
		// down and right
		if (KingPosition.y + 1 < 8 && KingPosition.x + 1 < 8 && MainBoard[KingPosition.y + 1][KingPosition.x + 1] && MainBoard[KingPosition.y + 1][KingPosition.x + 1]->showColor() == white && MainBoard[KingPosition.y + 1][KingPosition.x + 1]->getName() == "King")
		{
			return true;
		}
		// down and left
		if (KingPosition.y + 1 < 8 && KingPosition.x - 1 >= 0 && MainBoard[KingPosition.y + 1][KingPosition.x - 1] && MainBoard[KingPosition.y + 1][KingPosition.x - 1]->showColor() == white && MainBoard[KingPosition.y + 1][KingPosition.x - 1]->getName() == "King")
		{
			return true;
		}

		// up and right for pawn
		if ((KingPosition.y + 1 < 8 && KingPosition.x + 1 < 8) && MainBoard[KingPosition.y + 1][KingPosition.x + 1] && MainBoard[KingPosition.y + 1][KingPosition.x + 1]->showColor() == white && MainBoard[KingPosition.y + 1][KingPosition.x + 1]->getName() == "Pawn")
		{
			return true;
		}
		// down and left for pawn
		if ((KingPosition.y + 1 < 8 && KingPosition.x - 1 >= 0) && MainBoard[KingPosition.y + 1][KingPosition.x - 1] && MainBoard[KingPosition.y + 1][KingPosition.x - 1]->showColor() == white && MainBoard[KingPosition.y + 1][KingPosition.x - 1]->getName() == "Pawn")
		{
			return true;
		}

		// check from knight
		if ((KingPosition.y - 2 >= 0 && KingPosition.x - 1 >= 0) && MainBoard[KingPosition.y - 2][KingPosition.x - 1] && MainBoard[KingPosition.y - 2][KingPosition.x - 1]->showColor() == white && MainBoard[KingPosition.y - 2][KingPosition.x - 1]->getName() == "Knight")
		{
			return true;
		}
		if ((KingPosition.y - 2 >= 0 && KingPosition.x + 1 < 8) && MainBoard[KingPosition.y - 2][KingPosition.x + 1] && MainBoard[KingPosition.y - 2][KingPosition.x + 1]->showColor() == white && MainBoard[KingPosition.y - 2][KingPosition.x + 1]->getName() == "Knight")
		{
			return true;
		}
		if ((KingPosition.y + 2 < 8 && KingPosition.x - 1 >= 0) && MainBoard[KingPosition.y + 2][KingPosition.x - 1] && MainBoard[KingPosition.y + 2][KingPosition.x - 1]->showColor() == white && MainBoard[KingPosition.y + 2][KingPosition.x - 1]->getName() == "Knight")
		{
			return true;
		}
		if ((KingPosition.y + 2 < 8 && KingPosition.x + 1 < 8) && MainBoard[KingPosition.y + 2][KingPosition.x + 1] && MainBoard[KingPosition.y + 2][KingPosition.x + 1]->showColor() == white && MainBoard[KingPosition.y + 2][KingPosition.x + 1]->getName() == "Knight")
		{
			return true;
		}

		if ((KingPosition.y - 1 >= 0 && KingPosition.x - 2 >= 0) && MainBoard[KingPosition.y - 1][KingPosition.x - 2] && MainBoard[KingPosition.y - 1][KingPosition.x - 2]->showColor() == white && MainBoard[KingPosition.y - 1][KingPosition.x - 2]->getName() == "Knight")
		{
			return true;
		}
		if ((KingPosition.y - 1 >= 0 && KingPosition.x + 2 < 8) && MainBoard[KingPosition.y - 1][KingPosition.x + 2] && MainBoard[KingPosition.y - 1][KingPosition.x + 2]->showColor() == white && MainBoard[KingPosition.y - 1][KingPosition.x + 2]->getName() == "Knight")
		{
			return true;
		}
		if ((KingPosition.y + 1 < 8 && KingPosition.x - 2 >= 0) && MainBoard[KingPosition.y + 1][KingPosition.x - 2] && MainBoard[KingPosition.y + 1][KingPosition.x - 2]->showColor() == white && MainBoard[KingPosition.y + 1][KingPosition.x - 2]->getName() == "Knight")
		{
			return true;
		}
		if ((KingPosition.y + 1 < 8 && KingPosition.x + 2 < 8) && MainBoard[KingPosition.y + 1][KingPosition.x + 2] && MainBoard[KingPosition.y + 1][KingPosition.x + 2]->showColor() == white && MainBoard[KingPosition.y + 1][KingPosition.x + 2]->getName() == "Knight")
		{
			return true;
		}

		// right
		for (int j = KingPosition.x + 1; j < 8; j++)
		{
			if (MainBoard[KingPosition.y][j] == nullptr)
			{
				continue;
			}
			if (MainBoard[KingPosition.y][j]->showColor() == black)
			{
				break;
			}
			if (MainBoard[KingPosition.y][j]->showColor() == white && (MainBoard[KingPosition.y][j]->getName() == "Pawn" || MainBoard[KingPosition.y][j]->getName() == "Knight" || MainBoard[KingPosition.y][j]->getName() == "Bishop"))
			{
				break;
			}
			if (MainBoard[KingPosition.y][j]->showColor() == white && (MainBoard[KingPosition.y][j]->getName() == "Rook" || MainBoard[KingPosition.y][j]->getName() == "Queen"))
			{
				return true;
			}
		}

		// left
		for (int j = KingPosition.x - 1; j >= 0; j--)
		{
			if (MainBoard[KingPosition.y][j] == nullptr)
			{
				continue;
			}
			if (MainBoard[KingPosition.y][j]->showColor() == black)
			{
				break;
			}
			if (MainBoard[KingPosition.y][j]->showColor() == white && (MainBoard[KingPosition.y][j]->getName() == "Pawn" || MainBoard[KingPosition.y][j]->getName() == "Knight" || MainBoard[KingPosition.y][j]->getName() == "Bishop"))
			{
				break;
			}
			if (MainBoard[KingPosition.y][j]->showColor() == white && (MainBoard[KingPosition.y][j]->getName() == "Rook" || MainBoard[KingPosition.y][j]->getName() == "Queen"))
			{
				return true;
			}
		}

		// up
		for (int i = KingPosition.y - 1; i >= 0; i--)
		{
			if (MainBoard[i][KingPosition.x] == nullptr)
			{
				continue;
			}
			if (MainBoard[i][KingPosition.x]->showColor() == black)
			{
				break;
			}
			if (MainBoard[i][KingPosition.x]->showColor() == white && (MainBoard[i][KingPosition.x]->getName() == "Pawn" || MainBoard[i][KingPosition.x]->getName() == "Knight" || MainBoard[i][KingPosition.x]->getName() == "Bishop"))
			{
				break;
			}
			if (MainBoard[i][KingPosition.x]->showColor() == white && (MainBoard[i][KingPosition.x]->getName() == "Rook" || MainBoard[i][KingPosition.x]->getName() == "Queen"))
			{
				return true;
			}
		}

		// down
		for (int i = KingPosition.y + 1; i < 8 ; i++)
		{
			if (MainBoard[i][KingPosition.x] == nullptr)
			{
				continue;
			}
			if (MainBoard[i][KingPosition.x]->showColor() == black)
			{
				break;
			}
			if (MainBoard[i][KingPosition.x]->showColor() == white && (MainBoard[i][KingPosition.x]->getName() == "Pawn" || MainBoard[i][KingPosition.x]->getName() == "Knight" || MainBoard[i][KingPosition.x]->getName() == "Bishop"))
			{
				break;
			}
			if (MainBoard[i][KingPosition.x]->showColor() == white && (MainBoard[i][KingPosition.x]->getName() == "Rook" || MainBoard[i][KingPosition.x]->getName() == "Queen"))
			{
				return true;
			}
		}

		// up and right
		for (int i = KingPosition.y - 1, j = KingPosition.x + 1; i >= 0 && j < 8; i-- , j++)
		{
			if (MainBoard[i][j] == nullptr)
			{
				continue;
			}
			if (MainBoard[i][j]->showColor() == black)
			{
				break;
			}
			if (MainBoard[i][j]->showColor() == white && (MainBoard[i][j]->getName() == "Pawn" || MainBoard[i][j]->getName() == "Knight" || MainBoard[i][j]->getName() == "Rook"))
			{
				break;
			}
			if (MainBoard[i][j]->showColor() == white && (MainBoard[i][j]->getName() == "Bishop" || MainBoard[i][j]->getName() == "Queen"))
			{
				return true;
			}
		}

		// up and left
		for (int i = KingPosition.y - 1, j = KingPosition.x - 1; i >= 0 && j >= 0; i--, j--)
		{
			if (MainBoard[i][j] == nullptr)
			{
				continue;
			}
			if (MainBoard[i][j]->showColor() == black)
			{
				break;
			}
			if (MainBoard[i][j]->showColor() == white && (MainBoard[i][j]->getName() == "Pawn" || MainBoard[i][j]->getName() == "Knight" || MainBoard[i][j]->getName() == "Rook"))
			{
				break;
			}
			if (MainBoard[i][j]->showColor() == white && (MainBoard[i][j]->getName() == "Bishop" || MainBoard[i][j]->getName() == "Queen"))
			{
				return true;
			}
		}

		// down and right
		for (int i = KingPosition.y + 1, j = KingPosition.x + 1; i < 8 && j < 8; i++, j++)
		{
			if (MainBoard[i][j] == nullptr)
			{
				continue;
			}
			if (MainBoard[i][j]->showColor() == black)
			{
				break;
			}
			if (MainBoard[i][j]->showColor() == white && (MainBoard[i][j]->getName() == "Pawn" || MainBoard[i][j]->getName() == "Knight" || MainBoard[i][j]->getName() == "Rook"))
			{
				break;
			}
			if (MainBoard[i][j]->showColor() == white && (MainBoard[i][j]->getName() == "Bishop" || MainBoard[i][j]->getName() == "Queen"))
			{
				return true;
			}
		}

		// down and left
		for (int i = KingPosition.y + 1, j = KingPosition.x - 1; i < 8 && j >= 0; i++, j--)
		{
			if (MainBoard[i][j] == nullptr)
			{
				continue;
			}
			if (MainBoard[i][j]->showColor() == black)
			{
				break;
			}
			if (MainBoard[i][j]->showColor() == white && (MainBoard[i][j]->getName() == "Pawn" || MainBoard[i][j]->getName() == "Knight" || MainBoard[i][j]->getName() == "Rook"))
			{
				break;
			}
			if (MainBoard[i][j]->showColor() == white && (MainBoard[i][j]->getName() == "Bishop" || MainBoard[i][j]->getName() == "Queen"))
			{
				return true;
			}
		}
	}
	
	if (MainBoard[reallyKingPosition.y][reallyKingPosition.x]->showColor() == white)
	{
		// for opponent's king
		// up
		if (KingPosition.y - 1 >= 0 && MainBoard[KingPosition.y - 1][KingPosition.x] && MainBoard[KingPosition.y - 1][KingPosition.x]->showColor() == black && MainBoard[KingPosition.y - 1][KingPosition.x]->getName() == "King")
		{
			return true;
		}
		// down
		if (KingPosition.y + 1 < 8 && MainBoard[KingPosition.y + 1][KingPosition.x] && MainBoard[KingPosition.y + 1][KingPosition.x]->showColor() == black && MainBoard[KingPosition.y + 1][KingPosition.x]->getName() == "King")
		{
			return true;
		}
		// right
		if (KingPosition.x + 1 < 8 && MainBoard[KingPosition.y][KingPosition.x + 1] && MainBoard[KingPosition.y][KingPosition.x + 1]->showColor() == black && MainBoard[KingPosition.y][KingPosition.x + 1]->getName() == "King")
		{
			return true;
		}
		// left
		if (KingPosition.x - 1 >= 0 && MainBoard[KingPosition.y][KingPosition.x - 1] && MainBoard[KingPosition.y][KingPosition.x - 1]->showColor() == black && MainBoard[KingPosition.y][KingPosition.x - 1]->getName() == "King")
		{
			return true;
		}
		// up and right
		if (KingPosition.y - 1 >= 0 && KingPosition.x + 1 < 8 && MainBoard[KingPosition.y - 1][KingPosition.x + 1] && MainBoard[KingPosition.y - 1][KingPosition.x + 1]->showColor() == black && MainBoard[KingPosition.y - 1][KingPosition.x + 1]->getName() == "King")
		{
			return true;
		}
		// up and left
		if (KingPosition.y - 1 >= 0 && KingPosition.x - 1 >= 0 && MainBoard[KingPosition.y - 1][KingPosition.x - 1] && MainBoard[KingPosition.y - 1][KingPosition.x - 1]->showColor() == black && MainBoard[KingPosition.y - 1][KingPosition.x - 1]->getName() == "King")
		{
			return true;
		}
		// down and right
		if (KingPosition.y + 1 < 8 && KingPosition.x + 1 < 8 && MainBoard[KingPosition.y + 1][KingPosition.x + 1] && MainBoard[KingPosition.y + 1][KingPosition.x + 1]->showColor() == black && MainBoard[KingPosition.y + 1][KingPosition.x + 1]->getName() == "King")
		{
			return true;
		}
		// down and left
		if (KingPosition.y + 1 < 8 && KingPosition.x - 1 >= 0 && MainBoard[KingPosition.y + 1][KingPosition.x - 1] && MainBoard[KingPosition.y + 1][KingPosition.x - 1]->showColor() == black && MainBoard[KingPosition.y + 1][KingPosition.x - 1]->getName() == "King")
		{
			return true;
		}

		// up and right for pawn
		if ((KingPosition.y - 1 >= 0 && KingPosition.x + 1 < 8) && MainBoard[KingPosition.y - 1][KingPosition.x + 1] && MainBoard[KingPosition.y - 1][KingPosition.x + 1]->showColor() == black && MainBoard[KingPosition.y - 1][KingPosition.x + 1]->getName() == "Pawn")
		{
			return true;
		}
		// down and left for pawn
		if ((KingPosition.y - 1 >= 0 && KingPosition.x - 1 >= 0) && MainBoard[KingPosition.y - 1][KingPosition.x - 1] && MainBoard[KingPosition.y - 1][KingPosition.x - 1]->showColor() == black && MainBoard[KingPosition.y - 1][KingPosition.x - 1]->getName() == "Pawn")
		{
			return true;
		}

		// check from knight
		if ((KingPosition.y - 2 >= 0 && KingPosition.x - 1 >= 0) && MainBoard[KingPosition.y - 2][KingPosition.x - 1] && MainBoard[KingPosition.y - 2][KingPosition.x - 1]->showColor() == black && MainBoard[KingPosition.y - 2][KingPosition.x - 1]->getName() == "Knight")
		{
			return true;
		}
		if ((KingPosition.y - 2 >= 0 && KingPosition.x + 1 < 8) && MainBoard[KingPosition.y - 2][KingPosition.x + 1] && MainBoard[KingPosition.y - 2][KingPosition.x + 1]->showColor() == black && MainBoard[KingPosition.y - 2][KingPosition.x + 1]->getName() == "Knight")
		{
			return true;
		}
		if ((KingPosition.y + 2 < 8 && KingPosition.x - 1 >= 0) && MainBoard[KingPosition.y + 2][KingPosition.x - 1] && MainBoard[KingPosition.y + 2][KingPosition.x - 1]->showColor() == black && MainBoard[KingPosition.y + 2][KingPosition.x - 1]->getName() == "Knight")
		{
			return true;
		}
		if ((KingPosition.y + 2 < 8 && KingPosition.x + 1 < 8) && MainBoard[KingPosition.y + 2][KingPosition.x + 1] && MainBoard[KingPosition.y + 2][KingPosition.x + 1]->showColor() == black && MainBoard[KingPosition.y + 2][KingPosition.x + 1]->getName() == "Knight")
		{
			return true;
		}

		if ((KingPosition.y - 1 >= 0 && KingPosition.x - 2 >= 0) && MainBoard[KingPosition.y - 1][KingPosition.x - 2] && MainBoard[KingPosition.y - 1][KingPosition.x - 2]->showColor() == black && MainBoard[KingPosition.y - 1][KingPosition.x - 2]->getName() == "Knight")
		{
			return true;
		}
		if ((KingPosition.y - 1 >= 0 && KingPosition.x + 2 < 8) && MainBoard[KingPosition.y - 1][KingPosition.x + 2] && MainBoard[KingPosition.y - 1][KingPosition.x + 2]->showColor() == black && MainBoard[KingPosition.y - 1][KingPosition.x + 2]->getName() == "Knight")
		{
			return true;
		}
		if ((KingPosition.y + 1 < 8 && KingPosition.x - 2 >= 0) && MainBoard[KingPosition.y + 1][KingPosition.x - 2] && MainBoard[KingPosition.y + 1][KingPosition.x - 2]->showColor() == black && MainBoard[KingPosition.y + 1][KingPosition.x - 2]->getName() == "Knight")
		{
			return true;
		}
		if ((KingPosition.y + 1 < 8 && KingPosition.x + 2 < 8) && MainBoard[KingPosition.y + 1][KingPosition.x + 2] && MainBoard[KingPosition.y + 1][KingPosition.x + 2]->showColor() == black && MainBoard[KingPosition.y + 1][KingPosition.x + 2]->getName() == "Knight")
		{
			return true;
		}

		// right
		for (int j = KingPosition.x + 1; j < 8; j++)
		{
			if (MainBoard[KingPosition.y][j] == nullptr)
			{
				continue;
			}
			if (MainBoard[KingPosition.y][j]->showColor() == white)
			{
				break;
			}
			if (MainBoard[KingPosition.y][j]->showColor() == black && (MainBoard[KingPosition.y][j]->getName() == "Pawn" || MainBoard[KingPosition.y][j]->getName() == "Knight" || MainBoard[KingPosition.y][j]->getName() == "Bishop"))
			{
				break;
			}
			if (MainBoard[KingPosition.y][j]->showColor() == black && (MainBoard[KingPosition.y][j]->getName() == "Rook" || MainBoard[KingPosition.y][j]->getName() == "Queen"))
			{
				return true;
			}
		}

		// left
		for (int j = KingPosition.x - 1; j >= 0; j--)
		{
			if (MainBoard[KingPosition.y][j] == nullptr)
			{
				continue;
			}
			if (MainBoard[KingPosition.y][j]->showColor() == white)
			{
				break;
			}
			if (MainBoard[KingPosition.y][j]->showColor() == black && (MainBoard[KingPosition.y][j]->getName() == "Pawn" || MainBoard[KingPosition.y][j]->getName() == "Knight" || MainBoard[KingPosition.y][j]->getName() == "Bishop"))
			{
				break;
			}
			if (MainBoard[KingPosition.y][j]->showColor() == black && (MainBoard[KingPosition.y][j]->getName() == "Rook" || MainBoard[KingPosition.y][j]->getName() == "Queen"))
			{
				return true;
			}
		}

		// up
		for (int i = KingPosition.y - 1; i >= 0; i--)
		{
			if (MainBoard[i][KingPosition.x] == nullptr)
			{
				continue;
			}
			if (MainBoard[i][KingPosition.x]->showColor() == white)
			{
				break;
			}
			if (MainBoard[i][KingPosition.x]->showColor() == black && (MainBoard[i][KingPosition.x]->getName() == "Pawn" || MainBoard[i][KingPosition.x]->getName() == "Knight" || MainBoard[i][KingPosition.x]->getName() == "Bishop"))
			{
				break;
			}
			if (MainBoard[i][KingPosition.x]->showColor() == black && (MainBoard[i][KingPosition.x]->getName() == "Rook" || MainBoard[i][KingPosition.x]->getName() == "Queen"))
			{
				return true;
			}
		}

		// down
		for (int i = KingPosition.y + 1; i < 8; i++)
		{
			if (MainBoard[i][KingPosition.x] == nullptr)
			{
				continue;
			}
			if (MainBoard[i][KingPosition.x]->showColor() == white)
			{
				break;
			}
			if (MainBoard[i][KingPosition.x]->showColor() == black && (MainBoard[i][KingPosition.x]->getName() == "Pawn" || MainBoard[i][KingPosition.x]->getName() == "Knight" || MainBoard[i][KingPosition.x]->getName() == "Bishop"))
			{
				break;
			}
			if (MainBoard[i][KingPosition.x]->showColor() == black && (MainBoard[i][KingPosition.x]->getName() == "Rook" || MainBoard[i][KingPosition.x]->getName() == "Queen"))
			{
				return true;
			}
		}

		// up and right
		for (int i = KingPosition.y - 1, j = KingPosition.x + 1; i >= 0 && j < 8; i--, j++)
		{
			if (MainBoard[i][j] == nullptr)
			{
				continue;
			}
			if (MainBoard[i][j]->showColor() == white)
			{
				break;
			}
			if (MainBoard[i][j]->showColor() == black && (MainBoard[i][j]->getName() == "Pawn" || MainBoard[i][j]->getName() == "Knight" || MainBoard[i][j]->getName() == "Rook"))
			{
				break;
			}
			if (MainBoard[i][j]->showColor() == black && (MainBoard[i][j]->getName() == "Bishop" || MainBoard[i][j]->getName() == "Queen"))
			{
				return true;
			}
		}

		// up and left
		for (int i = KingPosition.y - 1, j = KingPosition.x - 1; i >= 0 && j >= 0; i--, j--)
		{
			if (MainBoard[i][j] == nullptr)
			{
				continue;
			}
			if (MainBoard[i][j]->showColor() == white)
			{
				break;
			}
			if (MainBoard[i][j]->showColor() == black && (MainBoard[i][j]->getName() == "Pawn" || MainBoard[i][j]->getName() == "Knight" || MainBoard[i][j]->getName() == "Rook"))
			{
				break;
			}
			if (MainBoard[i][j]->showColor() == black && (MainBoard[i][j]->getName() == "Bishop" || MainBoard[i][j]->getName() == "Queen"))
			{
				return true;
			}
		}

		// down and right
		for (int i = KingPosition.y + 1, j = KingPosition.x + 1; i < 8 && j < 8; i++, j++)
		{
			if (MainBoard[i][j] == nullptr)
			{
				continue;
			}
			if (MainBoard[i][j]->showColor() == white)
			{
				break;
			}
			if (MainBoard[i][j]->showColor() == black && (MainBoard[i][j]->getName() == "Pawn" || MainBoard[i][j]->getName() == "Knight" || MainBoard[i][j]->getName() == "Rook"))
			{
				break;
			}
			if (MainBoard[i][j]->showColor() == black && (MainBoard[i][j]->getName() == "Bishop" || MainBoard[i][j]->getName() == "Queen"))
			{
				return true;
			}
		}

		// down and left
		for (int i = KingPosition.y + 1, j = KingPosition.x - 1; i < 8 && j >= 0; i++, j--)
		{
			if (MainBoard[i][j] == nullptr)
			{
				continue;
			}
			if (MainBoard[i][j]->showColor() == white)
			{
				break;
			}
			if (MainBoard[i][j]->showColor() == black && (MainBoard[i][j]->getName() == "Pawn" || MainBoard[i][j]->getName() == "Knight" || MainBoard[i][j]->getName() == "Rook"))
			{
				break;
			}
			if (MainBoard[i][j]->showColor() == black && (MainBoard[i][j]->getName() == "Bishop" || MainBoard[i][j]->getName() == "Queen"))
			{
				return true;
			}
		}
	}
	return isCheck;
}

King::~King()
{}