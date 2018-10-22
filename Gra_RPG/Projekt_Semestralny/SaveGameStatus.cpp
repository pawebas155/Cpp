#include "SaveGameStatus.h"

SaveGameStatus::SaveGameStatus()
{}

void SaveGameStatus::saveStatusOfGame(string playerNick, string mapName, coord playerPos)
{
	ofstream outputFile;
	try
	{
		outputFile.open("gameSaves/" + playerNick + ".txt");

		if (!outputFile.good())
		{
			throw (string)"***Nie udalo sie otworzyc mapy z folderu gameMaps***\n";
		}
	}
	catch (string notification)
	{
		cout << notification << endl;
		return;
	}

	outputFile << mapName;
	outputFile << "\n";
	outputFile << playerPos.x << " " << playerPos.y;

	outputFile.close();
}

SaveGameStatus::~SaveGameStatus()
{}
