#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "MapReader.h"
#include "Render.h"
#include "Player.h"
#include "Menu.h"
#include "SaveGameStatus.h"

#include "Assassin.h"
#include "OrkSword.h"
#include "Pirate.h"
#include "Skeleton.h"
#include "OrkSpear.h"
#include "OrkSpearShield.h"

using namespace std;

class GameWindow
{
private:
	vector<vector<int>> mapLayer1;
	vector<vector<int>> mapLayer2;
	vector<vector<int>> mapLayer3;
	vector<nextMap> vectorOfNextMaps;

	sf::RenderWindow window;
	sf::Event event;
	MapReader mapReader;
	Render render;
	Menu menu;
	bool isError;
	SaveGameStatus gameStatus;
	
	vector<Opponent *> vectorOfOpponents;
	vector<opponentToRestore> dataToOpponentRespawn;

	Player hero;
	int positionCorrection;
	int saveDoAnimation;
	
	chrono::system_clock::time_point animateClock1;
	double animationStep;
	bool stopAnimation;
	bool showAnimation;
	int lastChampionDirection;

	sf::Texture textureBarOnTheRight;
	sf::Sprite spriteBarOnTheRight;

public:
	GameWindow();

	void drawTheMap();

	void createOpponents();
	
	void animationForPlayerMoving(int animation);

	void drawPlayer(int doAnimation);

	void drawOpponent(Opponent * tempOpponent, int doAnimation);

	void drawChampionOrOpponentPercentageOfHeal(coord championPosition, double lifePercentage);

	void clearOldMap();

	void loadNewMap(string tempNextMapName);

	void showBarOnTheRight();

	void  runGame();

	void deleteVectorOfOpponents();

	~GameWindow();
};