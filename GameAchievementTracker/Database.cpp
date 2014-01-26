#include "stdafx.h"
#include "Database.h"
#include <iostream>

using namespace std;

vector<Player> Database::playerList;
vector<Game> Database::gameList;
vector<Achievement> Database::achievementList;

Player Database::newPlayer(int id, string name)
{
	Player newPlayer = Player(id, name);
	playerList.push_back(newPlayer);
	return newPlayer;
}

Game Database::newGame(int id, string name)
{
	Game newGame = Game(id, name);
	gameList.push_back(newGame);
	return newGame;
}

Achievement Database::newAchievement(int gameID, int achID, string achName, int pts)
{
	Achievement newAchievement = Achievement(gameID, achID, achName, pts);
	achievementList.push_back(newAchievement);
	return newAchievement;
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

void Database::printGames()
{
	cout << "Current game list:\n----------------\n";
	for (int i = 0; i < gameList.size(); i++)
	{
		cout << gameList.at(i).toString();
	}
	cout << "----------------\n";
}

void Database::printAchievements()
{
	cout << "Current achievement list:\n----------------\n";
	for (int i = 0; i < achievementList.size(); i++)
	{
		cout << achievementList.at(i).toString();
	}
	cout << "----------------\n";
}
