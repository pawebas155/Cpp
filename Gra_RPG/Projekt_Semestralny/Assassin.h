#pragma once
#include "Opponent.h"
#include <SFML\Graphics.hpp>
#include "usefullStructures.h"
#include "string"
#include <chrono>
#include <random>
#include "Render.h"

using namespace std;

class Assassin : public Opponent
{
public:
	Assassin();

	int getSpriteNumberInSpritesArray();
	void setSpriteNumberInSpritesArray(int num);
	int action();

	void animationForOpponentMoving(int animation, sf::RenderWindow* tempWindow, Render* tempRender, Player *player);

	~Assassin();
};

