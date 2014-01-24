#pragma once
#include <string>

using namespace std;

class Player
{
	//private
	int id;
	string name;
public:
	Player();
	~Player();
	Player(int id, string name);
	string toString();
};
