#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer(int color, bool *tempIsCheck, bool *tempCheckMat, bool *tempWillBeCheck) : Player(color, tempIsCheck, tempCheckMat, tempWillBeCheck)//, ComputerPlayer(color, tempIsCheck, tempCheckMat, tempWillBeCheck)
{
	setBoardPointsForPawns();
	setPointsForPawns();
}

void ComputerPlayer::setBoardPointsForPawns()
{
	int tab1[8][8] =
	{
		 0,  0,  0,  0,  0,  0,  0,  0,
		50, 50, 50, 50, 50, 50, 50, 50,
		10, 10, 20, 30, 30, 20, 10, 10,
		 5,  5, 10, 25, 25, 10,  5,  5,
		 0,  0,  0, 20, 25,  0,  0,  0,
		 5, -5, -10, 0,  0,-10, -5,  5,
		 5, 10, 10,-20,-20, 10, 10,  5,
		 0,  0,  0,  0,  0,  0,  0,  0
	};
	swap(PawnPoints, tab1);
	
	int tab2[8][8] =
	{
		0,  0,  0,  0,  0,  0,  0,  0,
		5, 10, 10, 10, 10, 10, 10,  5,
		-5,  0,  0,  0,  0,  0,  0, -5,
		-5,  0,  0,  0,  0,  0,  0, -5,
		-5,  0,  0,  0,  0,  0,  0, -5,
		-5,  0,  0,  0,  0,  0,  0, -5,
		-5,  0,  0,  0,  0,  0,  0, -5,
		0,  0,  0,  5,  5,  0,  0,  0
	};
	swap(RookPoints, tab2);

	int tab3[8][8] =
	{
		-50,-40,-30,-30,-30,-30,-40,-50,
		-40,-20,  0,  0,  0,  0,-20,-40,
		-30,  0, 10, 15, 15, 10,  0,-30,
		-30,  5, 15, 20, 20, 15,  5,-30,
		-30,  0, 15, 20, 20, 15,  0,-30,
		-30,  5, 10, 15, 15, 10,  5,-30,
		-40,-20,  0,  5,  5,  0,-20,-40,
		-50,-40,-30,-30,-30,-30,-40,-50
	};
	swap(KnightPoints, tab3);

	int tab4[8][8] =
	{
		-20,-10,-10,-10,-10,-10,-10,-20,
		-10,  0,  0,  0,  0,  0,  0,-10,
		-10,  0,  5, 10, 10,  5,  0,-10,
		-10,  5,  5, 10, 10,  5,  5,-10,
		-10,  0, 10, 10, 10, 10,  0,-10,
		-10, 10, 10, 10, 10, 10, 10,-10,
		-10,  5,  0,  0,  0,  0,  5,-10,
		-20,-10,-10,-10,-10,-10,-10,-20
	};
	swap(BishopPoints, tab4);

	int tab5[8][8] =
	{
		-20,-10,-10, -5, -5,-10,-10,-20,
		-10,  0,  0,  0,  0,  0,  0,-10,
		-10,  0,  5,  5,  5,  5,  0,-10,
		-5,  0,  5,  5,  5,  5,  0, -5,
		0,  0,  5,  5,  5,  5,  0, -5,
		-10,  5,  5,  5,  5,  5,  0,-10,
		-10,  0,  5,  0,  0,  0,  0,-10,
		-20,-10,-10, -5, -5,-10,-10,-20
	};
	swap(QueenPoints, tab5);

	int tab6[8][8] =
	{
		-30,-40,-40,-50,-50,-40,-40,-30,
		-30,-40,-40,-50,-50,-40,-40,-30,
		-30,-40,-40,-50,-50,-40,-40,-30,
		-30,-40,-40,-50,-50,-40,-40,-30,
		-20,-30,-30,-40,-40,-30,-30,-20,
		-10,-20,-20,-20,-20,-20,-20,-10,
		20, 20,  0,  0,  0,  0, 20, 20,
		20, 30, 10,  0,  0, 10, 30, 20
	};
	swap(KingPoints, tab6);

	int tab7[8][8] =
	{
		-50,-40,-30,-20,-20,-30,-40,-50,
		-30,-20,-10,  0,  0,-10,-20,-30,
		-30,-10, 20, 30, 30, 20,-10,-30,
		-30,-10, 30, 40, 40, 30,-10,-30,
		-30,-10, 30, 40, 40, 30,-10,-30,
		-30,-10, 20, 30, 30, 20,-10,-30,
		-30,-30,  0,  0,  0,  0,-30,-30,
		-50,-30,-30,-30,-30,-30,-30,-50
	};
	swap(KingPointsEndGame, tab7);

}

void ComputerPlayer::setPointsForPawns()
{
	PawnPower = 100;
	RookPower = 500;
	KnightPower = 320;
	BishopPower = 330;
	QueenPower = 900;
	KingPower = 20000;
}

void ComputerPlayer::ComputerMove(vector<vector<MyAllPawns*>> *Board, Moves * allMoves, int TreeDepth, int tempColor, vector<MyAllPawns*> * ArrayOfDeathPawn)
{
	int Value = -99999;
	int currentValue = -99999;
	MyPoint moveFrom;
	MyPoint moveTo;

	int color = tempColor;
	int enemyColor;
	if (tempColor == black)
	{
		enemyColor = white;
	}
	else
	{
		enemyColor = black;
	}

	list<MyPoint> tempMoves;
	list<MyPoint>::iterator it;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((*Board)[i][j] != nullptr && (*Board)[i][j]->showColor() == tempColor)
			{
				(*Board)[i][j]->CheckPossibleMoves({ j,i }, *Board, allMoves, &PossibleMoves);

				for (it = PossibleMoves.begin(); it != PossibleMoves.end(); it++)
				{
					tempMoves.push_back({it->y, it->x});
				}

				while (tempMoves.empty() == false)
				{
					it = tempMoves.begin();

					moveThePawn((*it), Board, allMoves, { j,i }, false, ArrayOfDeathPawn);

					MiniMax(Board, allMoves, TreeDepth - 1, enemyColor, &currentValue, tempColor, ArrayOfDeathPawn);

					if (currentValue > Value)
					{
						Value = currentValue;
						moveFrom.x = j;
						moveFrom.y = i;
						moveTo = (*it);
					}
					tempMoves.pop_front();
					undoMove(Board, allMoves, ArrayOfDeathPawn);
				}
			}
		}
	}
	moveThePawn(moveTo, Board, allMoves, moveFrom, true, ArrayOfDeathPawn);
}

void ComputerPlayer::MiniMax(vector<vector<MyAllPawns*>> *Board, Moves * allMoves, int TreeDepth, int tempColor, int *BoardValue, int ComputerPlayerColor, vector<MyAllPawns*> * ArrayOfDeathPawn)
{
	int color = tempColor;
	int enemyColor;
	if (tempColor == black)
	{
		enemyColor = white;
	}
	else
	{
		enemyColor = black;
	}

	int enemyForComputerPlayerColor;
	if (ComputerPlayerColor == black)
	{
		enemyForComputerPlayerColor = white;
	}
	else
	{
		enemyForComputerPlayerColor = black;
	}

	list<MyPoint> tempMoves;
	list<MyPoint>::iterator it;

	if (TreeDepth > 0)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if ((*Board)[i][j] != nullptr && (*Board)[i][j]->showColor() == tempColor)
				{
					(*Board)[i][j]->CheckPossibleMoves({ j,i }, *Board, allMoves, &PossibleMoves);

					for (it = PossibleMoves.begin(); it != PossibleMoves.end(); it++)
					{
						tempMoves.push_back({ it->y, it->x });
					}

					while (tempMoves.empty() == false)
					{
						it = tempMoves.begin();

						moveThePawn(*it, Board, allMoves, { j,i }, false, ArrayOfDeathPawn);

						MiniMax(Board, allMoves, TreeDepth - 1, enemyColor, BoardValue, ComputerPlayerColor, ArrayOfDeathPawn);

						if (TreeDepth - 1 == 0)
						{
							int Value1 = countBoardPoints(Board, ComputerPlayerColor);
							int Value2 = countBoardPoints(Board, enemyForComputerPlayerColor);
							int Value3 = Value1 - Value2;
							if (Value3 > *BoardValue)
							{
								*BoardValue = Value3;
							}
						}
						tempMoves.pop_front();
						undoMove(Board, allMoves, ArrayOfDeathPawn);
					}
				}
			}
		}
	}
}

int ComputerPlayer::countBoardPoints(vector<vector<MyAllPawns*>> *Board, int color)
{
	int value = 0;

	if (color == white)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if ((*Board)[i][j] != nullptr && (*Board)[i][j]->showColor() == color)
				{
					if ((*Board)[i][j]->getName() == "Pawn")
					{
						value += PawnPower;
						value += PawnPoints[i][j];
					}
					if ((*Board)[i][j]->getName() == "Rook")
					{
						value += RookPower;
						value += RookPoints[i][j];
					}
					if ((*Board)[i][j]->getName() == "Knight")
					{
						value += KnightPower;
						value += KnightPoints[i][j];
					}
					if ((*Board)[i][j]->getName() == "Bishop")
					{
						value += BishopPower;
						value += BishopPoints[i][j];
					}
					if ((*Board)[i][j]->getName() == "Queen")
					{
						value += QueenPower;
						value += QueenPoints[i][j];
					}
					if ((*Board)[i][j]->getName() == "King")
					{
						value += KingPower;
						value += KingPoints[i][j];
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if ((*Board)[i][j] != nullptr && (*Board)[i][j]->showColor() == color)
				{
					if ((*Board)[i][j]->getName() == "Pawn")
					{
						value += PawnPower;
						value += PawnPoints[7 - i][7 - j];
					}
					if ((*Board)[i][j]->getName() == "Rook")
					{
						value += RookPower;
						value += RookPoints[7 - i][7 - j];
					}
					if ((*Board)[i][j]->getName() == "Knight")
					{
						value += KnightPower;
						value += KnightPoints[7 - i][7 - j];
					}
					if ((*Board)[i][j]->getName() == "Bishop")
					{
						value += BishopPower;
						value += BishopPoints[7 - i][7 - j];
					}
					if ((*Board)[i][j]->getName() == "Queen")
					{
						value += QueenPower;
						value += QueenPoints[7 - i][7 - j];
					}
					if ((*Board)[i][j]->getName() == "King")
					{
						value += KingPower;
						value += KingPoints[7 - i][7 - j];
					}
				}
			}
		}
	}

	return value;
}

list<MyPoint> *ComputerPlayer::PlayerSpeculation(MyPoint point, vector<vector<MyAllPawns*>> Board, Moves * allMoves, int playerColor)
{	
	return &PossibleMoves;
}

bool ComputerPlayer::PlayerChoose(MyPoint point, vector<vector<MyAllPawns*>> *Board, Moves * allMoves, MyPoint tempPawnPosition, vector<MyAllPawns*> * ArrayOfDeathPawn)
{
	return false;
}

void ComputerPlayer::moveThePawn(MyPoint point, vector<vector<MyAllPawns*>> *Board, Moves * allMoves, MyPoint tempPawnPosition, bool writeMoveToList, vector<MyAllPawns*> * ArrayOfDeathPawn)
{
	MyPoint pointFrom;
	MyPoint pointTo;
	int color = (*Board)[tempPawnPosition.y][tempPawnPosition.x]->showColor();
	int enemycolor;

	if (color == white)
	{
		enemycolor = black;
	}
	else
	{
		enemycolor = white;
	}

	// dla czarnego krola
	if (tempPawnPosition.y == 0 && tempPawnPosition.x == 4 && (*Board)[tempPawnPosition.y][tempPawnPosition.x]
		&& (*Board)[tempPawnPosition.y][tempPawnPosition.x]->getName() == "King"
		&& point.y == 0 && point.x == 0 && (*Board)[point.y][point.x] && (*Board)[point.y][point.x]->getName() == "Rook")
	{
		(*Board)[0][2] = (*Board)[tempPawnPosition.y][tempPawnPosition.x];
		(*Board)[tempPawnPosition.y][tempPawnPosition.x] = nullptr;

		(*Board)[0][3] = (*Board)[point.y][point.x];
		(*Board)[point.y][point.x] = nullptr;

		//if (writeMoveToList)
		{
			// 1. wpisanie ruchu króla
			pointFrom = tempPawnPosition;
			pointTo = { 2,0 };
			allMoves->AddToList(pointFrom, pointTo, color, -1);
			// 2. wpisanie imitacji ruchu bialego (-1,-1) -> (-1,-1)
			pointFrom = { -1,-1 };
			pointTo = { -1,-1 };
			allMoves->AddToList(pointFrom, pointTo, enemycolor, -1);
			// 3. wpisanie ruchu czarnego wierzy
			pointFrom = point;
			pointTo = { 3,0 };
			allMoves->AddToList(pointFrom, pointTo, color, -1);
		}
		return;
	}

	if (tempPawnPosition.y == 0 && tempPawnPosition.x == 4 && (*Board)[tempPawnPosition.y][tempPawnPosition.x]
		&& (*Board)[tempPawnPosition.y][tempPawnPosition.x]->getName() == "King"
		&& point.y == 0 && point.x == 7 && (*Board)[point.y][point.x] && (*Board)[point.y][point.x]->getName() == "Rook")
	{
		(*Board)[0][6] = (*Board)[tempPawnPosition.y][tempPawnPosition.x];
		(*Board)[tempPawnPosition.y][tempPawnPosition.x] = nullptr;

		(*Board)[0][5] = (*Board)[point.y][point.x];
		(*Board)[point.y][point.x] = nullptr;

		//if (writeMoveToList)
		{
			// 1. wpisanie ruchu króla
			pointFrom = tempPawnPosition;
			pointTo = { 6,0 };
			allMoves->AddToList(pointFrom, pointTo, color, -1);
			// 2. wpisanie imitacji ruchu bialego (-1,-1) -> (-1,-1)
			pointFrom = { -1,-1 };
			pointTo = { -1,-1 };
			allMoves->AddToList(pointFrom, pointTo, enemycolor, -1);
			// 3. wpisanie ruchu czarnego wierzy
			pointFrom = point;
			pointTo = { 5,0 };
			allMoves->AddToList(pointFrom, pointTo, color, -1);
		}
		return;
	}
	// dla czarnego krola

	// dla bia³ego krola
	if (tempPawnPosition.y == 7 && tempPawnPosition.x == 4 && (*Board)[tempPawnPosition.y][tempPawnPosition.x]
		&& (*Board)[tempPawnPosition.y][tempPawnPosition.x]->getName() == "King"
		&& point.y == 7 && point.x == 0 && (*Board)[point.y][point.x] && (*Board)[point.y][point.x]->getName() == "Rook")
	{
		(*Board)[7][2] = (*Board)[tempPawnPosition.y][tempPawnPosition.x];
		(*Board)[tempPawnPosition.y][tempPawnPosition.x] = nullptr;

		(*Board)[7][3] = (*Board)[point.y][point.x];
		(*Board)[point.y][point.x] = nullptr;

		//if (writeMoveToList)
		{
			// 1. wpisanie ruchu króla
			pointFrom = tempPawnPosition;
			pointTo = { 2,7 };
			allMoves->AddToList(pointFrom, pointTo, color, -1);
			// 2. wpisanie imitacji ruchu bialego (-1,-1) -> (-1,-1)
			pointFrom = { -1,-1 };
			pointTo = { -1,-1 };
			allMoves->AddToList(pointFrom, pointTo, enemycolor, -1);
			// 3. wpisanie ruchu czarnego wierzy
			pointFrom = point;
			pointTo = { 3,7 };
			allMoves->AddToList(pointFrom, pointTo, color, -1);
		}
		return;
	}

	if (tempPawnPosition.y == 7 && tempPawnPosition.x == 4 && (*Board)[tempPawnPosition.y][tempPawnPosition.x]
		&& (*Board)[tempPawnPosition.y][tempPawnPosition.x]->getName() == "King"
		&& point.y == 7 && point.x == 7 && (*Board)[point.y][point.x] && (*Board)[point.y][point.x]->getName() == "Rook")
	{
		(*Board)[7][6] = (*Board)[tempPawnPosition.y][tempPawnPosition.x];
		(*Board)[tempPawnPosition.y][tempPawnPosition.x] = nullptr;

		(*Board)[7][5] = (*Board)[point.y][point.x];
		(*Board)[point.y][point.x] = nullptr;

		//if (writeMoveToList)
		{
			// 1. wpisanie ruchu króla
			pointFrom = tempPawnPosition;
			pointTo = { 6,7 };
			allMoves->AddToList(pointFrom, pointTo, color, -1);
			// 2. wpisanie imitacji ruchu bialego (-1,-1) -> (-1,-1)
			pointFrom = { -1,-1 };
			pointTo = { -1,-1 };
			allMoves->AddToList(pointFrom, pointTo, enemycolor, -1);
			// 3. wpisanie ruchu czarnego wierzy
			pointFrom = point;
			pointTo = { 5,7 };
			allMoves->AddToList(pointFrom, pointTo, color, -1);
		}
		return;
	}
	// dla bia³ego krola

	if ((*Board)[point.y][point.x] == nullptr)
	{
		(*Board)[point.y][point.x] = (*Board)[tempPawnPosition.y][tempPawnPosition.x];
		(*Board)[tempPawnPosition.y][tempPawnPosition.x] = nullptr;
		// wpisywanie do listy ruchów
		
		//if (writeMoveToList)
		{
			pointFrom = tempPawnPosition;
			pointTo = point;
			allMoves->AddToList(pointFrom, pointTo, color, -1);
		}

	}
	else
	{
		//delete (*Board)[point.y][point.x];
		MyAllPawns * tempDestroyedPawn = (*Board)[point.y][point.x];
		(*Board)[point.y][point.x] = nullptr;

		(*Board)[point.y][point.x] = (*Board)[tempPawnPosition.y][tempPawnPosition.x];
		(*Board)[tempPawnPosition.y][tempPawnPosition.x] = nullptr;

		//if (writeMoveToList)
		{
			pointFrom = tempPawnPosition;
			pointTo = point;
			(*ArrayOfDeathPawn).push_back(tempDestroyedPawn);
			int s = (*ArrayOfDeathPawn).size() - 1;
			

			allMoves->AddToList(pointFrom, pointTo, color, s);
		}
	}
}

void ComputerPlayer::undoMove(vector<vector<MyAllPawns*>> *Board, Moves * allMoves, vector<MyAllPawns*> * ArrayOfDeathPawn)
{
	LastMove tempLastMove = allMoves->showLastMove();
	LastMove tempLastButNotLeastMove = allMoves->showLastButNotLeastMove();
	
	if (tempLastButNotLeastMove.pointFrom.x != -5)
	{
		// cofanie roszady
		if (tempLastButNotLeastMove.pointFrom.x == -1 && tempLastButNotLeastMove.pointFrom.y == -1)
		{
			(*Board)[tempLastMove.pointFrom.y][tempLastMove.pointFrom.x] = (*Board)[tempLastMove.pointTo.y][tempLastMove.pointTo.x];
			(*Board)[tempLastMove.pointTo.y][tempLastMove.pointTo.x] = nullptr;
			allMoves->deleteFirstPossibleMove();
			allMoves->deleteFirstPossibleMove();
			
			tempLastMove = allMoves->showLastMove();


			(*Board)[tempLastMove.pointFrom.y][tempLastMove.pointFrom.x] = (*Board)[tempLastMove.pointTo.y][tempLastMove.pointTo.x];
			(*Board)[tempLastMove.pointTo.y][tempLastMove.pointTo.x] = nullptr;
			allMoves->deleteFirstPossibleMove();

			return;
		}
		// cofanie roszady

		// cofanie zwyklego ruchu
		(*Board)[tempLastMove.pointFrom.y][tempLastMove.pointFrom.x] = (*Board)[tempLastMove.pointTo.y][tempLastMove.pointTo.x];
		(*Board)[tempLastMove.pointTo.y][tempLastMove.pointTo.x] = nullptr;

		if (tempLastMove.positionInArrayOfDeathPawns >= 0)
		{
			(*Board)[tempLastMove.pointTo.y][tempLastMove.pointTo.x] = (*ArrayOfDeathPawn)[tempLastMove.positionInArrayOfDeathPawns];
			(*ArrayOfDeathPawn)[tempLastMove.positionInArrayOfDeathPawns] = nullptr;
			(*ArrayOfDeathPawn).pop_back();
		}
		allMoves->deleteFirstPossibleMove();
		// cofanie zwyklego ruchu
	}
	else
	{
		if (tempLastMove.pointFrom.x >= 0)
		{
			// cofanie zwyklego ruchu
			(*Board)[tempLastMove.pointFrom.y][tempLastMove.pointFrom.x] = (*Board)[tempLastMove.pointTo.y][tempLastMove.pointTo.x];
			(*Board)[tempLastMove.pointTo.y][tempLastMove.pointTo.x] = nullptr;

			if (tempLastMove.positionInArrayOfDeathPawns >= 0)
			{
				(*Board)[tempLastMove.pointTo.y][tempLastMove.pointTo.x] = (*ArrayOfDeathPawn)[tempLastMove.positionInArrayOfDeathPawns];
				(*ArrayOfDeathPawn)[tempLastMove.positionInArrayOfDeathPawns] = nullptr;
				(*ArrayOfDeathPawn).pop_back();
			}
			allMoves->deleteFirstPossibleMove();
			// cofanie zwyklego ruchu
		}
	}
}