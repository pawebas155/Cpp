#pragma once
#include <string>
#include <chrono>
#include "usefullStructures.h"
#include "Player.h"
#include <SFML\Graphics.hpp>
#include "Render.h"

using namespace std;

class Player;

class Opponent
{
protected:
	string name;

	int timeBreakForMovingMillisecond;
	int spriteNumberInSpritesArray;
	chrono::system_clock::time_point ButtonPauseClock1;
	chrono::system_clock::time_point animateClock;
	
	double actualHeal;
	double totalHeal;

	bool isDead;
	int respawnTimeAfterDeathSecond;

	int armor;
	int attackDamage;

	coord positionAtStart;

	coord tempPosition;
	bool canMove;

	bool detectChampion;
	coord chamionTempPosition;

	int doAnimation;										// przyjmuje wartosci 1, 2, 3, ... UP, LEFT, DOWN, ...

	bool stopOpponentAnimation;
	bool showOpponentAnimation;
	double opponentAnimationStep;
	int saveDoAnimationOpponent;
	int lastOpponentDirection;

	int positionCorrection;

public:
	Opponent();

	virtual int getSpriteNumberInSpritesArray() = 0;
	virtual void setSpriteNumberInSpritesArray(int num) = 0;

	coord getPosition();
	void setPosition(coord &tempPos);

	coord getPositionAtStart();
	void setPositionAtStart(coord &tempPos);

	string getName();
	void setName(string & champName);

	bool getStopOpponentAnimation();
	void setStopOpponentAnimation(bool val);

	bool getShowOpponentAnimation();
	void setShowOpponentAnimation(bool val);

	double getOpponentAnimationStep();
	void setOpponentAnimationStep(double val);

	int getSaveDoAnimationOpponent();
	void setSaveDoAnimationOpponent(int & val);

	int getLastOpponentDirection();
	void setLastOpponentDirection(int & val);

	chrono::system_clock::time_point getAnimateClock();
	void setAnimateClock(chrono::system_clock::time_point &val);

	virtual int action() = 0;

	int getAttackDamage();
	void setAttackDamage(int val);

	int getArmor();
	void setArmor(int val);

	bool getIsDead();
	void setIsDead(bool val);

	void checkLifeLevel();

	void detectChampionNearOpponent(Player * hero);

	double getLifePercentage();

	void getInjures(int damage);

	int getRespawnTimeAfterDeath();

	virtual void animationForOpponentMoving(int animation, sf::RenderWindow *tempWindow, Render *tempRender, Player * player) = 0;

	void drawOpponentPercentageOfHeal(sf::RenderWindow *tempWindow, coord opponentPosition);

	virtual ~Opponent();
};