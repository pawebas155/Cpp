#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include "usefullStructures.h"

using namespace std;

class Render
{
private:
	vector<sf::Texture> textureMapElements;
	vector<sf::Sprite> spriteMapElements;

	vector<sf::Texture> textureChampion;
	vector<sf::Sprite> spriteChampion;

	int textureMapElementsAmount;
	int textureChampionAmount;

public:
	Render();

	const sf::Sprite & getSpriteMapElementWithNumber(int number);

	const sf::Sprite & getSpriteChampiontWithNumber(int number);

	void readTextureMapElements();

	void readSpriteMapElements();

	void readTextureChampion();

	void readSpriteChampion();

	~Render();
};

