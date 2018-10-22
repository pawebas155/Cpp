#include "Opponent.h"

Opponent::Opponent()
{
	timeBreakForMovingMillisecond = 1400;
	opponentAnimationStep = 0;
	stopOpponentAnimation = false;
	showOpponentAnimation = false;
	saveDoAnimationOpponent = 3;
	lastOpponentDirection = 3;
	canMove = true;
	doAnimation = 0;
	detectChampion = false;
	isDead = false;
	respawnTimeAfterDeathSecond = 10;
	positionCorrection = 8;
}

coord Opponent::getPosition()
{
	return coord(tempPosition);
}

void Opponent::setPosition(coord &tempPos)
{
	tempPosition = tempPos;
}

coord Opponent::getPositionAtStart()
{
	return coord(positionAtStart);
}

void Opponent::setPositionAtStart(coord & tempPos)
{
	positionAtStart = tempPos;
}

string Opponent::getName()
{
	return string(name);
}

void Opponent::setName(string & champName)
{
	name = champName;
}

bool Opponent::getStopOpponentAnimation()
{
	return stopOpponentAnimation;
}

void Opponent::setStopOpponentAnimation(bool val)
{
	stopOpponentAnimation = val;
}

bool Opponent::getShowOpponentAnimation()
{
	return showOpponentAnimation;
}

void Opponent::setShowOpponentAnimation(bool val)
{
	showOpponentAnimation = val;
}

double Opponent::getOpponentAnimationStep()
{
	return opponentAnimationStep;
}

void Opponent::setOpponentAnimationStep(double val)
{
	opponentAnimationStep = val;
}

int Opponent::getSaveDoAnimationOpponent()
{
	return saveDoAnimationOpponent;
}

void Opponent::setSaveDoAnimationOpponent(int & val)
{
	saveDoAnimationOpponent = val;
}

int Opponent::getLastOpponentDirection()
{
	return lastOpponentDirection;
}

void Opponent::setLastOpponentDirection(int & val)
{
	lastOpponentDirection = val;
}

chrono::system_clock::time_point Opponent::getAnimateClock()
{
	return chrono::system_clock::time_point(animateClock);
}

void Opponent::setAnimateClock(chrono::system_clock::time_point & val)
{
	animateClock = val;
}

void Opponent::detectChampionNearOpponent(Player * hero)
{
	chamionTempPosition = hero->getPosition();

	if (abs(chamionTempPosition.x - tempPosition.x) < 4 && abs(chamionTempPosition.y - tempPosition.y) < 4)
	{
		detectChampion = true;
		timeBreakForMovingMillisecond = 0;
	}
	else
	{
		detectChampion = false;
		timeBreakForMovingMillisecond = 1400;
	}
}

double Opponent::getLifePercentage()
{
	return (double)(actualHeal / totalHeal);
}

int Opponent::getAttackDamage()
{
	return attackDamage;
}

void Opponent::setAttackDamage(int val)
{
	attackDamage = val;
}

int Opponent::getArmor()
{
	return armor;
}

void Opponent::setArmor(int val)
{
	armor = val;
}

bool Opponent::getIsDead()
{
	return isDead;
}

void Opponent::setIsDead(bool val)
{
	isDead = val;
}

void Opponent::checkLifeLevel()
{
	if (actualHeal <= 0)
	{
		isDead = true;
	}
}

void Opponent::getInjures(int damage)
{
	if(damage - armor < 0, 95 * damage)
	{
		actualHeal -= 0.05 * damage;
	}
	else
	{
		actualHeal -= (damage - armor);
	}
}

int Opponent::getRespawnTimeAfterDeath()
{
	return respawnTimeAfterDeathSecond;
}

void Opponent::drawOpponentPercentageOfHeal(sf::RenderWindow * tempWindow, coord opponentPosition)
{
	coord rectangleSize = { 20, 5 };		// docelowo 20 x 5
	int board = 1;							// docelowo 1
	coord positionOnScreen = opponentPosition;
	positionOnScreen.x += 7;
	positionOnScreen.y -= 2;
	double lifePercentage = actualHeal / totalHeal;


	sf::RectangleShape HealFrame(sf::Vector2f(rectangleSize.x, rectangleSize.y));
	HealFrame.setFillColor(sf::Color::Transparent);
	HealFrame.setOutlineThickness(board);
	HealFrame.setOutlineColor(sf::Color::Black);
	HealFrame.setPosition(sf::Vector2f(positionOnScreen.x, positionOnScreen.y));

	sf::RectangleShape healLevel(sf::Vector2f(rectangleSize.x * lifePercentage, rectangleSize.y));
	healLevel.setFillColor(sf::Color::Red);
	healLevel.setPosition(sf::Vector2f(positionOnScreen.x, positionOnScreen.y));

	tempWindow->draw(HealFrame);
	tempWindow->draw(healLevel);
}

Opponent::~Opponent()
{
}


