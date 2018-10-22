#pragma once
#include <vector>
#include <string>
#include <chrono>

using namespace std;

#define NOTHING 0
#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4
#define FIGHT 5

enum championsOutfits
{
	assasin = 0, hero, orkSpear, orkSpearShield, orkSword, pirate, skeleton
};

enum
{
	NEWGAME = 1, LOADGAME, INFOABOUTGAME, ERRORHEPPENED
};

struct coord
{
	int x;
	int y;
};

struct nextMap
{
	coord blockPosition;
	vector<int> crossingFields;
	coord positionAtNextMap;
	string nextMapName;
};

struct opponentPositionAndOutfit
{
	coord opponentPosition;
	string outfitName;
	int outfitID;
};

struct opponentToRestore
{
	coord opponentPosition;
	string outfitName;
	int outfitID;
	chrono::system_clock::time_point deathTime;
	int respawnTimeAfterDeath;
};

struct playerlist
{
	string Name;
	string Surname;
	string Nick;
};