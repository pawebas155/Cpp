#include "Render.h"

Render::Render()
{
	textureMapElementsAmount = 54 + 1;		// 0-54 czyli 55 elementow
	textureChampionAmount = 7;				// assassin, hero, orkSpear, orkSpearShield, orkSword, pirate, skeleton

	textureMapElements.resize(textureMapElementsAmount);
	textureChampion.resize(textureChampionAmount);

	spriteMapElements.resize(textureMapElementsAmount);
	spriteChampion.resize(textureChampionAmount);

	readTextureMapElements();
	readTextureChampion();

	readSpriteMapElements();
	readSpriteChampion();
}

const sf::Sprite & Render::getSpriteMapElementWithNumber(int number)
{
	return spriteMapElements[number];
}

const sf::Sprite & Render::getSpriteChampiontWithNumber(int number)
{
	return spriteChampion[number];
}

void Render::readTextureMapElements()
{
	string imagePath;
	for (int i = 0; i < textureMapElementsAmount; i++)
	{
		imagePath = "textures/" + to_string(i) + ".png";
		textureMapElements[i].loadFromFile(imagePath);
	}
}

void Render::readSpriteMapElements()
{
	for (int i = 0; i < textureMapElementsAmount; i++)
	{
		spriteMapElements[i].setTexture(textureMapElements[i]);
	}
}

void Render::readTextureChampion()
{
	string imagePath;

	imagePath = "champions/assassin.png";
	textureChampion[0].loadFromFile(imagePath);

	imagePath = "champions/hero.png";
	textureChampion[1].loadFromFile(imagePath);

	imagePath = "champions/orkSpear.png";
	textureChampion[2].loadFromFile(imagePath);

	imagePath = "champions/orkSpearShield.png";
	textureChampion[3].loadFromFile(imagePath);

	imagePath = "champions/orkSword.png";
	textureChampion[4].loadFromFile(imagePath);

	imagePath = "champions/pirate.png";
	textureChampion[5].loadFromFile(imagePath);

	imagePath = "champions/skeleton.png";
	textureChampion[6].loadFromFile(imagePath);
}

// kazde klatka ma rozmiar 64 x 64 px
// zdjêcie z grafikami wygl¹da nastepujaco(AxB --> A-ilosc wierszy, B-ilosc kolumn; wiersze : tyl, lewo, przod, prawo):
// 4x7  atak spella
// 4x8  atak wlocznia
// 4x9  chodzenie
// 4x6  atak mieczem
// 3x13 atak lukiem
// 1x6  umieranie
void Render::readSpriteChampion()
{
	for (int i = 0; i < textureChampionAmount; i++)
	{
		spriteChampion[i].setTexture(textureChampion[i]);
	}
}

Render::~Render()
{
}
