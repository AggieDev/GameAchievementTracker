#pragma once
#include <string>
#include <vector>

using namespace std;

class Game
{
	//private
	int id;
	string name;
	vector<pair<string, int>> ignList; //list of player's in-game names with their id's
public:
	Game();
	~Game();
	Game(int id, string name);
	string toString();
	void addIGN(int id, string name);
};

