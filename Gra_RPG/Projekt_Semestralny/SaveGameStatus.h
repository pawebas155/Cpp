#pragma once
#include <string>
#include "usefullStructures.h"
#include <fstream>
#include <iostream>

using namespace std;

class SaveGameStatus
{
public:
	SaveGameStatus();

	void saveStatusOfGame(string playerNick, string mapName, coord playerPos);

	~SaveGameStatus();
};

