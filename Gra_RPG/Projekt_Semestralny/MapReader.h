#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "usefullStructures.h"
#include <vector>
#include <string>

using namespace std;

// klasa czytajaca mape z pliku i zapisujaca j¹ do tablicy
class MapReader
{
private:
	string mapName;
	coord playerPosition;
	coord mapSize;
	vector<opponentPositionAndOutfit> opponentPosAndOutfit;

public:
	string getMapName();
	void setMapName(string val);

	coord getPlayerPositionAtStart();

	coord getMapSize();

	vector<opponentPositionAndOutfit> getOpponentPositionAndOutfitNumber();

	void readGameState(string tempFileName);

	void readMapFromFile(vector<vector<int>> & gameMapLayer1, vector<vector<int>> & gameMapLayer2, vector<vector<int>> & gameMapLayer3, vector<nextMap> & nextMaps);
};

