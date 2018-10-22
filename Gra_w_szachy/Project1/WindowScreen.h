#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "vector"
#include "myUsefulStruct.h"
#include <list>

#define width 1000
#define height 700
#define square 72
#define board 576

using namespace std;

class MyWindow
{
private:
	sf::Image image;
	sf::RectangleShape rectangle;
	
	sf::Texture pointTextureForPossibleMove;
	sf::Sprite pointSpriteForPossibleMove;

	sf::Texture numbertexture[8];
	sf::Sprite numbersprite[8];

	sf::Texture lettertexture[8];
	sf::Sprite lettersprite[8];

	sf::Vector2i MouseLocalPosition;

	MyPoint mouseChoose;

public:
	sf::Event event;
	sf::RenderWindow window;

	MyWindow();

	void CreateMyWindow();
	
	void setWindowIcon();

	void pointForPossibleMove();
	
	void setNumbersForBoard();
	
	void showNumberForBoard();
	
	void setAndShowChessColorBoard();
	
	void sendMessage(int choice);

	void showChessOnBoard(const vector<vector<sf::Sprite*>> Board);
	
	MyPoint MouseOperations();
	
	void showPossibleMoves(list<MyPoint> *listOfPossibleMoves);
};