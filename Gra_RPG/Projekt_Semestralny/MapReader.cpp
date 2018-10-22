#include "MapReader.h"

string MapReader::getMapName()
{
	return string(mapName);
}

void MapReader::setMapName(string val)
{
	mapName = val;
}

coord MapReader::getPlayerPositionAtStart()
{
	return coord(playerPosition);
}

coord MapReader::getMapSize()
{
	return coord(mapSize);
}

vector<opponentPositionAndOutfit> MapReader::getOpponentPositionAndOutfitNumber()
{
	return vector<opponentPositionAndOutfit>(opponentPosAndOutfit);
}

void MapReader::readGameState(string tempFileName)
{
	int x;

	ifstream gameState;
	try
	{
		gameState.open(tempFileName);
		if (!gameState.good())
		{
			throw (string)"***Nie udalo sie otworzyc pliku gameState***\n";
		}
	}
	catch (string notification)
	{
		cout << notification << endl;
		return;
	}
	
	gameState >> mapName;
	gameState >> playerPosition.x;
	gameState >> playerPosition.y;

	gameState.close();
}

void MapReader::readMapFromFile(vector<vector<int>> & gameMapLayer1, vector<vector<int>> & gameMapLayer2, vector<vector<int>> & gameMapLayer3, vector<nextMap> & nextMaps)
{
	int mapSizeX = 0;
	int mapSizeY = 0;
	int amountOfMaps = 0;

	int amountOfOpponents = 0;
	opponentPositionAndOutfit temp2;

	nextMap temp;
	int amountOfCrossing = 0;
	int numberOfSquare = 0;

	ifstream actualMap;
	
	try
	{
		actualMap.open("gameMaps/" + mapName + ".txt");

		if (!actualMap.good())
		{
			throw (string)"***Nie udalo sie otworzyc mapy z folderu gameMaps***\n";
		}
	}
	catch (string notification)
	{
		cout << notification << endl;
		return;
	}

	char eatDOT;

	gameMapLayer1.clear();
	gameMapLayer2.clear();
	gameMapLayer3.clear();
	nextMaps.clear();

	actualMap >> mapSizeX >> mapSizeY;
	mapSize.x = mapSizeX;
	mapSize.y = mapSizeY;
	gameMapLayer1.resize(mapSizeY, vector<int>(mapSizeX));
	gameMapLayer2.resize(mapSizeY, vector<int>(mapSizeX));
	gameMapLayer3.resize(mapSizeY * 3, vector<int>(mapSizeX * 3));

	// wczytanie gameMapLayer1
	for (int i = 0; i < mapSizeY; i++)
	{
		for (int j = 0; j < mapSizeX; j++)
		{
			actualMap >> gameMapLayer1[i][j];
			actualMap >> eatDOT;
		}
	}

	// wczytanie gameMapLayer2
	for (int i = 0; i < mapSizeY; i++)
	{
		for (int j = 0; j < mapSizeX; j++)
		{
			actualMap >> gameMapLayer2[i][j];
			actualMap >> eatDOT;
		}
	}

	// wczytanie gameMapLayer3
	for (int i = 0; i < mapSizeY * 3; i++)
	{
		for (int j = 0; j < mapSizeX * 3; j++)
		{
			actualMap >> gameMapLayer3[i][j];
			actualMap >> eatDOT;
		}
	}
	//------------------------------------------------------------------------------------------------------------------
	actualMap >> amountOfOpponents;

	opponentPosAndOutfit.clear();
	
	for (int i = 0; i < amountOfOpponents; i++)
	{
		actualMap >> temp2.opponentPosition.x;
		actualMap >> temp2.opponentPosition.y;
		actualMap >> temp2.outfitName;
		actualMap >> temp2.outfitID;
		opponentPosAndOutfit.push_back(temp2);
	}
	//------------------------------------------------------------------------------------------------------------------
	actualMap >> amountOfMaps;

	for (int i = 0; i < amountOfMaps; i++)
	{
		temp.crossingFields.clear();

		actualMap >> temp.blockPosition.x;
		actualMap >> temp.blockPosition.y;

		actualMap >> amountOfCrossing;
		for (int j = 0; j < amountOfCrossing; j++)
		{
			actualMap >> numberOfSquare;
			temp.crossingFields.push_back(numberOfSquare);
		}

		//wczytanie pozycji na jakiej ma sie pojawic gracz po przejsciu na nastepna mape

		actualMap >> temp.positionAtNextMap.x;
		actualMap >> temp.positionAtNextMap.y;

		actualMap >> temp.nextMapName;

		nextMaps.push_back(temp);
	}
	actualMap.close();
}
