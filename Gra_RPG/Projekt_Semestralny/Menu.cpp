#include "Menu.h"

Menu::Menu()
{}

int Menu::gameMenu()
{
	menuChoice = ERRORHEPPENED;

	system("cls");
	

	cout << " Select option" << endl;
	cout << " 1. New Game" << endl;
	cout << " 2. Load Game" << endl;
	cout << " 3. Info" << endl;

	regex chooseRegex("\\d");
	string choose;
	while (true)
	{
		cout << " Your choice :";
		cin >> choose;
				
		if (regex_match(choose, chooseRegex))
		{
			if (stoi(choose) > 0 && stoi(choose) < 4)
			{
				break;
			}
		}
		
	}

	if (stoi(choose) == NEWGAME)
	{
		startNewGame();

		menuChoice = NEWGAME;

		return menuChoice;
	}
	else if (stoi(choose) == LOADGAME)
	{
		startLoadGame();
		menuChoice = LOADGAME;
		return menuChoice;
	}
	else if (stoi(choose) == INFOABOUTGAME)
	{
		// pokazuje sterowanie
		info();
		gameMenu();
	}

	return menuChoice;
}

void Menu::startNewGame()
{
	system("cls");

	bool nickNotBusy = false;

	ifstream inputFile;
	try
	{
		inputFile.open("gameSaves/listOfPlayers.txt");

		if (!inputFile.good())
		{
			throw (string)"***Nie udalo sie otworzyc mapy z folderu gameMaps***\n";
		}
	}
	catch (string notification)
	{
		cout << notification << endl;
		return;
	}

	playerlist tempElementOfPlayerList;
	while (!inputFile.eof())
	{
		inputFile >> tempElementOfPlayerList.Name;
		inputFile >> tempElementOfPlayerList.Surname;
		inputFile >> tempElementOfPlayerList.Nick;

		listOfPlayers.push_back(tempElementOfPlayerList);
	}
	inputFile.close();

	regex checkName("[A-Z][a-z]{1,}");
	regex checkSurname("[A-Z][a-z]+");
	regex checkNick("[A-Z]((\\d)|([a-z])){3,}");

	// write name
	while(true)
	{
		cout << " Name: ";
		cin >> playerName;

		if (regex_match(playerName, checkName))
		{
			break;
		}
		else
		{
			cout << " Incorrect name\n";
		}
	}

	// write surname
	while (true)
	{
		cout << " Surname: ";
		cin >> playerSurname;

		if (regex_match(playerSurname, checkSurname))
		{
			break;
		}
		else
		{
			cout << " Incorrect surname\n";
		}
	}

	// write nick
	while (true)
	{
		cout << " Nick: ";
		cin >> playerNick;

		for (int i = 0; i < listOfPlayers.size(); i++)
		{
			if (listOfPlayers[i].Nick == playerNick)
			{
				cout << " this nickname is busy\n";
				nickNotBusy = true;
				break;
			}
			else
			{
				nickNotBusy = false;
			}
		}

		if (regex_match(playerNick, checkNick) && nickNotBusy == false)
		{
			
			break;
		}
		else
		{
			cout << " Incorrect nick\n";
		}
	}


	ofstream outputFile;
	try
	{
		outputFile.open("gameSaves/listOfPlayers.txt", ofstream::app);

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

	outputFile << playerName;
	outputFile << "\n";
	outputFile << playerSurname;
	outputFile << "\n";
	outputFile << playerNick;
	outputFile << "\n\n";

	outputFile.close();

	fileName = "gameMaps/startNewGame.txt";
}

void Menu::startLoadGame()
{
	system("cls");

	ifstream inputFile;
	try
	{
		inputFile.open("gameSaves/listOfPlayers.txt");

		if (!inputFile.good())
		{
			throw (string)"***Nie udalo sie otworzyc mapy z folderu gameMaps***\n";
		}
	}
	catch (string notification)
	{
		cout << notification << endl;
		return;
	}

	listOfPlayers.clear();
	playerlist tempElementOfPlayerList;
	while (!inputFile.eof())
	{
		if (!(inputFile >> tempElementOfPlayerList.Name))
		{
			break;
		}
		inputFile >> tempElementOfPlayerList.Surname;
		inputFile >> tempElementOfPlayerList.Nick;

		listOfPlayers.push_back(tempElementOfPlayerList);
	}
	inputFile.close();

	int i;
	for (i = 0; i < listOfPlayers.size(); i++)
	{
		cout << " " << i << "." << endl;
		cout << " " << listOfPlayers[i].Name << endl;
		cout << " " << listOfPlayers[i].Surname << endl;
		cout << " " << listOfPlayers[i].Nick << endl;
		cout << endl;
	}
	cout << " " << i << ". back number\n";

	cout << " Chose your hero or back number\n\n";

	regex chooseRegex("\\d");
	string choice;
	while (true)
	{
		cout << " Your Choice :";
		cin >> choice;

		if (regex_match(choice, chooseRegex))
		{
			if (stoi(choice) >= 0 && stoi(choice) <= i)
			{
				break;
			}
		}
	}

	if (stoi(choice) == i)
	{
		listOfPlayers.clear();
		gameMenu();
		return;
	}

	playerName = listOfPlayers[stoi(choice)].Name;
	playerSurname = listOfPlayers[stoi(choice)].Surname;
	playerNick = listOfPlayers[stoi(choice)].Nick;

	fileName = "gameSaves/" + listOfPlayers[stoi(choice)].Nick + ".txt";
}

void Menu::info()
{
	system("cls");
	cout << "    ***Control***    " << endl;
	cout << " w     --> move up   " << endl;
	cout << " s     --> move down " << endl;
	cout << " a     --> move left " << endl;
	cout << " d     --> move right" << endl;
	cout << " space --> attact    " << endl << endl;

	regex backToMenuRegex("[a-z]");
	string backToMenu;
	cout << " press b to back\n";
	while (true)
	{
		cout << " Your Choice :";
		cin >> backToMenu;
		if (regex_match(backToMenu, backToMenuRegex))
		{
			if (backToMenu == "b" || backToMenu == "B")
			{
				break;
			}
		}
	}
	system("cls");
}

string Menu::getFileName()
{
	return string(fileName);
}

string Menu::getPlayerNick()
{
	return string(playerNick);
}

void Menu::hideConsole()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}

Menu::~Menu()
{}
