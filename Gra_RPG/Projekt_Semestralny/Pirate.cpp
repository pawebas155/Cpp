#include "Pirate.h"

Pirate::Pirate() : Opponent()
{
	totalHeal = 100;
	actualHeal = totalHeal;
	armor = 10;
	attackDamage = 16;
}

int Pirate::getSpriteNumberInSpritesArray()
{
	return spriteNumberInSpritesArray;
}

void Pirate::setSpriteNumberInSpritesArray(int num)
{
	spriteNumberInSpritesArray = num;
}

int Pirate::action()
{
	doAnimation = NOTHING;

	// jesli true to goni postac i atakuje
	if (detectChampion == true)
	{
		if (abs(chamionTempPosition.x - tempPosition.x) < 2 && abs(chamionTempPosition.y - tempPosition.y) < 2)
		{
			// jesli zgadza sie kierunek i ten warunek (pozycja) to atakuje
			if (lastOpponentDirection == UP && (chamionTempPosition.y == tempPosition.y - 1 || chamionTempPosition.y == tempPosition.y) && abs(chamionTempPosition.x - tempPosition.x) < 1)
			{
				doAnimation = FIGHT;
				return doAnimation;
			}
			else if (lastOpponentDirection == DOWN && (chamionTempPosition.y == tempPosition.y + 1 || chamionTempPosition.y == tempPosition.y) && abs(chamionTempPosition.x - tempPosition.x) < 1)
			{
				doAnimation = FIGHT;
				return doAnimation;
			}
			else if (lastOpponentDirection == LEFT && (chamionTempPosition.x == tempPosition.x - 1 || chamionTempPosition.x == tempPosition.x) && abs(chamionTempPosition.y - tempPosition.y) < 1)
			{
				doAnimation = FIGHT;
				return doAnimation;
			}
			else if (lastOpponentDirection == RIGHT && (chamionTempPosition.x == tempPosition.x + 1 || chamionTempPosition.x == tempPosition.x) && abs(chamionTempPosition.y - tempPosition.y) < 1)
			{
				doAnimation = FIGHT;
				return doAnimation;
			}

			// jesli nie zgadza sie kierunek to wchodzi na postac
			if (chamionTempPosition.y == tempPosition.y - 1)
			{
				doAnimation = UP;
				return doAnimation;
			}
			else if (chamionTempPosition.y == tempPosition.y + 1)
			{
				doAnimation = DOWN;
				return doAnimation;
			}
			else if (chamionTempPosition.x == tempPosition.x - 1)
			{
				doAnimation = LEFT;
				return doAnimation;
			}
			else if (chamionTempPosition.x == tempPosition.x + 1)
			{
				doAnimation = RIGHT;
				return doAnimation;
			}
		}
		else
		{
			// goni postac				
			if (chamionTempPosition.y < tempPosition.y)
			{
				doAnimation = UP;
				return doAnimation;
			}
			else if (chamionTempPosition.y > tempPosition.y)
			{
				doAnimation = DOWN;
				return doAnimation;
			}
			else if (chamionTempPosition.x < tempPosition.x)
			{
				doAnimation = LEFT;
				return doAnimation;
			}
			else if (chamionTempPosition.x > tempPosition.x)
			{
				doAnimation = RIGHT;
				return doAnimation;
			}
		}
	}
	else if (abs(positionAtStart.x - tempPosition.x) > 3 || abs(positionAtStart.y - tempPosition.y) > 3)
	{
		//jesli jest w swoim kwadracie to nic jesli nie to wraca
		if (positionAtStart.y - 3 > tempPosition.y)
		{
			doAnimation = DOWN;
			return doAnimation;
		}
		if (positionAtStart.y + 3 < tempPosition.y)
		{
			doAnimation = UP;
			return doAnimation;
		}
		if (positionAtStart.x - 3 > tempPosition.x)
		{
			doAnimation = RIGHT;
			return doAnimation;
		}
		if (positionAtStart.x + 3 < tempPosition.x)
		{
			doAnimation = LEFT;
			return doAnimation;
		}
	}


	if (canMove == false)
	{
		chrono::duration<double, std::milli> timeBetween = chrono::system_clock::now() - ButtonPauseClock1;

		if (timeBetween > chrono::milliseconds(timeBreakForMovingMillisecond))
		{
			canMove = true;
			doAnimation = NOTHING;
			return doAnimation;
		}
		else
		{
			doAnimation = NOTHING;
			return doAnimation;
		}
	}
	ButtonPauseClock1 = chrono::system_clock::now();
	canMove = false;

	// obtain a seed from the system clock:
	unsigned seed = static_cast<int> (std::chrono::system_clock::now().time_since_epoch().count());
	// seeds the random number engine, the mersenne_twister_engine
	std::mt19937 generator(seed);
	// set a distribution range (1 - 4)
	std::uniform_int_distribution<int> distribution(0, 4);
	// losowanie randomowego kierunku, w ktor¹ strone ma chodziæ
	doAnimation = distribution(generator);

	// stworzenie pola, po ktorym moze sie ta postaæ poruszaæ kwadrat 5x5
	if (doAnimation == UP)
	{
		if (tempPosition.y <= positionAtStart.y - 2)
		{
			doAnimation = NOTHING;
		}
	}
	else if (doAnimation == DOWN)
	{
		if (tempPosition.y >= positionAtStart.y + 2)
		{
			doAnimation = NOTHING;
		}
	}
	else if (doAnimation == LEFT)
	{
		if (tempPosition.x <= positionAtStart.x - 2)
		{
			doAnimation = NOTHING;
		}
	}
	else if (doAnimation == RIGHT)
	{
		if (tempPosition.x >= positionAtStart.x + 2)
		{
			doAnimation = NOTHING;
		}
	}

	return doAnimation;
}

void Pirate::animationForOpponentMoving(int animation, sf::RenderWindow * tempWindow, Render * tempRender, Player *player)
{
	if (animation == FIGHT)
	{
		sf::Sprite tempGraphics;

		tempGraphics = tempRender->getSpriteChampiontWithNumber(spriteNumberInSpritesArray);

		bool isLastFrame = false;

		if (stopOpponentAnimation == false)
		{

			animateClock = chrono::system_clock::now();
			stopOpponentAnimation = true;

		}

		if (opponentAnimationStep > 5)
		{
			opponentAnimationStep = 0;
			isLastFrame = true;
		}
		tempGraphics.setTextureRect(sf::IntRect(34 * opponentAnimationStep, 34 * (4 + 4 + 4 + lastOpponentDirection - 1), 34, 34));

		coord tempOpponentPos = tempPosition;

		tempGraphics.setPosition((tempOpponentPos.x * 20 - positionCorrection), (tempOpponentPos.y * 20) - (positionCorrection + 4));		// -13 korekta polozenie gracza
		tempWindow->draw(tempGraphics);

		drawOpponentPercentageOfHeal(tempWindow, { (tempOpponentPos.x * 20 - positionCorrection), (tempOpponentPos.y * 20) - (positionCorrection + 4) });

		if (isLastFrame == true)
		{
			opponentAnimationStep = 0;
			showOpponentAnimation = (false);
			stopOpponentAnimation = (false);

			player->getInjures(attackDamage);


			return;
		}

		chrono::duration<double, milli> d1 = chrono::system_clock::now() - animateClock;
		if (d1 > chrono::milliseconds(25))
		{
			opponentAnimationStep++;
			stopOpponentAnimation = (false);
		}
	}
	else
	{
		sf::Sprite tempGraphics;
		tempGraphics = tempRender->getSpriteChampiontWithNumber(spriteNumberInSpritesArray);

		bool isLastFrame = false;

		if (stopOpponentAnimation == false)
		{
			animateClock = (chrono::system_clock::now());
			stopOpponentAnimation = (true);
		}

		if (opponentAnimationStep > 8)
		{
			opponentAnimationStep = (1);
			if (animation == LEFT || animation == RIGHT)
			{
				opponentAnimationStep = (0);
			}
			isLastFrame = true;
		}

		// wyzukanie set texture rect
		tempGraphics.setTextureRect(sf::IntRect(34 * opponentAnimationStep, 34 * (4 + 4 + animation - 1), 34, 34));


		if (isLastFrame == true)
		{
			opponentAnimationStep = (9);
		}

		double step = 20 / 9;


		coord tempOpponentPos = tempPosition;

		if (animation == UP)
		{
			tempGraphics.setPosition((tempOpponentPos.x * 20 - positionCorrection), (tempOpponentPos.y * 20) - opponentAnimationStep * step - (positionCorrection + 4));		// -13 korekta polozenie gracza
			tempWindow->draw(tempGraphics);

			drawOpponentPercentageOfHeal(tempWindow, { (tempOpponentPos.x * 20 - positionCorrection), (int)((tempOpponentPos.y * 20) - opponentAnimationStep * step - (positionCorrection + 4)) });
		}
		else if (animation == DOWN)
		{
			tempGraphics.setPosition((tempOpponentPos.x * 20 - positionCorrection), (tempOpponentPos.y * 20) + opponentAnimationStep * step - (positionCorrection + 4));
			tempWindow->draw(tempGraphics);

			drawOpponentPercentageOfHeal(tempWindow, { (tempOpponentPos.x * 20 - positionCorrection), (int)((tempOpponentPos.y * 20) + opponentAnimationStep * step - (positionCorrection + 4)) });
		}
		else if (animation == LEFT)
		{
			tempGraphics.setPosition((tempOpponentPos.x * 20 - positionCorrection) - opponentAnimationStep * step, (tempOpponentPos.y * 20) - (positionCorrection + 4));
			tempWindow->draw(tempGraphics);

			drawOpponentPercentageOfHeal(tempWindow, { (int)((tempOpponentPos.x * 20 - positionCorrection) - opponentAnimationStep * step), ((tempOpponentPos.y * 20) - (positionCorrection + 4)) });
		}
		else if (animation == RIGHT)
		{
			tempGraphics.setPosition((tempOpponentPos.x * 20 - positionCorrection) + opponentAnimationStep * step, (tempOpponentPos.y * 20) - (positionCorrection + 4));
			tempWindow->draw(tempGraphics);

			drawOpponentPercentageOfHeal(tempWindow, { (int)((tempOpponentPos.x * 20 - positionCorrection) + opponentAnimationStep * step), ((tempOpponentPos.y * 20) - (positionCorrection + 4)) });
		}


		if (isLastFrame == true)
		{
			opponentAnimationStep = (1);

			if (animation == UP)
			{
				tempOpponentPos.y--;
			}
			if (animation == DOWN)
			{
				tempOpponentPos.y++;
			}
			if (animation == LEFT)
			{
				tempOpponentPos.x--;
			}
			if (animation == RIGHT)
			{
				tempOpponentPos.x++;
			}
			tempPosition = (tempOpponentPos);
			showOpponentAnimation = (false);
			stopOpponentAnimation = (false);
			return;
		}


		// jesli wykona wszystkie kroki to wtedy ustawia showAnimation = false;
		chrono::duration<double, milli> deltaTime = chrono::system_clock::now() - animateClock;
		if (deltaTime > chrono::milliseconds(50))
		{
			opponentAnimationStep++;
			stopOpponentAnimation = (false);
		}
	}
}

Pirate::~Pirate()
{
}
