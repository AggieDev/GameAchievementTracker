#pragma once
#include <string>

using namespace std;

class Game
{
	//private
	//private
	int id;
	string name;
public:
	Game();
	~Game();
	Game(int id, string name);
	string toString();
};

