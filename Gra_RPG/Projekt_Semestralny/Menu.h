#pragma once
#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <vector>
#include "usefullStructures.h"
#include <Windows.h>

using namespace std;

class Menu
{
private:
	string playerName;
	string playerSurname;
	string playerNick;
	string fileName;
	int menuChoice;
	vector<playerlist> listOfPlayers;

public:
	Menu();

	int gameMenu();

	void startNewGame();

	void startLoadGame();

	void info();

	string getFileName();

	string getPlayerNick();

	void hideConsole();

	~Menu();
};

