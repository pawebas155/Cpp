#include "Moves.h"

Moves::Moves() : head(nullptr)
{}

//konstruktor kopiuj¹cy
Moves::Moves(const Moves & right)
{
	MoveElement * pom = right.head;
	MoveElement * tempTail = nullptr;

	if (right.head == nullptr)
	{
		head = nullptr;
	}
	else
	{
		head = new MoveElement({ right.head->pointFrom, right.head->pointTo, right.head->Color, right.head->positionInArrayOfDeathPawns, nullptr });
		tempTail = head;
		pom = pom->next;
		while (pom != nullptr)
		{
			tempTail->next = new MoveElement({ right.head->pointFrom, right.head->pointTo, right.head->Color, right.head->positionInArrayOfDeathPawns, nullptr });
			pom = pom->next;
			tempTail = tempTail->next;
		}
	}
}

//konstruktor przenosz¹cy
Moves::Moves(Moves &&right)
{
	head = right.head;
	right.head = nullptr;
}

//operator kopiuj¹cy
Moves & Moves::operator=(const Moves & right)
{
	MoveElement * pom = right.head;
	MoveElement * tempTail = nullptr;

	if (head != nullptr)
	{
		RemoveAllList();
	}
		
	if (right.head == nullptr)
	{
		head = nullptr;
	}
	else
	{
		head = new MoveElement({ right.head->pointFrom, right.head->pointTo, right.head->Color, right.head->positionInArrayOfDeathPawns, nullptr });
		tempTail = head;
		pom = pom->next;
		while (pom != nullptr)
		{
			tempTail->next = new MoveElement({ right.head->pointFrom, right.head->pointTo, right.head->Color, right.head->positionInArrayOfDeathPawns, nullptr });
			pom = pom->next;
			tempTail = tempTail->next;
		}
	}

	return *this;
}

//operator przenosz¹cy
Moves & Moves::operator=(Moves && right)
{
	if (head != nullptr)
	{
		RemoveAllList();
	}
	head = right.head;
	right.head = nullptr;
	return *this;
}

void Moves::AddToList(const MyPoint & tempPointFrom, const MyPoint & tempPointTo, const int & tempColor, int tempPositionDestroyedPawn)
{
	if (head == nullptr)
	{
		head = new MoveElement({ tempPointFrom, tempPointTo, tempColor, tempPositionDestroyedPawn, nullptr });
		return;
	}

	head = new MoveElement({ tempPointFrom, tempPointTo, tempColor, tempPositionDestroyedPawn, head });
}

void Moves::showAllMoves()
{
	MoveElement * pom = head;
	while (pom)
	{
		cout << "Color: " << pom->Color << endl;
		cout << "Move From: (" << pom->pointFrom.x << ", " << pom->pointFrom.y << ") -> Move To: (" << pom->pointTo.x << ", " << pom->pointTo.y << ")" << endl;
		cout << "pawn index :" << pom->positionInArrayOfDeathPawns << endl;
		pom = pom->next;
	}
}

void Moves::saveMovesToFile()
{
	ofstream file;
	file.open("plik_z_wynikami.txt");

	int i = 1;
	MoveElement * pom = head;
	while (pom)
	{
		if (pom->Color == white)
		{
			file << "Move[" << i << "], " << "Color: white" << endl;
		}
		else
		{
			file << "Move[" << i << "], " << "Color: black" << endl;
		}
		
		file << "Move From: (" << pom->pointFrom.x << ", " << pom->pointFrom.y << ") -> Move To: (" << pom->pointTo.x << ", " << pom->pointTo.y << ")" << endl;
		file << "pawn index :" << pom->positionInArrayOfDeathPawns << endl;
		pom = pom->next;
		i++;
	}
	file.close();
}

LastMove Moves::showLastMove()
{
	LastMove tempMove;

	if (head == nullptr)
	{
		tempMove.pointFrom = {-5,-5};
		tempMove.pointTo = {-5,-5};
		tempMove.Color = 0;
		tempMove.positionInArrayOfDeathPawns = -1;
	}
	else
	{
		tempMove.pointFrom = head->pointFrom;
		tempMove.pointTo = head->pointTo;
		tempMove.Color = head->Color;
		tempMove.positionInArrayOfDeathPawns = head->positionInArrayOfDeathPawns;
	}

	return tempMove;
}

LastMove Moves::showLastButNotLeastMove()
{
	LastMove tempMove;

	if (head == nullptr || head->next == nullptr)
	{
		tempMove.pointFrom = { -5,-5 };
		tempMove.pointTo = { -5,-5 };
		tempMove.Color = 0;
		tempMove.positionInArrayOfDeathPawns = -1;
	}
	else
	{
		tempMove.pointFrom = head->next->pointFrom;
		tempMove.pointTo = head->next->pointTo;
		tempMove.Color = head->next->Color;
		tempMove.positionInArrayOfDeathPawns = head->next->positionInArrayOfDeathPawns;
	}

	return tempMove;
}

// jesli znajdzie dany ruch to zwraca true
bool Moves::doResearchForCastling(MyPoint positionToSearch, int color)
{
	MoveElement *pom = head;
	if (head == nullptr)
	{
		return false;
	}
	// jezeli teraz jest ruch bia³ych to ostatni ruch naleza³ do czarnych
	if (color == white)
	{
		pom = pom->next;
		while (pom->next != nullptr)
		{
			if (pom->pointFrom.y == positionToSearch.y && pom->pointFrom.x == positionToSearch.x)
			{
				return true;
			}
			pom = pom->next->next;
		}
		return false;
	}

	// jezeli teraz jest ruch czarnych to ostatni ruch naleza³ do bia³ych
	if (color == black)
	{
		pom = pom->next;
		while (1)
		{
			if (pom == nullptr)
			{
				break;
			}
			if (pom->pointFrom.y == positionToSearch.y && pom->pointFrom.x == positionToSearch.x)
			{
				return true;
			}
			if (pom->next->next == nullptr)
			{
				break;
			}
			else
			{
				pom = pom->next->next;
			}
			
		}
		return false;
	}
	return false;
}

void Moves::deleteFirstPossibleMove()
{
	MoveElement *pom = head;
	head = head->next;

	delete pom;
}

void Moves::RemoveAllList()
{
	if (head == nullptr)
	{
		return;
	}

	MoveElement * pom;
	while (head)
	{
		pom = head;
		head = head->next;

		delete pom;
	}
}

Moves::~Moves()
{
	RemoveAllList();
}