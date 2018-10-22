#include "AllPawns.h"

MyAllPawns::MyAllPawns(string Name, MyPoint point, int color, int pos) : name(Name), position(point), Pcolor(color)
{
	graphic.texture.loadFromFile("Graphics/chesspiece.png", sf::IntRect(pos * 64, color * 64, 64, 64));
	graphic.sprite.setTexture(graphic.texture);
}

sf::Sprite* MyAllPawns::getSprite()
{
	return &graphic.sprite;
}

int MyAllPawns::showColor()
{
	return Pcolor;
}

string MyAllPawns::getName()
{
	return name;
}

MyPoint MyAllPawns::getPosition()
{
	return position;
}

MyAllPawns::~MyAllPawns()
{}