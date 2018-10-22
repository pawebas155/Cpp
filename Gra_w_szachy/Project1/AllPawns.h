#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "myUsefulStruct.h"
#include <list>
#include "Moves.h"
using namespace std;

class MyAllPawns
{
protected:
	string name;
	MyPoint position;
	PawnsGraphic graphic;
	int Pcolor;

public:
	MyAllPawns(string Name, MyPoint point, int color, int pos);

	// pobranie tekst�r pionk�w szachowych i stworzenie sprite'a oraz nadanie pionkom imion
	// rzad(row) w zdj�ciu 0 = czarne, 1 = bia�e

	sf::Sprite* getSprite();

	virtual void CheckPossibleMoves(MyPoint point, vector<vector<MyAllPawns*>> MainBoard, Moves *move, list<MyPoint> *listOfPossibleMoves) = 0;

	virtual bool isCheck(vector<vector<MyAllPawns*>> MainBoard, MyPoint KingPosition, MyPoint reallyKingPosition) = 0;

	int showColor();

	string getName();

	MyPoint getPosition();

	virtual ~MyAllPawns();
};