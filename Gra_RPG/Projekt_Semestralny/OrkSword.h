#pragma once
#include "Opponent.h"
#include <chrono>
#include <random>
#include "Render.h"
#include <SFML\Graphics.hpp>
using namespace std;

class OrkSword : public Opponent
{
public:
	OrkSword();

	int getSpriteNumberInSpritesArray();
	void setSpriteNumberInSpritesArray(int num);

	int action();

	void animationForOpponentMoving(int animation, sf::RenderWindow *tempWindow, Render* tempRender, Player *player);

	~OrkSword();
};

