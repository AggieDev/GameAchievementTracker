#pragma once

#include <string>
#include <vector>
#include "Player.h"
#include "Game.h"
#include "Achievement.h"

using namespace std;

class Database
{
	//private
	static vector<Player> playerList;
	static vector<Game> gameList;
	static vector<Achievement> achievementList;

public:
	//public functions
	static Player newPlayer(int id, string name);
	static Game newGame(int id, string name);
	static Achievement newAchievement(int gameID, int id, string name, int pts);

	//testing
	static void printPlayers();
	static void printGames();
	static void printAchievements();
};
