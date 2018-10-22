#include "WindowScreen.h"
#include <iostream>
#include "Pawn.h"

MyWindow::MyWindow()
{
	CreateMyWindow();
}

void MyWindow::CreateMyWindow()
{
	window.create(sf::VideoMode(width, height), "My Window", sf::Style::Close | sf::Style::Titlebar);
	setWindowIcon();
	rectangle.setSize(sf::Vector2f(square, square));
	setNumbersForBoard();
	pointForPossibleMove();
}

//ustawianie ikony okna
void MyWindow::setWindowIcon()
{
	image.loadFromFile("Graphics/ChessIcon.png");
	window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
}

// ustawienie tekstury i sprite'u dla punktu wskazujacego na mozliwe ruchy gracza
void MyWindow::pointForPossibleMove()
{
	pointTextureForPossibleMove.loadFromFile("Graphics/aim.png");
	pointSpriteForPossibleMove.setTexture(pointTextureForPossibleMove);
}

// ustawienie w oknie oznakowania planszy: cyfr od 1 do 8 i liter od A do H
void MyWindow::setNumbersForBoard()
{
	numbertexture[0].loadFromFile("Graphics/ozn1.png");
	numbersprite[0].setTexture(numbertexture[0]);
	numbertexture[1].loadFromFile("Graphics/ozn2.png");
	numbersprite[1].setTexture(numbertexture[1]);
	numbertexture[2].loadFromFile("Graphics/ozn3.png");
	numbersprite[2].setTexture(numbertexture[2]);
	numbertexture[3].loadFromFile("Graphics/ozn4.png");
	numbersprite[3].setTexture(numbertexture[3]);
	numbertexture[4].loadFromFile("Graphics/ozn5.png");
	numbersprite[4].setTexture(numbertexture[4]);
	numbertexture[5].loadFromFile("Graphics/ozn6.png");
	numbersprite[5].setTexture(numbertexture[5]);
	numbertexture[6].loadFromFile("Graphics/ozn7.png");
	numbersprite[6].setTexture(numbertexture[6]);
	numbertexture[7].loadFromFile("Graphics/ozn8.png");
	numbersprite[7].setTexture(numbertexture[7]);

	lettertexture[0].loadFromFile("Graphics/oznA.png");
	lettersprite[0].setTexture(lettertexture[0]);
	lettertexture[1].loadFromFile("Graphics/oznB.png");
	lettersprite[1].setTexture(lettertexture[1]);
	lettertexture[2].loadFromFile("Graphics/oznC.png");
	lettersprite[2].setTexture(lettertexture[2]);
	lettertexture[3].loadFromFile("Graphics/oznD.png");
	lettersprite[3].setTexture(lettertexture[3]);
	lettertexture[4].loadFromFile("Graphics/oznE.png");
	lettersprite[4].setTexture(lettertexture[4]);
	lettertexture[5].loadFromFile("Graphics/oznF.png");
	lettersprite[5].setTexture(lettertexture[5]);
	lettertexture[6].loadFromFile("Graphics/oznG.png");
	lettersprite[6].setTexture(lettertexture[6]);
	lettertexture[7].loadFromFile("Graphics/oznH.png");
	lettersprite[7].setTexture(lettertexture[7]);
}

// pokazanie w oknie oznakowanie planszy: cyfr od 1 do 8 i liter od A do H
void MyWindow::showNumberForBoard()
{
	for (int i = 0; i < 8; i++)
	{
		numbersprite[7 - i].setPosition((float)((width - board) / 2 - 50), (float)((height - board) / 2 + (square * i)));
		window.draw(numbersprite[i]);
		lettersprite[i].setPosition((float)((width - board) / 2 + (square * i)), (float)((height - board) / 2 - 50));
		window.draw(lettersprite[i]);
	}
}

// wydrukowanie szachownicy na ekranie
void MyWindow::setAndShowChessColorBoard()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			rectangle.setPosition((float)(((width - board) / 2) + (square*j)), (float)(((height - board) / 2) + (square*i)));
			if (i % 2 != 0)
			{
				if (j % 2 == 0)
				{
					rectangle.setFillColor(sf::Color::Black);
				}
				else
				{
					rectangle.setFillColor(sf::Color::White);
				}
			}
			else
			{
				if (j % 2 == 0)
				{
					rectangle.setFillColor(sf::Color::White);
				}
				else
				{
					rectangle.setFillColor(sf::Color::Black);
				}
			}
			window.draw(rectangle);
		}
	}
}

// wydrukowanie wszystkich pionków na szachownicy
void MyWindow::showChessOnBoard( const vector<vector<sf::Sprite*>> Board)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (Board[i][j] != nullptr)
			{
				(Board[i][j])->setPosition((float)(((width - board) / 2 + 4) + (square * j)), (float)(((height - board) / 2 + 4) + (square * i)));
				window.draw( *(Board[i][j]) );
			}
		}
	}
}

void MyWindow::sendMessage(int choice)
{
	sf::Font font; // (uzywamy wszedzie tej samej czcionki)
	font.loadFromFile("ExampleFont.ttf");
	sf::Text text;
	text.setFont(font);
	// ustawienie wielkoœci czcionki w pikselach
	text.setCharacterSize(24);
	text.setPosition(sf::Vector2f(800, 300));
	
	if (choice > 3)
	{
		return;
	}

	switch (choice)
	{
	case 1:
	{
		text.setString("Szach");
		break;
	}
	case 2:
	{
		text.setString("Szach Mat");
		break;
	}
	case 3:
	{
		text.setString("Bedzie Szach");
		break;
	}
	}
	window.draw(text);
}

// obs³uga myszy, jesli nacisnie przycisk to wybiera dane pole
MyPoint MyWindow::MouseOperations()
{
	mouseChoose = { -1,-1 };
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			MouseLocalPosition = sf::Mouse::getPosition(window);

			for (int i = 212, j = 0; i < 717; i += 72, j++)
			{
				if (MouseLocalPosition.x > i && MouseLocalPosition.x < i + 72 && MouseLocalPosition.y >(height - board) / 2 && MouseLocalPosition.y < ((height - board) / 2) + board)
				{
					mouseChoose.x = j;
					break;
				}
			}

			for (int i = 62, j = 0; i < 567; i += 72, j++)
			{
				if (MouseLocalPosition.y > i && MouseLocalPosition.y < i + 72 && MouseLocalPosition.x >(width - board) / 2 && MouseLocalPosition.x < ((width - board) / 2) + board)
				{
					mouseChoose.y = j;
					break;
				}
			}
		}
			
	}
	return mouseChoose;
}

void MyWindow::showPossibleMoves(list<MyPoint> *listOfPossibleMoves)
{
	list<MyPoint>::iterator it = (*listOfPossibleMoves).begin();

	for (; it != (*listOfPossibleMoves).end(); it++)
	{
		pointSpriteForPossibleMove.setPosition((float)(((width - board) / 2 + 16) + (square * it->y)), (float)(((height - board) / 2 + 16) + (square * it->x)));
		window.draw(pointSpriteForPossibleMove);
	}
}