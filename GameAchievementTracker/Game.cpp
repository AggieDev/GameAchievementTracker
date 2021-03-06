#include "stdafx.h"
#include "Game.h"
#include <iostream>

using namespace std;

Game::Game()
{
}
Game::~Game()
{
}

Game::Game(int i, string n)
{
	id = i;
	name = n;
	achievementNumber = 0;
}

//add to list of players playing this game
void Game::addPlays(int playerID, string ign)
{
	ignList.push_back(make_pair(ign, playerID));
}

//print all players and IGNs that play this game
void Game::printGamesPlay()
{
	for (int i = 0; i < ignList.size(); i++)
		cout << "Game ID: " + to_string(id) + " Player ID: " + to_string(ignList.at(i).second) + " Player IGN: " + ignList.at(i).first + "\n";
}


//accessors

string Game::toString()
{
	return "Name: " + name + " ID: " + to_string(id) + "\n";
}

