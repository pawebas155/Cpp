#include "MainBoard.h"

Board::Board(bool isGameContinue, int gMode): AllMoves(), turn(true), isCheck(false), checkMat(false), willBeCheck(false), gameModeToSave(gMode)
{
	if (isGameContinue)
	{

	}
	else
	{
		setBoard();
	}
}

void Board::RestoreBoard(int pos_i, int pos_j, int tempColor, string tempName)
{
	MainBoard.resize(8, vector<MyAllPawns*>(8));

	if (tempName == "Pawn")
	{
		MainBoard[pos_i][pos_j] = new Pawn("Pawn", { pos_j, pos_i }, tempColor, 5);
	}
	if (tempName == "Rook")
	{
		MainBoard[pos_i][pos_j] = new Rook("Rook", { pos_j, pos_i }, tempColor, 2);
	}
	if (tempName == "Bishop")
	{
		MainBoard[pos_i][pos_j] = new Bishop("Bishop", { pos_j, pos_i }, tempColor, 4);
	}
	if (tempName == "Knight")
	{
		MainBoard[pos_i][pos_j] = new Knight("Knight", { pos_j, pos_i }, tempColor, 3);
	}
	if (tempName == "Queen")
	{
		MainBoard[pos_i][pos_j] = new Queen("Queen", { pos_j, pos_i }, tempColor, 1);
	}
	if (tempName == "King")
	{
		MainBoard[pos_i][pos_j] = new King("King", { pos_j, pos_i }, tempColor, 0);
	}

}

// utworzenie pionków 
void Board::setBoard()
{
	MainBoard.resize(8, vector<MyAllPawns*>(8));

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			MainBoard[i][j] = nullptr;
		}
	}

	// pionki lepsze czarne	
	MainBoard[0][0] = new Rook("Rook", { 0, 0 }, black, 2);
	MainBoard[0][1] = new Knight("Knight", { 0, 1 }, black, 3);
	MainBoard[0][2] = new Bishop("Bishop", { 0, 2 }, black, 4);
	MainBoard[0][3] = new Queen("Queen", { 0, 3 }, black, 1);
	MainBoard[0][4] = new King("King", { 0, 4 }, black, 0);
	MainBoard[0][5] = new Bishop("Bishop", { 0, 5 }, black, 4);
	MainBoard[0][6] = new Knight("Knight", { 0, 6 }, black, 3);
	MainBoard[0][7] = new Rook("Rook", { 0, 7 }, black, 2);
	// pionki lepsze bia³e
	MainBoard[7][0] = new Rook("Rook", { 7, 0 }, white, 2);
	MainBoard[7][1] = new Knight("Knight", { 7, 1 }, white, 3);
	MainBoard[7][2] = new Bishop("Bishop", { 7, 2 }, white, 4);
	MainBoard[7][3] = new Queen("Queen", { 7, 3 }, white, 1);
	MainBoard[7][4] = new King("King", { 7, 4 }, white, 0);
	MainBoard[7][5] = new Bishop("Bishop", { 7, 5 }, white, 4);
	MainBoard[7][6] = new Knight("Knight", { 7, 6 }, white, 3);
	MainBoard[7][7] = new Rook("Rook", { 7, 7 }, white, 2);
	
	for (int i = 0; i < 8; i++)
	{
		// pionki czarne
		MainBoard[1][i] = new Pawn("Pawn", { 1, i }, black, 5);
		// pionki bia³e
		MainBoard[6][i] = new Pawn("Pawn", { 6, i }, white, 5);
	}
}

const vector<vector<sf::Sprite*>> Board::ShowArrayOfSprite()
{
	vector<vector<sf::Sprite*>> tempArray;
	
	tempArray.resize(8, vector<sf::Sprite*>(8));

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (MainBoard[i][j] != nullptr)
			{
				(tempArray[i][j]) = (MainBoard[i][j]->getSprite());
			}
		}
	}
	return tempArray;
}

void Board::createPlayers()
{
	player[black] = new RealPlayer(black, &isCheck, &checkMat, &willBeCheck);
	player[white] = new RealPlayer(white, &isCheck, &checkMat, &willBeCheck);
}

void Board::createPlayerAndComputer()
{
	player[black] = new ComputerPlayer(white, &isCheck, &checkMat, &willBeCheck);
	player[white] = new RealPlayer(black, &isCheck, &checkMat, &willBeCheck);
}

bool Board::playerXTurn(MyPoint point)
{
	tempPawnPosition = point;
	if (turn == true)
	{
		tempPossibleMoves = player[white]->PlayerSpeculation(point, MainBoard, &AllMoves, white);
	}
	else
	{
		tempPossibleMoves = player[black]->PlayerSpeculation(point, MainBoard, &AllMoves, black);
	}
	if (!tempPossibleMoves->empty())
	{
		return false;
	}
	return true;
}

bool Board::playerXChoice(MyPoint point)
{
	MyPoint positionOfKing;

	if (turn == true)
	{
		if (player[white]->PlayerChoose(point, &MainBoard, &AllMoves, tempPawnPosition, &BoardOfDeathPawns))
		{
			turn = false;
			positionOfKing = findKingOnBoardOfColorX(black);
			isCheck = MainBoard[positionOfKing.y][positionOfKing.x]->isCheck(MainBoard, positionOfKing, positionOfKing);
		}
	}
	else
	{
		if (player[black]->PlayerChoose(point, &MainBoard, &AllMoves, tempPawnPosition, &BoardOfDeathPawns))
		{
			turn = true;
			positionOfKing = findKingOnBoardOfColorX(white);
			isCheck = MainBoard[positionOfKing.y][positionOfKing.x]->isCheck(MainBoard, positionOfKing, positionOfKing);
		}
	}
	if (tempPossibleMoves->empty())
	{
		return true;
	}
	return false;
}

MyPoint Board::findKingOnBoardOfColorX(int color)
{
	MyPoint temp = { -1, -1 };

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (MainBoard[i][j] != nullptr)
			{
				if (MainBoard[i][j]->getName() == "King" && MainBoard[i][j]->showColor() == color)
				{
					temp.x = j;
					temp.y = i;
					break;
				}
			}
		}
	}
	return temp;
}

list<MyPoint> *Board::sendPossibleMoves()
{
	return tempPossibleMoves;
}

// operator <<
ofstream & operator<< (ofstream &file, Board & temp)
{
	file << temp.gameModeToSave << endl;
	file << temp.showTurn() << endl;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (temp.MainBoard[i][j] != nullptr)
			{
				file << temp.MainBoard[i][j]->showColor() << " " << i << " " << j << " " << temp.MainBoard[i][j]->getName() << endl;
			}
		}
	}
	
	return file;
}

// operator >>
ifstream & operator >> (ifstream &file, Board * temp)
{
	int tempTurn;
	int tempColor;
	int pos_i, pos_j;
	string tempName;

	file >> (*temp).gameModeToSave;
	file >> tempTurn;
	
	(*temp).turn = tempTurn;

	while (!file.eof())
	{
		file >> tempColor >> pos_i >> pos_j >> tempName;
		cout << tempColor << " " << pos_i << " " << pos_j << " " << tempName;

		(*temp).RestoreBoard(pos_i, pos_j, tempColor, tempName);
	}
	return file;
}

int Board::showGameMode()
{
	return gameModeToSave;
}

void Board::showListOfMoves()
{
	AllMoves.showAllMoves();
}

bool Board::showIsCheck()
{
	return isCheck;
}

void Board::setIsCheck(bool x)
{
	isCheck = x;
}

bool Board::showCheckMat()
{
	return checkMat;
}

bool Board::showTurn()
{
	return turn;
}

void Board::doComputerMove()
{
	player[black]->ComputerMove(&MainBoard, &AllMoves, 2, black, &BoardOfDeathPawns);

	turn = true;
}

void Board::doUndoMove()
{
	player[white]->undoMove(&MainBoard, &AllMoves, &BoardOfDeathPawns);
}

void Board::saveToFile()
{
	AllMoves.saveMovesToFile();
}

bool Board::showWillBeCheck()
{
	return willBeCheck;
}

void Board::setWillBeCheck(bool x)
{
	willBeCheck = x;
}

void Board::deleteMyBoard()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (MainBoard[i][j] != nullptr)
			{
				MyAllPawns * pom = MainBoard[i][j];
				delete pom ;
				MainBoard[i][j] = nullptr;
			}
		}
	}
}

Board::~Board()
{
	deleteMyBoard();
}