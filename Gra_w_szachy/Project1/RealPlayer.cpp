#include "RealPlayer.h"

RealPlayer::RealPlayer(int color, bool *tempIsCheck, bool *tempCheckMat, bool *tempWillBeCheck) : Player( color, tempIsCheck, tempCheckMat, tempWillBeCheck)//, RealPlayer(color, tempIsCheck, tempCheckMat, tempWillBeCheck)
{}

list<MyPoint> *RealPlayer::PlayerSpeculation(MyPoint point, vector<vector<MyAllPawns*>> Board, Moves * allMoves, int playerColor)
{
	if (point.x == -1 || point.y == -1)
	{
		return &PossibleMoves;
	}

	if (Board[point.y][point.x] != nullptr)
	{
		if (Board[point.y][point.x]->showColor() == playerColor)
		{
			Board[point.y][point.x]->CheckPossibleMoves(point, Board, allMoves, &PossibleMoves);
		}
	}
	return &PossibleMoves;
}

bool RealPlayer::PlayerChoose(MyPoint point, vector<vector<MyAllPawns*>> *Board, Moves * allMoves, MyPoint tempPawnPosition, vector<MyAllPawns*> * ArrayOfDeathPawn)
{
	// kopiowanie tablicy orginalnej do pomocniczej
	vector<vector<MyAllPawns*>> pomBoard;
	pomBoard.resize(8, vector<MyAllPawns*>(8));
	
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((*Board)[i][j] == nullptr)
			{
				continue;
			}
			if ((*Board)[i][j]->getName() == "Pawn")
			{
				pomBoard[i][j] = new Pawn("Pawn", { i, j }, (*Board)[i][j]->showColor(), 5);
			}
			if ((*Board)[i][j]->getName() == "Rook")
			{
				pomBoard[i][j] = new Rook("Rook", { i, j }, (*Board)[i][j]->showColor(), 2);
			}
			if ((*Board)[i][j]->getName() == "Knight")
			{
				pomBoard[i][j] = new Knight("Knight", { i, j }, (*Board)[i][j]->showColor(), 3);
			}
			if ((*Board)[i][j]->getName() == "Bishop")
			{
				pomBoard[i][j] = new Bishop("Bishop", { i, j }, (*Board)[i][j]->showColor(), 4);
			}
			if ((*Board)[i][j]->getName() == "Queen")
			{
				pomBoard[i][j] = new Queen("Queen", { i, j }, (*Board)[i][j]->showColor(), 1);
			}
			if ((*Board)[i][j]->getName() == "King")
			{
				pomBoard[i][j] = new King("King", { i, j }, (*Board)[i][j]->showColor(), 0);
			}
		}
	}
	// kopiowanie tablicy orginalnej do pomocniczej

	int tempColor = (*Board)[tempPawnPosition.y][tempPawnPosition.x]->showColor();
	int otherColor;
	MyPoint tempPositionOfKing;

	if (tempColor == white)
	{
		otherColor = black;
	}
	else
	{
		otherColor = white;
	}

	if (!PossibleMoves.empty())
	{
		list<MyPoint>::iterator it = PossibleMoves.begin();
		for (; it != PossibleMoves.end(); it++)
		{
			if (point.y == it->x && point.x == it->y)
			{
				moveThePawn(point, &pomBoard, allMoves, tempPawnPosition, false, ArrayOfDeathPawn);

				// finding king
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						if (pomBoard[i][j] != nullptr)
						{
							if (pomBoard[i][j]->getName() == "King" && pomBoard[i][j]->showColor() == tempColor)
							{
								tempPositionOfKing.x = j;
								tempPositionOfKing.y = i;
								break;
							}
						}
					}
				}
				// finding king

				if (pomBoard[tempPositionOfKing.y][tempPositionOfKing.x]->isCheck(pomBoard, tempPositionOfKing, tempPositionOfKing))
				{
					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 8; j++)
						{
							if ((pomBoard)[i][j] != nullptr)
							{
								delete pomBoard[i][j];
							}
						}
					}
					*willBeCheck = true;
					return false;
				}

				// usuwanie tablicy pomocniczej
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						if ((pomBoard)[i][j] != nullptr)
						{
							delete pomBoard[i][j];
						}
					}
				}
				// usuwanie tablicy pomocniczej

				moveThePawn(point, Board, allMoves, tempPawnPosition, true, ArrayOfDeathPawn);
				
				// funkcja promocji pionka
				// dla czarnych
				if ((*Board)[point.y][point.x] && (*Board)[point.y][point.x]->showColor() == black &&
					(*Board)[point.y][point.x]->getName() == "Pawn" && point.y == 7)
				{
					int number = 0;
					int color = (*Board)[point.y][point.x]->showColor();

					cout << "Wybierz na jak¹ figure chcesz zamienic pionka i zatwierdz enter: " << endl;
					cout << "1. Queen  - Krolowa" << endl;
					cout << "2. Rook   - Wieza" << endl;
					cout << "3. Bishop - Goniec" << endl;
					cout << "4. Knight - Kon" << endl;
					do
					{
						cin >> number;
					} while (number < 1 && number > 4);

					switch (number)
					{
					case 1:
					{
						delete (*Board)[point.y][point.x];
						(*Board)[point.y][point.x] = new Queen("Queen", point, color, 1);
						break;
					}
					case 2:
					{
						delete (*Board)[point.y][point.x];
						(*Board)[point.y][point.x] = new Rook("Rook", point, color, 2);
						break;
					}
					case 3:
					{
						delete (*Board)[point.y][point.x];
						(*Board)[point.y][point.x] = new Bishop("Bishop", point, color, 4);
						break;
					}
					case 4:
					{
						delete (*Board)[point.y][point.x];
						(*Board)[point.y][point.x] = new Knight("Knight", tempPawnPosition, color, 3);
						break;
					}
					default:
						break;
					}
				}

				// dla bia³ych
				if ((*Board)[point.y][point.x] && (*Board)[point.y][point.x]->showColor() == white &&
					(*Board)[point.y][point.x]->getName() == "Pawn" && point.y == 0)
				{
					int number = 0;
					int color = (*Board)[point.y][point.x]->showColor();

					cout << "Wybierz na jak¹ figure chcesz zamienic pionka i zatwierdz enter: " << endl;
					cout << "1. Queen  - Krolowa" << endl;
					cout << "2. Rook   - Wieza" << endl;
					cout << "3. Bishop - Goniec" << endl;
					cout << "4. Knight - Kon" << endl;
					do
					{
						cin >> number;
					} while (number < 1 && number > 4);

					switch (number)
					{
					case 1:
					{
						delete (*Board)[point.y][point.x];
						(*Board)[point.y][point.x] = new Queen("Queen", point, color, 1);
						break;
					}
					case 2:
					{
						delete (*Board)[point.y][point.x];
						(*Board)[point.y][point.x] = new Rook("Rook", point, color, 2);
						break;
					}
					case 3:
					{
						delete (*Board)[point.y][point.x];
						(*Board)[point.y][point.x] = new Bishop("Bishop", point, color, 4);
						break;
					}
					case 4:
					{
						delete (*Board)[point.y][point.x];
						(*Board)[point.y][point.x] = new Knight("Knight", tempPawnPosition, color, 3);
						break;
					}
					default:
						break;
					}
				}
				// funkcja promocji pionka
				PossibleMoves.clear();
				*willBeCheck = false;
				return true;
			}
		}
		if (point.x != -1 && point.y != -1)
		{
			PossibleMoves.clear();
		}
	}

	return false;
}

void RealPlayer::moveThePawn(MyPoint point, vector<vector<MyAllPawns*>> *Board, Moves * allMoves, MyPoint tempPawnPosition, bool writeMoveToList, vector<MyAllPawns*> * ArrayOfDeathPawn)
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

		if (writeMoveToList)
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

		if (writeMoveToList)
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

		if (writeMoveToList)
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

		if (writeMoveToList)
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
		
		if (writeMoveToList)
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

		if (writeMoveToList)
		{
			pointFrom = tempPawnPosition;
			pointTo = point;
			(*ArrayOfDeathPawn).push_back(tempDestroyedPawn);
			int s = (*ArrayOfDeathPawn).size() - 1;


			allMoves->AddToList(pointFrom, pointTo, color, s);
		}
	}
}

void RealPlayer::undoMove(vector<vector<MyAllPawns*>> *Board, Moves * allMoves, vector<MyAllPawns*> * ArrayOfDeathPawn)
{}

void RealPlayer::setBoardPointsForPawns()
{}

void RealPlayer::setPointsForPawns()
{}

void RealPlayer::ComputerMove(vector<vector<MyAllPawns*>> *Board, Moves * allMoves, int TreeDepth, int tempColor, vector<MyAllPawns*> * ArrayOfDeathPawn)
{}

void RealPlayer::MiniMax( vector<vector<MyAllPawns*>> *Board, Moves * allMoves, int TreeDepth, int tempColor, int *BoardValue, int ComputerPlayerColor, vector<MyAllPawns*> * ArrayOfDeathPawn)
{}

int RealPlayer::countBoardPoints(vector<vector<MyAllPawns*>> *Board, int color)
{
	return 0;
}