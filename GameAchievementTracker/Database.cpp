#include "stdafx.h"
#include "Database.h"
#include <iostream>

using namespace std;

vector<Player> Database::playerList;

Player Database::newPlayer(int id, string name)
{
	Player newPlayer = Player(id, name);
	
	playerList.push_back(newPlayer);
	return newPlayer;
}

Game Database::newGame(int id, string name)
{
	return Game();
}

Achievement Database::newAchievement(int gameID, int achID, int achName, int pts)
{
	return Achievement();
}

void Database::printPlayers()
{
	cout << "Current player list:\n----------------\n";
	for (int i = 0; i < playerList.size(); i++)
	{
		cout << playerList.at(i).toString();
	}
	cout << "----------------\n";
}
