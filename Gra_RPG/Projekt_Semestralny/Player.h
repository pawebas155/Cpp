#pragma once
#include <iostream>
#include "usefullStructures.h"
#include <string>
#include <chrono>
#include <SFML\Graphics.hpp>
#include "Opponent.h"

using namespace std;

class Opponent;

class Player
{
private:
	coord tempPosition;
	int totalExpToNextLvl;
	int actualExp;
	int lvl;

	string championName;
	double actualHeal;
	double totalHeal;

	int spriteNumberInSpritesArray;

	int timeBreakForMovingMillisecond;
	int doAnimation;							// przyjmuje wartosci 1, 2, 3, ... UP, LEFT, DOWN, ...

	chrono::system_clock::time_point ButtonPauseClock1;

	bool canMove;
	
	int armor;
	int attackDamage;

public:
	Player();

	int getSpriteNumberInSpritesArray();
	void setSpriteNumberInSpritesArray(int num);

	coord getPosition();
	void setPosition(coord &tempPos);

	string getChampionName();
	void setChampionName(string name);

	// poruszanie sie
	int action();

	double getLifePercentage();

	// odejmuje iloœæ zycia podan¹ w argumencie
	void getInjures(int damage);

	int getAttackDamage();

	void setAttackDamage(int val);

	int getArmor();

	void setArmor(int val);

	bool detectOpponentNearPlayer(Opponent * opponent, int tempPlayerDirection);

	void changeActualHeal(double val);
};