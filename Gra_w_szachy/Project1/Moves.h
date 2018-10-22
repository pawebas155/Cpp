#pragma once
#include <iostream>
#include <fstream>
#include "myUsefulStruct.h"

using namespace std;

class Moves
{
private:
	MoveElement *head;

public:
	Moves();

	void AddToList(const MyPoint & tempPointFrom, const MyPoint & tempPointTo, const int & tempColor, int tempPositionDestroyedPawn);

	//konstruktor kopiuj�cy
	Moves (const Moves & right);

	//konstruktor przenosz�cy
	Moves (Moves && right);

	//operator kopiuj�cy
	Moves & operator=(const Moves &right);

	//operator przenosz�cy
	Moves & operator=(Moves &&right);

	void showAllMoves();

	void saveMovesToFile();

	LastMove showLastMove();

	LastMove showLastButNotLeastMove();

	bool doResearchForCastling(MyPoint positionToSearch, int color);

	void deleteFirstPossibleMove();

	void RemoveAllList();

	~Moves();
};