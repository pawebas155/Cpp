#pragma once

#define black 0
#define white 1

#include <string>
#include <SFML/Graphics.hpp>

struct PawnsGraphic
{
	sf::Texture texture;
	sf::Sprite sprite;
};

struct ChessPawns
{
	std::string name;
	sf::Sprite sprite;
};

struct MyPoint
{
	int x;
	int y;
};

struct Movements
{
	std::string name;
	MyPoint oldPosition;
	MyPoint newPosition;
};

struct movePoints
{
	MyPoint pointFrom;
	MyPoint pointTo;
};

struct Element
{
	movePoints points;
	Element * next;
};

struct MoveElement
{
	MyPoint pointFrom;
	MyPoint pointTo;
	int Color;
	int positionInArrayOfDeathPawns;
	MoveElement * next;
};

struct LastMove
{
	MyPoint pointFrom;
	MyPoint pointTo;
	int Color;
	int positionInArrayOfDeathPawns;
};