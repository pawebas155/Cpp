#include "GameWindow.h"

GameWindow::GameWindow()
{
	isError = false;
	int menuChoice = menu.gameMenu();

	if (menuChoice == NEWGAME)
	{
		mapReader.readGameState(menu.getFileName());
	}
	else if (menuChoice == LOADGAME)
	{
		mapReader.readGameState(menu.getFileName());
	}
	else if (menuChoice == ERRORHEPPENED)
	{
		isError = true;
		return;
	}
	hero.setChampionName(menu.getPlayerNick());

	mapReader.readMapFromFile(mapLayer1, mapLayer2, mapLayer3, vectorOfNextMaps);
	
	render.readTextureMapElements();
	render.readSpriteMapElements();

	render.readTextureChampion();
	render.readSpriteChampion();
	

	hero.setPosition(mapReader.getPlayerPositionAtStart());
	positionCorrection = 8;
	
	stopAnimation = false;
	animationStep = 0;
	showAnimation = false;
	saveDoAnimation = 3;
	lastChampionDirection = 3;

	createOpponents();

	textureBarOnTheRight.loadFromFile("graphics/graphic.png");
	spriteBarOnTheRight.setTexture(textureBarOnTheRight);
}

void GameWindow::drawTheMap()
{
	sf::Sprite tempGraphics;

	coord mapSize = mapReader.getMapSize();

	for (int i = 0; i < mapSize.y; i++)
	{
		for (int j = 0; j < mapSize.x; j++)
		{
			if (mapLayer1[i][j] != 0)
			{
				tempGraphics = render.getSpriteMapElementWithNumber(mapLayer1[i][j] - 1);
				tempGraphics.setPosition(j * 60, i * 60);
				window.draw(tempGraphics);
			}
			if (mapLayer2[i][j] != 0)
			{
				tempGraphics = render.getSpriteMapElementWithNumber(mapLayer2[i][j] - 1);
				tempGraphics.setPosition(j * 60, i * 60);
				window.draw(tempGraphics);
			}
		}
	}
}

void GameWindow::createOpponents()
{
	vector<opponentPositionAndOutfit> tempOpponents = mapReader.getOpponentPositionAndOutfitNumber();
	vectorOfOpponents.resize(tempOpponents.size());

	for (int i = 0; i < tempOpponents.size(); i++)
	{
		//assassin, hero, orkSpear, orkSpearShield, orkSword, pirate, skeleton
		if (tempOpponents[i].outfitID == assasin)
		{
			vectorOfOpponents[i] = new Assassin();
		}
		else if ((tempOpponents[i].outfitID == orkSpear))
		{
			vectorOfOpponents[i] = new OrkSpear();
		}
		else if ((tempOpponents[i].outfitID == orkSpearShield))
		{
			vectorOfOpponents[i] = (new OrkSpearShield());
		}
		else if ((tempOpponents[i].outfitID == orkSword))
		{
			vectorOfOpponents[i] = (new OrkSword());
		}
		else if ((tempOpponents[i].outfitID == pirate))
		{
			vectorOfOpponents[i] = (new Pirate());
		}
		else if ((tempOpponents[i].outfitID == skeleton))
		{
			vectorOfOpponents[i] = (new Skeleton());
		}
		vectorOfOpponents[i]->setPosition(tempOpponents[i].opponentPosition);
		vectorOfOpponents[i]->setPositionAtStart(tempOpponents[i].opponentPosition);

		vectorOfOpponents[i]->setName(tempOpponents[i].outfitName);
		vectorOfOpponents[i]->setSpriteNumberInSpritesArray(tempOpponents[i].outfitID);
	}
}

void GameWindow::animationForPlayerMoving(int animation)
{
	if (animation == FIGHT)
	{
		sf::Sprite tempGraphics;
		tempGraphics = render.getSpriteChampiontWithNumber(hero.getSpriteNumberInSpritesArray());

		bool isLastFrame = false;

		if (stopAnimation == false)
		{
			animateClock1 = chrono::system_clock::now();
			stopAnimation = true;
		}

		if (animationStep > 5)
		{
			animationStep = 0;
			isLastFrame = true;
		}
		tempGraphics.setTextureRect(sf::IntRect(34 * animationStep, 34 * (4 + 4 + 4 + lastChampionDirection - 1), 34, 34));

		coord tempHeroPos = hero.getPosition();
		
		tempGraphics.setPosition((tempHeroPos.x * 20 - positionCorrection), (tempHeroPos.y * 20)- (positionCorrection + 4));		// -13 korekta polozenie gracza
		window.draw(tempGraphics);
		drawChampionOrOpponentPercentageOfHeal({ (tempHeroPos.x * 20 - positionCorrection), (tempHeroPos.y * 20) - (positionCorrection + 4) }, hero.getLifePercentage());
		
		if (isLastFrame == true)
		{
			animationStep = 0;
			showAnimation = false;
			stopAnimation = false;

			for (int i = 0; i < vectorOfOpponents.size(); i++)
			{
				if (hero.detectOpponentNearPlayer(vectorOfOpponents[i], lastChampionDirection))
				{
					vectorOfOpponents[i]->getInjures(hero.getAttackDamage());
				}
			}

			return;
		}

		chrono::duration<double, milli> d1 = chrono::system_clock::now() - animateClock1;
		if (d1 > chrono::milliseconds(25))
		{
			animationStep++;
			stopAnimation = false;
		}
	}
	else
	{
		sf::Sprite tempGraphics;
		tempGraphics = render.getSpriteChampiontWithNumber(hero.getSpriteNumberInSpritesArray());

		bool isLastFrame = false;

		if (stopAnimation == false)
		{
			animateClock1 = chrono::system_clock::now();
			stopAnimation = true;
		}

		if (animationStep > 8)
		{
			animationStep = 1;
			if (animation == LEFT || animation == RIGHT)
			{
				animationStep = 0;
			}
			isLastFrame = true;
		}

		// wyzukanie set texture rect
		tempGraphics.setTextureRect(sf::IntRect(34 * animationStep, 34 * (4 + 4 + animation - 1), 34, 34));


		if (isLastFrame == true)
		{
			animationStep = 9;
		}

		double step = 20 / 9;

		
		coord tempHeroPos = hero.getPosition();

		if (animation == UP) 
		{
			tempGraphics.setPosition((tempHeroPos.x * 20 - positionCorrection), (tempHeroPos.y * 20) - animationStep * step - (positionCorrection + 4));		// -13 korekta polozenie gracza
			window.draw(tempGraphics);
			drawChampionOrOpponentPercentageOfHeal({ (tempHeroPos.x * 20 - positionCorrection), (int)((tempHeroPos.y * 20) - animationStep * step - (positionCorrection + 4)) }, hero.getLifePercentage());
		}
		else if (animation == DOWN)
		{
			tempGraphics.setPosition((tempHeroPos.x * 20 - positionCorrection), (tempHeroPos.y * 20) + animationStep * step - (positionCorrection + 4));
			window.draw(tempGraphics);
			drawChampionOrOpponentPercentageOfHeal({ (tempHeroPos.x * 20 - positionCorrection), (int)((tempHeroPos.y * 20) + animationStep * step - (positionCorrection + 4)) }, hero.getLifePercentage());
		}
		 else if (animation == LEFT)
		{
			tempGraphics.setPosition((tempHeroPos.x * 20 - positionCorrection) - animationStep * step, (tempHeroPos.y * 20) - (positionCorrection + 4));
			window.draw(tempGraphics);
			drawChampionOrOpponentPercentageOfHeal({ (int)((tempHeroPos.x * 20 - positionCorrection) - animationStep * step), ((tempHeroPos.y * 20) - (positionCorrection + 4)) }, hero.getLifePercentage());
		}
		else if (animation == RIGHT)
		{
			tempGraphics.setPosition((tempHeroPos.x * 20 - positionCorrection) + animationStep * step, (tempHeroPos.y * 20) - (positionCorrection + 4));
			window.draw(tempGraphics);
			drawChampionOrOpponentPercentageOfHeal({ (int)((tempHeroPos.x * 20 - positionCorrection) + animationStep * step), ((tempHeroPos.y * 20) - (positionCorrection + 4)) }, hero.getLifePercentage());
		}
		

		if (isLastFrame == true)
		{
			animationStep = 1;

			if (animation == UP)
			{
				tempHeroPos.y--;
			}
			if (animation == DOWN)
			{
				tempHeroPos.y++;
			}
			if (animation == LEFT)
			{
				tempHeroPos.x--;
			}
			if (animation == RIGHT)
			{
				tempHeroPos.x++;
			}
			hero.setPosition(tempHeroPos);
			showAnimation = false;
			stopAnimation = false;
			return;
		}


		// jesli wykona wszystkie kroki to wtedy ustawia showAnimation = false;
		chrono::duration<double, milli> d1 = chrono::system_clock::now() - animateClock1;
		if (d1 > chrono::milliseconds(25))
		{
			animationStep++;
			stopAnimation = false;
		}
	}
}

void GameWindow::drawPlayer(int doAnimation)
{
	if (hero.getLifePercentage() <= 0)
	{
		hero.changeActualHeal(2000);
	}

	if (showAnimation == true)
	{
		animationForPlayerMoving(saveDoAnimation);
		return;
	}

	if (doAnimation != NOTHING)
	{
		coord tempPos = hero.getPosition();
		int mapSizeY = mapLayer3.size();
		int mapSizeX = mapLayer3[0].size();

		coord whichSquare = { 0, 0 };

		if (doAnimation == UP)
		{
			if (tempPos.y == 0 || mapLayer3[tempPos.y - 1][tempPos.x] == 0)
			{
				doAnimation = NOTHING;
			}

			if (tempPos.y > 0 && mapLayer3[tempPos.y - 1][tempPos.x] == 2)
			{
				for (vector<nextMap>::iterator it = vectorOfNextMaps.begin(); it != vectorOfNextMaps.end(); it++)
				{
					for (vector<int>::iterator it2 = (*it).crossingFields.begin(); it2 != (*it).crossingFields.end(); it2++)
					{
						whichSquare = {0, 0};

						switch ((*it2))
						{
						case 1:
						{
							break;
						}
						case 2:
						{
							whichSquare.x += 1;
							break;
						}
						case 3:
						{
							whichSquare.x += 2;
							break;
						}
						case 4:
						{
							whichSquare.y += 1;
							break;
						}
						case 5:
						{
							whichSquare.x += 1;
							whichSquare.y += 1;
							break;
						}
						case 6:
						{
							whichSquare.x += 2;
							whichSquare.y += 1;
							break;
						}
						case 7:
						{
							whichSquare.y += 2;
							break;
						}
						case 8:
						{
							whichSquare.x += 1;
							whichSquare.y += 2;
							break;
						}
						case 9:
						{
							whichSquare.x += 2;
							whichSquare.y += 2;
							break;
						}
						default:
						{
							break;
						}
						}

						if ((*it).blockPosition.x * 3  + whichSquare.x == tempPos.x && (*it).blockPosition.y * 3 + whichSquare.y == tempPos.y - 1)
						{
							clearOldMap();
							loadNewMap(it->nextMapName);
							return;
						}
					}
				}
			}
		}
		if (doAnimation == DOWN)
		{
			if (tempPos.y == mapSizeY - 1 || mapLayer3[tempPos.y + 1][tempPos.x] == 0)
			{
				doAnimation = NOTHING;
			}
			if (tempPos.y < mapSizeY - 1 && mapLayer3[tempPos.y + 1][tempPos.x] == 2)
			{
				for (vector<nextMap>::iterator it = vectorOfNextMaps.begin(); it != vectorOfNextMaps.end(); it++)
				{
					for (vector<int>::iterator it2 = (*it).crossingFields.begin(); it2 != (*it).crossingFields.end(); it2++)
					{
						whichSquare = { 0, 0 };

						switch ((*it2))
						{
						case 1:
						{
							break;
						}
						case 2:
						{
							whichSquare.x += 1;
							break;
						}
						case 3:
						{
							whichSquare.x += 2;
							break;
						}
						case 4:
						{
							whichSquare.y += 1;
							break;
						}
						case 5:
						{
							whichSquare.x += 1;
							whichSquare.y += 1;
							break;
						}
						case 6:
						{
							whichSquare.x += 2;
							whichSquare.y += 1;
							break;
						}
						case 7:
						{
							whichSquare.y += 2;
							break;
						}
						case 8:
						{
							whichSquare.x += 1;
							whichSquare.y += 2;
							break;
						}
						case 9:
						{
							whichSquare.x += 2;
							whichSquare.y += 2;
							break;
						}
						default:
						{
							break;
						}
						}

						if ((*it).blockPosition.x * 3 + whichSquare.x == tempPos.x && (*it).blockPosition.y * 3 + whichSquare.y == tempPos.y + 1)
						{
							clearOldMap();
							loadNewMap(it->nextMapName);
							return;
						}
					}
				}
			}
		}
		if (doAnimation == LEFT)
		{
			if (tempPos.x == 0 || mapLayer3[tempPos.y][tempPos.x - 1] == 0)
			{
				doAnimation = NOTHING;
			}
			if (tempPos.x > 0 && mapLayer3[tempPos.y][tempPos.x - 1] == 2)
			{
				for (vector<nextMap>::iterator it = vectorOfNextMaps.begin(); it != vectorOfNextMaps.end(); it++)
				{
					for (vector<int>::iterator it2 = (*it).crossingFields.begin(); it2 != (*it).crossingFields.end(); it2++)
					{
						whichSquare = { 0, 0 };

						switch ((*it2))
						{
						case 1:
						{
							break;
						}
						case 2:
						{
							whichSquare.x += 1;
							break;
						}
						case 3:
						{
							whichSquare.x += 2;
							break;
						}
						case 4:
						{
							whichSquare.y += 1;
							break;
						}
						case 5:
						{
							whichSquare.x += 1;
							whichSquare.y += 1;
							break;
						}
						case 6:
						{
							whichSquare.x += 2;
							whichSquare.y += 1;
							break;
						}
						case 7:
						{
							whichSquare.y += 2;
							break;
						}
						case 8:
						{
							whichSquare.x += 1;
							whichSquare.y += 2;
							break;
						}
						case 9:
						{
							whichSquare.x += 2;
							whichSquare.y += 2;
							break;
						}
						default:
						{
							break;
						}
						}

						if ((*it).blockPosition.x * 3 + whichSquare.x == tempPos.x - 1 && (*it).blockPosition.y * 3 + whichSquare.y == tempPos.y)
						{
							clearOldMap();
							loadNewMap(it->nextMapName);
							return;
						}
					}
				}
			}
		}
		if (doAnimation == RIGHT)
		{
			if (tempPos.x == mapSizeX - 1 || mapLayer3[tempPos.y][tempPos.x + 1] == 0)
			{
				doAnimation = NOTHING;
			}
			if (tempPos.x < mapSizeX - 1 && mapLayer3[tempPos.y][tempPos.x + 1] == 2)
			{
				for (vector<nextMap>::iterator it = vectorOfNextMaps.begin(); it != vectorOfNextMaps.end(); it++)
				{
					for (vector<int>::iterator it2 = (*it).crossingFields.begin(); it2 != (*it).crossingFields.end(); it2++)
					{
						whichSquare = { 0, 0 };

						switch ((*it2))
						{
						case 1:
						{
							break;
						}
						case 2:
						{
							whichSquare.x += 1;
							break;
						}
						case 3:
						{
							whichSquare.x += 2;
							break;
						}
						case 4:
						{
							whichSquare.y += 1;
							break;
						}
						case 5:
						{
							whichSquare.x += 1;
							whichSquare.y += 1;
							break;
						}
						case 6:
						{
							whichSquare.x += 2;
							whichSquare.y += 1;
							break;
						}
						case 7:
						{
							whichSquare.y += 2;
							break;
						}
						case 8:
						{
							whichSquare.x += 1;
							whichSquare.y += 2;
							break;
						}
						case 9:
						{
							whichSquare.x += 2;
							whichSquare.y += 2;
							break;
						}
						default:
						{
							break;
						}
						}

						if ((*it).blockPosition.x * 3 + whichSquare.x == tempPos.x + 1 && (*it).blockPosition.y * 3 + whichSquare.y == tempPos.y)
						{
							clearOldMap();
							loadNewMap(it->nextMapName);
							return;
						}
					}
				}
			}
		}
	}

	if (doAnimation != NOTHING)
	{
		if (doAnimation != FIGHT)
		{
			lastChampionDirection = doAnimation;
		}
		
		saveDoAnimation = doAnimation;
		showAnimation = true;
		animationForPlayerMoving(saveDoAnimation);
	}
	else
	{
		if (stopAnimation == false)
		{
			animateClock1 = chrono::system_clock::now();
			stopAnimation = true;
		}
		chrono::duration<double, milli> d1 = chrono::system_clock::now() - animateClock1;
		if (d1 > chrono::milliseconds(50))
		{
			animationStep = 0;
			stopAnimation = false;
		}

		sf::Sprite tempGraphics;
		tempGraphics = render.getSpriteChampiontWithNumber(hero.getSpriteNumberInSpritesArray());
		tempGraphics.setTextureRect(sf::IntRect(animationStep * 34, 34 * (4 + 4 + lastChampionDirection - 1), 34, 34));
		tempGraphics.setPosition(20 * hero.getPosition().x - positionCorrection, 20 * hero.getPosition().y - (positionCorrection + 4) );
		window.draw(tempGraphics);
		drawChampionOrOpponentPercentageOfHeal({ 20 * hero.getPosition().x - positionCorrection, 20 * hero.getPosition().y - (positionCorrection + 4 )}, hero.getLifePercentage());
	}
}

void GameWindow::drawOpponent(Opponent * tempOpponent, int doAnimation)
{
	// jeœli zaczyna wyswietlac animacje lub jest w trakcie jej wyswietlania
	if (tempOpponent->getShowOpponentAnimation() == true)
	{
		tempOpponent->animationForOpponentMoving(tempOpponent->getSaveDoAnimationOpponent(), &window, &render, &hero);
		return;
	}

	// sprawdza czy pole na ktore chce wejsc ma mozliwosc wejscia na nie - mapLayer3[][] == 0
	if (doAnimation != NOTHING)
	{
		coord tempPos = tempOpponent->getPosition();
		int mapSizeY = mapLayer3.size();
		int mapSizeX = mapLayer3[0].size();

		if (doAnimation == UP)
		{
			if (tempPos.y == 0 || mapLayer3[tempPos.y - 1][tempPos.x] == 0)
			{
				doAnimation = NOTHING;
			}
		}
		else if (doAnimation == DOWN)
		{
			if (tempPos.y == mapSizeY - 1 || mapLayer3[tempPos.y + 1][tempPos.x] == 0)
			{
				doAnimation = NOTHING;
			}
		}
		else if (doAnimation == LEFT)
		{
			if (tempPos.x == 0 || mapLayer3[tempPos.y][tempPos.x - 1] == 0)
			{
				doAnimation = NOTHING;
			}
		}
		else if (doAnimation == RIGHT)
		{
			if (tempPos.x == mapSizeX - 1 || mapLayer3[tempPos.y][tempPos.x + 1] == 0)
			{
				doAnimation = NOTHING;
			}
		}
	}

	if (doAnimation != NOTHING)
	{
		// jeœli nie jest FIGHT to zapisuje kierunek gracza
		// jak nastepny ruch bedzie FIGHT to bedize wiedzial w ktorym kierunku wyswietlac animacje walki
		if (doAnimation != FIGHT)
		{
			tempOpponent->setLastOpponentDirection(doAnimation);
		}

		tempOpponent->setSaveDoAnimationOpponent(doAnimation);
		tempOpponent->setShowOpponentAnimation(true);

		tempOpponent->animationForOpponentMoving(tempOpponent->getSaveDoAnimationOpponent(), &window, &render, &hero);
	}
	else
	{
		if (tempOpponent->getStopOpponentAnimation() == false)
		{
			tempOpponent->setAnimateClock(chrono::system_clock::now());
			tempOpponent->setStopOpponentAnimation(true);
		}
		chrono::duration<double, milli> d1 = chrono::system_clock::now() - tempOpponent->getAnimateClock();
		if (d1 > chrono::milliseconds(50))
		{
			tempOpponent->setOpponentAnimationStep(0);
			tempOpponent->setStopOpponentAnimation(false);
		}

		sf::Sprite tempGraphics;
		tempGraphics = render.getSpriteChampiontWithNumber(tempOpponent->getSpriteNumberInSpritesArray());

		tempGraphics.setTextureRect(sf::IntRect(tempOpponent->getOpponentAnimationStep() * 34, 34 * (4 + 4 + tempOpponent->getLastOpponentDirection() - 1), 34, 34));
		tempGraphics.setPosition(20 * tempOpponent->getPosition().x - positionCorrection, 20 * tempOpponent->getPosition().y - (positionCorrection + 4));
		window.draw(tempGraphics);

		drawChampionOrOpponentPercentageOfHeal({ 20 * tempOpponent->getPosition().x - positionCorrection, 20 * tempOpponent->getPosition().y - (positionCorrection + 4) }, tempOpponent->getLifePercentage());
	}
}

void GameWindow::drawChampionOrOpponentPercentageOfHeal(coord championPosition, double lifePercentage)
{
	coord rectangleSize = {20, 5};			// docelowo 22 x 6
	int board = 1;							// docelowo 1
	coord positionOnScreen = championPosition;
	positionOnScreen.x += 7;
	positionOnScreen.y -= 2;

	sf::RectangleShape HealFrame(sf::Vector2f(rectangleSize.x, rectangleSize.y));
	HealFrame.setFillColor(sf::Color::Transparent);
	HealFrame.setOutlineThickness(board);
	HealFrame.setOutlineColor(sf::Color::Black);
	HealFrame.setPosition(sf::Vector2f(positionOnScreen.x, positionOnScreen.y));

	sf::RectangleShape healLevel(sf::Vector2f(rectangleSize.x * lifePercentage, rectangleSize.y));
	healLevel.setFillColor(sf::Color::Red);
	healLevel.setPosition(sf::Vector2f(positionOnScreen.x, positionOnScreen.y));
	

	window.draw(HealFrame);
	window.draw(healLevel);
}

void GameWindow::clearOldMap()
{
	mapLayer1.clear();
	mapLayer2.clear();
	mapLayer3.clear();

	vectorOfOpponents.clear();
	dataToOpponentRespawn.clear();
}

void GameWindow::loadNewMap(string tempNextMapName)
{
	for (int i = 0; i < vectorOfNextMaps.size(); i++)
	{
		if (vectorOfNextMaps[i].nextMapName == tempNextMapName)
		{
			mapReader.setMapName(vectorOfNextMaps[i].nextMapName);
			hero.setPosition(vectorOfNextMaps[i].positionAtNextMap);
		}
	}

	vectorOfNextMaps.clear();
	mapReader.readMapFromFile(mapLayer1, mapLayer2, mapLayer3, vectorOfNextMaps);

	createOpponents();
}

void GameWindow::showBarOnTheRight()
{
	coord rectangleSize = { 116, 16 };
	coord positionOnScreen = { 1080 + 42, 0 + 82 };
	double lifePercentage = hero.getLifePercentage();

	sf::RectangleShape healLevel(sf::Vector2f(rectangleSize.x * lifePercentage, rectangleSize.y));
	healLevel.setFillColor(sf::Color::Red);
	healLevel.setPosition(sf::Vector2f(positionOnScreen.x, positionOnScreen.y));

	spriteBarOnTheRight.setPosition(sf::Vector2f(1080, 0));
	window.draw(spriteBarOnTheRight);
	window.draw(healLevel);
}

void GameWindow::runGame()
{
	menu.hideConsole();

	if (isError == true)
	{
		return;
	}

	window.create(sf::VideoMode(1080 + 200, 720), "SFML window", sf::Style::Close | sf::Style::Titlebar);

	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				gameStatus.saveStatusOfGame(hero.getChampionName(), mapReader.getMapName(), hero.getPosition());
				window.close();
			}
		}
		window.clear();

		drawTheMap();

		if (dataToOpponentRespawn.empty() == false)
		{
            chrono::system_clock::time_point time = chrono::system_clock::now();

			for(vector<opponentToRestore>::iterator it = dataToOpponentRespawn.begin(); it != dataToOpponentRespawn.end();)
			{
				chrono::duration<double, std::milli> deltaTime = time - it->deathTime;

				if (deltaTime > chrono::seconds(it->respawnTimeAfterDeath))
				{
					int opponentVectorSize = vectorOfOpponents.size();
					if (it->outfitID == assasin)
					{
						vectorOfOpponents.push_back(new Assassin());
					}
					else if (it->outfitID == orkSpear)
					{
						vectorOfOpponents.push_back(new OrkSpear());
					}
					else if (it->outfitID == orkSpearShield)
					{
						vectorOfOpponents.push_back(new OrkSpearShield());
					}
					else if (it->outfitID == orkSword)
					{
						vectorOfOpponents.push_back(new OrkSword());
					}
					else if (it->outfitID == pirate)
					{
						vectorOfOpponents.push_back(new Pirate());
					}
					else if (it->outfitID == skeleton)
					{
						vectorOfOpponents.push_back(new Skeleton());
					}

					vectorOfOpponents[opponentVectorSize]->setPosition(it->opponentPosition);
					vectorOfOpponents[opponentVectorSize]->setPositionAtStart(it->opponentPosition);

					vectorOfOpponents[opponentVectorSize]->setName(it->outfitName);
					vectorOfOpponents[opponentVectorSize]->setSpriteNumberInSpritesArray(it->outfitID);

					it = dataToOpponentRespawn.erase(it);
				}
				else
				{
					it++;
				}
			}
		}

		for(vector<Opponent *>::iterator it = vectorOfOpponents.begin(); it != vectorOfOpponents.end();)
		{
			
			(*it)->checkLifeLevel();
			if ((*it)->getIsDead() == true)
			{
				dataToOpponentRespawn.push_back({ (*it)->getPositionAtStart(), (*it)->getName(), (*it)->getSpriteNumberInSpritesArray(), chrono::system_clock::now(), (*it)->getRespawnTimeAfterDeath() });
          		it = vectorOfOpponents.erase(it);
			}
			else
			{
				(*it)->detectChampionNearOpponent(&hero);
				drawOpponent((*it), (*it)->action());
				it++;
			}
		}

		drawPlayer(hero.action());
		
		showBarOnTheRight();

		window.display();
	}
}

void GameWindow::deleteVectorOfOpponents()
{
	for (int i = 0; i < vectorOfOpponents.size(); i++)
	{
		delete vectorOfOpponents[i];
	}
	vectorOfOpponents.clear();
}

GameWindow::~GameWindow()
{
	deleteVectorOfOpponents();
}