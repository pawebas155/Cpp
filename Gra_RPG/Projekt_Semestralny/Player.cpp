#include "Player.h"

Player::Player()
{
	spriteNumberInSpritesArray = 1;
	timeBreakForMovingMillisecond = 50;
	doAnimation = 0;
	canMove = true;
	totalHeal = 200;
	actualHeal = totalHeal;
	armor = 20;
	attackDamage = 500;
}

int Player::getSpriteNumberInSpritesArray()
{
	return spriteNumberInSpritesArray;
}

void Player::setSpriteNumberInSpritesArray(int num)
{
	spriteNumberInSpritesArray = num;
}

coord Player::getPosition()
{
	return coord(tempPosition);
}

void Player::setPosition(coord &tempPos)
{
	tempPosition = tempPos;
}

string Player::getChampionName()
{
	return string(championName);
}

void Player::setChampionName(string name)
{
	championName = name;
}

int Player::action()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (canMove == false)
		{
			chrono::duration<double, std::milli> timeBetween = chrono::system_clock::now() - ButtonPauseClock1;

			if (timeBetween > chrono::milliseconds(timeBreakForMovingMillisecond))
			{
				canMove = true;
				return NOTHING;
			}
			else
			{
				return NOTHING;
			}
		}
		ButtonPauseClock1 = (chrono::system_clock::now());

		canMove = false;

		doAnimation = UP;
		
		return doAnimation;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (canMove == false)
		{
			chrono::duration<double, std::milli> timeBetween = chrono::system_clock::now() - ButtonPauseClock1;

			if (timeBetween > chrono::milliseconds(timeBreakForMovingMillisecond))
			{
				canMove = true;
				return NOTHING;
			}
			else
			{
				return NOTHING;
			}
		}
		ButtonPauseClock1 = (chrono::system_clock::now());

		canMove = false;

		doAnimation = DOWN;
		return doAnimation;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (canMove == false)
		{
			chrono::duration<double, std::milli> timeBetween = chrono::system_clock::now() - ButtonPauseClock1;

			if (timeBetween > chrono::milliseconds(timeBreakForMovingMillisecond))
			{
				canMove = true;
				return NOTHING;
			}
			else
			{
				return NOTHING;
			}
		}
		ButtonPauseClock1 = (chrono::system_clock::now());

		canMove = false;

		doAnimation = LEFT;
		return doAnimation;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (canMove == false)
		{
			chrono::duration<double, std::milli> timeBetween = chrono::system_clock::now() - ButtonPauseClock1;

			if (timeBetween > chrono::milliseconds(timeBreakForMovingMillisecond))
			{
				canMove = true;
				return NOTHING;
			}
			else
			{
				return NOTHING;
			}
		}
		ButtonPauseClock1 = (chrono::system_clock::now());

		canMove = false;

		doAnimation = RIGHT;
		return doAnimation;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (canMove == false)
		{
			chrono::duration<double, std::milli> timeBetween = chrono::system_clock::now() - ButtonPauseClock1;

			if (timeBetween > chrono::milliseconds(timeBreakForMovingMillisecond))
			{
				canMove = true;
				return NOTHING;
			}
			else
			{
				return NOTHING;
			}
		}
		ButtonPauseClock1 = (chrono::system_clock::now());

		canMove = false;

		doAnimation = FIGHT;
		return doAnimation;
	}
	
	return NOTHING;
}

double Player::getLifePercentage()
{
	return (double)(actualHeal/totalHeal);
}

void Player::getInjures(int damage)
{
	if (damage - armor < 0,95 * damage)
	{
		actualHeal -= 0.05 * damage;
	}
	else
	{
		actualHeal -= (damage - armor);
	}
}

int Player::getAttackDamage()
{
	return attackDamage;
}

void Player::setAttackDamage(int val)
{
	attackDamage = val;
}

int Player::getArmor()
{
	return armor;
}

void Player::setArmor(int val)
{
	armor = val;
}

bool Player::detectOpponentNearPlayer(Opponent * opponent, int tempPlayerDirection)
{
	coord opponentPosition = opponent->getPosition();
	bool isDetect = false;

	if (tempPlayerDirection == UP && tempPosition.y - opponentPosition.y < 2 && tempPosition.y - opponentPosition.y >= 0 && abs(opponentPosition.x - tempPosition.x) < 1)
	{
		isDetect = true;
	}
	else if (tempPlayerDirection == DOWN && opponentPosition.y - tempPosition.y < 2 && opponentPosition.y - tempPosition.y >= 0 && abs(opponentPosition.x - tempPosition.x) < 1)
	{
		isDetect = true;
	}
	else if (tempPlayerDirection == LEFT && tempPosition.x - opponentPosition.x < 2 && tempPosition.x - opponentPosition.x >= 0 && abs(opponentPosition.y - tempPosition.y) < 1)
	{
		isDetect = true;
	}
	else if (tempPlayerDirection == RIGHT && opponentPosition.x - tempPosition.x < 2 && opponentPosition.x - tempPosition.x >= 0 && abs(opponentPosition.y - tempPosition.y) < 1)
	{
		isDetect = true;
	}

	return isDetect;
}

void Player::changeActualHeal(double val)
{
	if (val + actualHeal > totalHeal)
	{
		actualHeal = totalHeal;
	}
	else
	{
		actualHeal += val;
	}
}
