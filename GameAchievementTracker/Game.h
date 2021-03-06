#pragma once
#include <string>
#include <vector>

using namespace std;

class Game
{
	//private
	int id;
	string name;
	vector<pair<string, int>> ignList;	//list of player's in-game names with their id's
	int achievementNumber;				//total number of achievements for game

public:
	Game();
	~Game();
	Game(int id, string name);
	//add data to game
	void addPlays(int playerID, string ign);
	void addIGN(int id, string name);
	void addToAchievementNumber(){ achievementNumber++; };
	//print players that play this game
	void printGamesPlay();
	//accessors
	string toString();
	int getID(){ return id; };
	string getName(){ return name; };
	vector<pair<string, int>> getIGNList(){ return ignList; };
	int getAchievementNumber(){ return achievementNumber; };

};

