#pragma once

#include <string>
#include <vector>
#include "Player.h"
#include "Game.h"
#include "Achievement.h"

using namespace std;

//database has static methods to allow methods/data members to belong to 
//class rather than instance, only 1 database so no instances needed

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
	static Game* playerPlays(int playerID, int gameID, string ign);
	static void makeFriends(int firstID, int secondID);
	static void achieved(int playerID, int gameID, int achievementID);
	static void printFriendsWhoPlay(int playerID, int gameID);
	static void comparePlayers(int playerID1, int playerID2, int gameID);

	//accessors
	static Player* getPlayerByID(int id);
	static Game* getGameByID(int id);
	static Achievement* getAchievementByID(int id);

	//printouts for testing
	static void printPlayers();
	static void printGames();
	static void printAchievements();
};
